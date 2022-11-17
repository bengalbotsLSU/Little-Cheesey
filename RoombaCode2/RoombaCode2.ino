#include <Servo.h>
//#include <ServoTimer2.h> // Include Alternate Servo Library:
#include <PS4BT.h>
#include <usbhub.h>

Servo servoTwo, servoThree, servoFive;
/* Create Servo Objects.
   servoTwo = Top Of Arm. servoThree = Center Arm. ServoFive = Hook Servo.
   servoTwo Range: 10(Up) - 70(Down).
   servoThree Range: 80(Up) - 50(Down).
   servoFive Range: 40(Up) - 0(Down)
*/

// Satisfy the IDE, which needs to see the include statement in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
int IN1 = 3;       //control pin for first motor
int IN2 = 4;       //control pin for first motor
int IN3 = 5;        //control pin for second motor
int IN4 = 6;        //control pin for second motor
USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the PS4BT class in two ways */
// This will start an inquiry and then pair with the PS4 controller - you only have to do this once
// You will need to hold down the PS and Share button at the same time, the PS4 controller will then start to blink rapidly indicating that it is in pairing mode
PS4BT PS4(&Btd, PAIR);

// After that you can simply create the instance like so and then press the PS button on the device
//PS4BT PS4(&Btd);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

void setup() {
  // Servo Pin Attachments:
  servoTwo.attach(2);
  servoThree.attach(7);
  servoFive.attach(8);
/*
  servoFive.write(0);
      servoThree.write(80);
      delay(1000);
      servoTwo.write(10);
      delay(1000);

      // Arm Down & Grab:
      servoTwo.write(70);
      delay(1000);
      servoThree.write(50);
      delay(1000);
      servoFive.write(20);
      delay(500);
*/

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));

}
void loop() {
  Usb.Task();

  if (PS4.connected()) {
    //  if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) {
    if (PS4.getAnalogHat(LeftHatX) < 10)
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      Serial.print("\nHatX: 50 ");
    }
    else if (PS4.getAnalogHat(LeftHatX) > 240)
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

      Serial.print("\nHatX: 200 ");
    }
    else if (PS4.getAnalogHat(LeftHatY) < 20)
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

      Serial.print("\nHatY: 50 ");
    }
    else if (PS4.getAnalogHat(LeftHatY) > 200)
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      Serial.print("\nHatY: 200 ");
    }
    //////////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ARM CODE
    else if (PS4.getButtonClick(TRIANGLE))
    {

      Serial.print(F("\r\nTriangle"));
      
      // Arm Up:
  servoFive.attach(8);
  servoFive.write(0);
  servoThree.write(80);
  delay(1000);
  servoTwo.write(10); 
  delay(1000);

  // Arm Down & Grab:
  servoTwo.write(70);
  delay(1000); 
  servoThree.write(50);
  delay(1000);
  servoFive.write(40);
  delay(500);

  // Arm Pull In & Up:
  servoThree.write(110);
  delay(1000);
  servoFive.detach(); // This Detach Is To Ensure Hook Hangs With Weight Rather Than Staying Engaged.
  servoTwo.write(10); 
  delay(1000);


    }
    //////////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ARM CODE
    else {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      Serial.print("\nrotate the joystick ");


    }

  }
}
