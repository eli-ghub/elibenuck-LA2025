const int fanPin = 7;       // PWM pin to control fan speed
const int lightSensorPin = A6; // Analog pin for light sensor
const int rotarySensorPin = A0; // Analog pin for rotary angle sensor
unsigned long lastTime = 0; // Last time RPM was calculated
int fanSpeed = 0;           // Fan speed in RPM
int lightThreshold = 350;   // Threshold for detecting fan blade (adjust based on your setup)
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
  //Serial.println(lightValue);
  if (lightValue < lightThreshold) { // Detect fan blade passing
    bladeCount++;
    delay(10); // Debounce to avoid multiple counts for the same blade
    Serial.println(bladeCount);
  }

}