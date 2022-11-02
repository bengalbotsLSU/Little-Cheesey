/*
This code is for the RoboRio board. As such, there are a few naming conventions, libraries, and class names that require pre-requisite 
knowledge to fully understand. Any information surrounding this can be found on WPILIB's website: https://docs.wpilib.org/en/stable/index.html 

Additionally, if you wanted to run this you would have to download the WPILIB (College who made the software) version of vs-code and there are 
additional JSON and initialization files that would be automatically created. Other than that, though, this is the main CPP file for the basic drive 
controls with a ps4 controller and 2 motors. 
*/

// Libraries:-------------------------------------------------------------------

#include <frc/TimedRobot.h> // Robot Project Type.
#include <frc/drive/DifferentialDrive.h> // Differential Drive Train.
#include <frc/PS4Controller.h> // PS4 Controller Library.
#include <frc/motorcontrol/VictorSP.h> // Using Victor SP Motor Controller.

//------------------------------------------------------------------------------

class Robot : public frc::TimedRobot 
{ 
 public: // Main Drive Code Goes Here In Public.

  void RobotInit() override // Robot Initialization.
  {
    // Invert Right Side Motor.
    victor2.SetInverted(true); 
  }

  void TeleopPeriodic() override // Contantly Looping Code.
  { 
    // Arcade Drive Type. R2/L2 Controlls Forward/Backward, Left Joystick Controls 0-Point Turns:
    m_drive.ArcadeDrive(examplePS4.GetR2Axis() - examplePS4.GetL2Axis(), examplePS4.GetLeftX());
  }

 private: // Variable & Object Declarations Go Here In Private.

  // PS4 Controller Object.
  frc::PS4Controller examplePS4{0}; 

  // Motor Controller Objects & PWM Pins:
  frc::VictorSP victor1{0};
  frc::VictorSP victor2{1};

  // Drive Train Object.
  frc::DifferentialDrive m_drive{victor1, victor2}; 
};

// This Section Bypasses The Main Function To Run Our Functions:
#ifndef RUNNING_FRC_TESTS
int main() 
{
  return frc::StartRobot<Robot>();
}
#endif
