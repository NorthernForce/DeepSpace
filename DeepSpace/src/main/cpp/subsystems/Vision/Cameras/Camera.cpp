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

Vision::Camera::Camera(std::string name, std::string devPath, int width, int height, int fps, bool flipOutput, int lightRingID) {
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

  m_flipOutput = flipOutput;

  if (lightRingID != -1) {
    m_lightRing.reset(new frc::Relay(lightRingID, frc::Relay::kForwardOnly));
  }

  m_isTargetting = false;
}

void Vision::Camera::process() {
  if (!isTargetting()) {
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

    if (m_flipOutput) {
      cv::flip(frame, frame, -1);
    }

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
  if (newSettings == "") {
    newSettings = k_defaultSettings;
  }

  if (newSettings == m_currentSettings) {
    // Update settings, just in case something happened
    system((m_baseCommand +newSettings).c_str());
  }
  else {
    // Reset old settings, too
    if (newSettings != k_defaultSettings) {
      newSettings = k_defaultSettings +"," +newSettings;
    }

    system((m_baseCommand +newSettings).c_str());

    // Pause the camera thread while camera settings update
    std::this_thread::sleep_for(std::chrono::milliseconds(k_settingsChangeDelayMillis));
  }

  m_currentSettings = newSettings;
}

void Vision::Camera::setLightRing(bool turnOn) {
  if (m_lightRing != nullptr) {
    frc::Relay::Value val = ((turnOn && isTargetting()) ? frc::Relay::kOn : frc::Relay::kOff);

    if (m_lightRing->Get() != val) {
      m_lightRing->Set(val);

      // THIS SHOULDN'T MATTER!
      // // Pause the camera thread while the lightring turns on/off
      // std::this_thread::sleep_for(std::chrono::milliseconds(k_lightringChangeDelayMillis));
    }
  }
}

void Vision::Camera::setTarget(std::shared_ptr<Vision::Target> target) {
  std::atomic_store(&m_objectToTarget, target);
}

std::string Vision::Camera::getTarget() {
  if (m_objectToTarget == nullptr) {
    return "";
  }
  else {
    return m_objectToTarget->k_name;
  }
}

void Vision::Camera::enableTargetting(bool enable) {
  m_isTargetting = enable;

  if (!enable) {
    setLightRing(false);
  }
  else {
    if (m_currentTarget != nullptr) {
      m_currentTarget->setup(this);
    }
  }
}

bool Vision::Camera::isTargetting() {
  return m_isTargetting.load();
}