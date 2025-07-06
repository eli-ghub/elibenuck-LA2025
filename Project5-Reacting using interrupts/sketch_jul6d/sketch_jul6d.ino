
int button = 6;
int led = 4;

int buttonState;

void setup() {
  pinMode(button, INPUT); // Set pin 2 as an input
  Serial.begin(9600); // Start serial communication

  pinMode(led, OUTPUT);
}

void loop() {
  buttonState = digitalRead(button); // Read the state of pin 2
  if (buttonState == HIGH) {
    
    digitalWrite(led, HIGH); // Turn on the LED
  } else {
    digitalWrite(led, LOW);
  }
}