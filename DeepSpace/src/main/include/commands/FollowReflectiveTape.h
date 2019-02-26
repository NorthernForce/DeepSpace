/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/PIDController.h>

#include <string>

class FollowReflectiveTape : public frc::Command {
 public:
  FollowReflectiveTape();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

  class TargetPIDSource : public frc::PIDSource {
   public:
    TargetPIDSource() {};
    virtual double PIDGet() override;
    virtual void SetPIDSourceType(frc::PIDSourceType pidSource) {
      m_pidSource = pidSource;
    };
    virtual frc::PIDSourceType GetPIDSourceType() const {
      return m_pidSource;
    };
  };
  class DriveTrainPIDOutput : public frc::PIDOutput {
   public:
    DriveTrainPIDOutput() {};
    virtual void PIDWrite(double output) override;
  };

 private:
  const double k_p = 0;
  const double k_i = 0;
  const double k_d = 0;
  const double k_f = 0;
  
  std::shared_ptr<frc::PIDController> m_pidController;
};
