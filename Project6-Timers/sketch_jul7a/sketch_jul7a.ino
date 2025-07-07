int buttonPin = 2;
int buttonLED = 6;
int blinkLED = 4;
int startTime = 0;
volatile bool ledOn = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonLED, OUTPUT);
  pinMode(blinkLED, OUTPUT);
  Serial.begin(9600);   
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, RISING);
}

void buttonInterrupt() {
 
  Serial.println("Interrupt triggered!");
    digitalWrite(blinkLED, HIGH);
    ledOn = true;
    startTime = millis();
    

}

void loop() {
    for (int i = 0; i < 10000; i++) {
    Serial.println("calculating...");}
  if (ledOn) {
    // Keep the LED on
    if (millis() - startTime > 5000) {
      digitalWrite(blinkLED, LOW);
      ledOn = false;
    }
  }
}
