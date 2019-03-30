#include "subsystems/Vision/Cameras/Camera.h"

const std::string Vision::Camera::k_defaultSettings = 
  "brightness=133,"
  "contrast=5,"
  "saturation=83,"
  // "white_balance_temperature_auto=0," // Must be manual to change settings.
  // "white_balance_temperature=4500,"
  "white_balance_temperature_auto=1,"
  "power_line_frequency=2,"
  "sharpness=25,"
  "backlight_compensation=0,"
  "exposure_auto=1,"
  "exposure_absolute=156";
  // "pan_absolute=0,"
  // "tilt_absolute=0,"
  // "zoom_absolute=0";

const int Vision::Camera::k_settingsChangeDelayMillis = 250;
const int Vision::Camera::k_lightringChangeDelayMillis = 50;

Vision::Camera::Camera(std::string name, std::string devPath, int width, int height, int fps, int lightRingID) {
  m_name = name;
  m_path = devPath;

  m_baseCommand = "v4l2-ctl --device " +m_path +" --set-ctrl ";

  // This link has a way to get frames but not start automatic capture:
  // https://www.chiefdelphi.com/t/vision-processing-limits/339493/21
  // m_camera = std::make_shared<cs::UsbCamera>(m_name, m_path);
  // frc::GetCameraServerShared()->ReportUsbCamera(m_camera->GetHandle());
  m_camera = std::make_shared<cs::UsbCamera>(frc::CameraServer::GetInstance()->StartAutomaticCapture(m_name, m_path));
  m_camera->SetResolution(width, height);
  m_camera->SetFPS(fps);
  m_cameraSink = std::make_shared<cs::CvSink>(frc::CameraServer::GetInstance()->GetVideo(m_name));
  m_debugStream = std::make_shared<cs::CvSource>(frc::CameraServer::GetInstance()->PutVideo(m_name +" Debug", width, height));

  if (lightRingID != -1) {
    m_lightRing.reset(new frc::Relay(lightRingID, frc::Relay::kForwardOnly));
  }

  m_isEnabled = false;
}

void Vision::Camera::process() {
  if (!isEnabled()) {
    return;
  }

  if (m_currentTarget != m_objectToTarget) {
    if (m_currentTarget != nullptr) {
      m_currentTarget->resetOffset();
    }

    m_currentTarget = m_objectToTarget;

    // Reset all camera settings
    setLightRing(false);

    // Call target setup
    if (m_currentTarget != nullptr) {
      m_currentTarget->setup(this);
    }
  }

  if (m_currentTarget != nullptr) {
    cv::Mat frame;
    auto status = m_cameraSink->GrabFrame(frame);

    if (status == 0) {
      std::cout << "Vision Error: " << m_name << ": " << m_cameraSink->GetError() << "\n";
    }
    else {
      m_currentTarget->run(frame);

      m_debugStream->PutFrame(frame);
    }
  }
}

void Vision::Camera::updateSettings(std::string newSettings) {
  if (newSettings != m_currentSettings) {
    system((m_baseCommand + k_defaultSettings).c_str());

    if (newSettings != "") {
      system((m_baseCommand + newSettings).c_str());
      m_currentSettings = newSettings;
    }
    else {
      m_currentSettings = k_defaultSettings;
    }

    // Pause the camera thread while camera settings update
    std::this_thread::sleep_for(std::chrono::milliseconds(k_settingsChangeDelayMillis));
  }
}

void Vision::Camera::setLightRing(bool turnOn) {
  if (m_lightRing != nullptr) {
    frc::Relay::Value val = ((turnOn && isEnabled()) ? frc::Relay::kOn : frc::Relay::kOff);

    if (m_lightRing->Get() != val) {
      m_lightRing->Set(val);

      // // Pause the camera thread while the lightring turns on/off
      // std::this_thread::sleep_for(std::chrono::milliseconds(k_lightringChangeDelayMillis));
    }
  }
}

void Vision::Camera::setTarget(std::shared_ptr<Vision::Target> target) {
  std::atomic_store(&m_objectToTarget, target);

  if (target != nullptr) {
    enable(true);
  }
}

void Vision::Camera::enable(bool enable) {
  m_isEnabled = enable;

  if (!enable) {
    setLightRing(false);
  }
  else {
    if (m_currentTarget != nullptr) {
      m_currentTarget->setup(this);
    }
  }
}

bool Vision::Camera::isEnabled() {
  return m_isEnabled.load();
}