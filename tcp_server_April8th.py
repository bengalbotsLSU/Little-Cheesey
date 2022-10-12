#!/usr/bin/python3

import socketserver
import Setup
import MotorCallableFunctions as motor_lib
import os
from time import sleep
SOLENOID_PIN = 16

def parse_data(byte_input):
	if len(byte_input) is not 4:
		return None
	key = (byte_input[1] << 8) + byte_input[0]
	val = (byte_input[3] << 8) + byte_input[2]
	return (key, val)
class TCP_Handler(socketserver.BaseRequestHandler):
    def handle(self):
        while True:
            self.data = self.request.recv(4).strip()
            key, val = parse_data(self.data)
            if key == 0xA01:
		#TODO: KILL
                print("kill")
                motor_lib.killMotors()
                os.system("sudo shutdown -h now")
            elif key == 0x702:
                if val == 0x8001:
                  motor_lib.setMotorSpeed(240)
                  print("up")
                elif val == 0x7fff:
                  motor_lib.setMotorSpeed(-240)
                  print("down")
                else:
                  motor_lib.setMotorSpeed(0)
                  print("release dpad")
            elif key == 0x401:
                motor_lib.rotateLeftTrigger(240)
                print("left")
            elif key == 0x501:
                motor_lib.rotateRightTrigger(240)
                print("right")
            elif key == 0x201 and val == 1:
                Setup._pi.write(SOLENOID_PIN, 1)
                sleep(1)
                Setup._pi.write(SOLENOID_PIN, 0)
            elif key == 0x401 and val == 0:
                motor_lib.setMotorSpeed(0)
            else:
                print("Nothing")

if __name__ == "__main__":
    host = "167.96.2.239"
    port = 501
    # Setup motors
    motor_lib.start()
    # Setup TCP Server
    tcp = socketserver.TCPServer((host,port), TCP_Handler)
    tcp.serve_forever()
