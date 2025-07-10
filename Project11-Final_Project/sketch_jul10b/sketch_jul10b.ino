#include <Servo.h>
#include <Arduino_SensorKit.h>

// Pin definitions
#define SERVO_PIN 3
#define FAN_PIN 7

// Create Servo object
Servo servo;

// Variables
float angleX = 0; // Angle from accelerometer

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize servo
  servo.attach(SERVO_PIN);
  servo.write(90); // Start at 90 degrees (neutral position)

  // Initialize fan
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, HIGH); // Start fan

  // Initialize Sensor Kit
  SENSORKIT.init();
}

void loop() {
  // Read accelerometer data
  SENSORKIT.init();
  float accelX = SENSORKIT.getAccelX();
  float accelY = SENSORKIT.getAccelY();
  float accelZ = SENSORKIT.getAccelZ();

  // Calculate angle from accelerometer
  angleX = atan2(accelY, accelZ) * 180 / PI;

  // Map angle to servo range (0° to 180°)
  int servoAngle = map(angleX, -90, 90, 0, 180);
  servo.write(servoAngle); // Update servo angle

  // Debugging
  Serial.print("Angle: ");
  Serial.println(angleX);

  delay(100); // Small delay for stability
}