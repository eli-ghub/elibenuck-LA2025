const int fanPin = 7;       // PWM pin to control fan speed
const int lightSensorPin = A6; // Analog pin for light sensor
const int rotarySensorPin = A0; // Analog pin for rotary angle sensor
unsigned long lastTime = 0; // Last time RPM was calculated
int fanSpeed = 0;           // Fan speed in RPM
int lightThreshold = 500;   // Threshold for detecting fan blade (adjust based on your setup)
volatile int bladeCount = 0; // Count of fan blade passes

void setup() {
  pinMode(fanPin, OUTPUT);
  pinMode(lightSensorPin, INPUT);
  pinMode(rotarySensorPin, INPUT);
  Serial.begin(9600); // Start serial communication
}

void loop() {
  // Read the rotary angle sensor to set fan speed
  int rotaryValue = analogRead(rotarySensorPin);
  int pwmValue = map(rotaryValue, 0, 1023, 0, 255); // Map rotary value to PWM range
  analogWrite(fanPin, pwmValue);

  // Measure fan speed using the light sensor
  int lightValue = analogRead(lightSensorPin);
  if (lightValue < lightThreshold) { // Detect fan blade passing
    bladeCount++;
    delay(10); // Debounce to avoid multiple counts for the same blade
  }

  // Calculate RPM every second
  if (millis() - lastTime >= 1000) {
    fanSpeed = (bladeCount * 60) / 2; // Calculate RPM (2 blades per revolution)
    bladeCount = 0; // Reset blade count
    lastTime = millis();

    // Send RPM to the computer
    Serial.println(fanSpeed);
  }
}