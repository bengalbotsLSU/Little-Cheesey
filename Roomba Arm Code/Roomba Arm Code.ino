#include <Servo.h> // Include Servo Library:

Servo servoTwo, servoThree, servoFive;
/* Create Servo Objects. 
 * servoTwo = Top Of Arm. servoThree = Center Arm. ServoFive = Hook Servo.
 * servoTwo Range: 10(Up) - 70(Down).
 * servoThree Range: 80(Up) - 50(Down).
 * servoFive Range: 20(Up) - 0(Down)
 */

void setup() 
{
  // Servo Pin Attachments:
  servoTwo.attach(5); 
  servoThree.attach(3); 
  servoFive.attach(9); 

  // Arm Up:
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

  // Arm Pull In & Up:
  servoThree.write(110);
  delay(1000);
  servoFive.detach(); // This Detach Is To Ensure Hook Hangs With Weight Rather Than Staying Engaged.
  servoTwo.write(10); 
  delay(1000);
}

void loop() 
{
}