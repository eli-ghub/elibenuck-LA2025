int buttonPin = 2;
int buttonLED = 6;
int blinkLED = 4;
volatile bool buttonPressed = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonLED, OUTPUT);
  pinMode(blinkLED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, CHANGE);
}

void buttonInterrupt() {
  buttonPressed = true;
}



void loop() {
  digitalWrite(blinkLED, HIGH);



  if (buttonPressed) {
    buttonPressed = false;
    digitalWrite(blinkLED, LOW); // Toggle LED state
  }

}