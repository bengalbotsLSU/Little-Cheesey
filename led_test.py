import Setup
import MotorCallableFunctions
from time import sleep

MotorCallableFunctions.killMotors()
sleep(5)
MotorCallableFunctions.start()
sleep(5)
print(Setup._pi.read(22))
