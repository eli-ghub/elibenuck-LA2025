#include "Arduino_SensorKit.h"
#include <Servo.h>

Servo myservo;  // create Servo object to control a servo

int potpin = A0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int val2;

void setup() {
  myservo.attach(3); 
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  
  Accelerometer.begin();
}
 
void loop() {
  // put your main code here, to run repeatedly:
  // 3 axis
  Serial.print("x:"); 
  val2=Accelerometer.readX();
  Serial.println(Accelerometer.readX());  // Read the X Value 
  
    // scale it for use with the servo (value between 0 and 180)
  myservo.write(Accelerometer.readX());                  // sets the servo position according to the scaled value

 
  delay(15);
}




