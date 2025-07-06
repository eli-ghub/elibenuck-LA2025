/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/
int mydelay = 1000; // delay in microseconds
int gled1 = 13;
int gled2 = 12;
int x = 3;
int y;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins gled1 and gled2 as outputs.
  pinMode(gled1, OUTPUT);
  pinMode(gled2, OUTPUT);
}



void loop() {
  PORTB |= (1 << PB5) | (1 << PB4); // Set pins 13 (PB5) and 12 (PB4) HIGH simultaneously
  delayMicroseconds(mydelay);

  PORTB &= ~((1 << PB5) | (1 << PB4)); // Set pins 13 (PB5) and 12 (PB4) LOW simultaneously
  delayMicroseconds(mydelay);
}

