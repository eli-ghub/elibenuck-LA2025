
int button = 6;
int led = 4;

int buttonState;

void setup() {
  pinMode(button, INPUT); // Set pin 2 as an input
  Serial.begin(9600); // Start serial communication

  pinMode(led, OUTPUT);
}

void loop() {
  for (int i = 0; i < 10000; i++) {
    Serial.println("calculating...");}
    
    buttonState = digitalRead(button); // Read the state of pin 2

    if (buttonState == HIGH) {
      Serial.println("on!");
      digitalWrite(led, HIGH); // Turn on the LED
    } else {
      Serial.println("off!");
      digitalWrite(led, LOW);
    }
  
}