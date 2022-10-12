from __future__ import print_function
import time
from dual_g2_hpmd_rpi import motors, MAX_SPEED

#Call this function first
def start():
    motors.enable()
    motors.setSpeeds(0, 0)

def setMotorSpeed(speed):
    motors.motor1.setSpeed(speed)
    motors.motor2.setSpeed(speed)

def killMotors():
    motors.motor1.setSpeed(0)
    motors.motor2.setSpeed(0)
    motors.disable()

def rotateRightTrigger(speed):
    motors.motor1.setSpeed(speed)
    motors.motor2.setSpeed(-speed)

def rotateLeftTrigger(speed):
    motors.motor1.setSpeed(-speed)
    motors.motor2.setSpeed(speed)
