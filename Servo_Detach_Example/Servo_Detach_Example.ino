#include <Servo.h> // Include Servo Library:

Servo servoTwo, servoThree; 
/* Create Servo Objects. 
 * servoTwo = Top Of Arm. servoThree = Center Arm. 
 * servoTwo Range: 0(Down) - 125(Up).
 * servoThree Range: 20(Down) - 180(Up).
 */

void setup() 
{
  servoTwo.attach(5); // Top Of Arm Servo Pin Attachment And Initial Position Setup.
  servoTwo.write(125); 
  delay(500); // Small Delay To Avoid Servo Detach Too Early.
  servoTwo.detach();
  
  servoThree.attach(3); // Central Arm Servo Pin Attachment And Initial Position Setup.
  servoThree.write(180);
  delay(500); // Small Delay To Avoid Servo Detach Too Early.
  servoThree.detach();
}

void loop() 
{
  
}

// Arm Down Function. Arm Will Swing Down & Hook. Detaching After Every Movement To Avoid High Current Draw And/Or Resets. 
void armDown()
{
  
  //attach-write-detach cycle prevents more than 
  //two servos from being powered at once
  servoThree.attach(3);
  servoThree.write(20);
  delay(500);
  servoThree.detach();

  servoTwo.attach(5);
  servoTwo.write(0);
  delay(500);
  servoTwo.detach();
}

// Arm Pick Up Function. Arm Will Swing Back Up. Detaching After To Avoid High Current Draw And/Or Resets. 
void armUp()
{
  servoThree.attach(3);
  servoThree.write(180);
  delay(500);
  servoThree.detach();
}
