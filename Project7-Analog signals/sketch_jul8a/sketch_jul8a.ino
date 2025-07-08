#include <MD_PWM.h>

int PWM_FREQ = 300; // Set PWM frequency
int rotaryPin = A0; // Rotary encoder connected to A0
MD_PWM pwm[] = { MD_PWM(4) }; // Create an MD_PWM object for pin 4

void setup() {
  Serial.begin(9600); // Start serial communication
  pwm[0].begin(PWM_FREQ); // Initialize PWM on pin 4
  Serial.println("PWM enabled on pin 4. Adjust using rotary encoder.");
}

void loop() {
  // Read the rotary value (0-1023)
  int rotaryValue = analogRead(rotaryPin);

  // Map the rotary value to the PWM range (0-255)
  int pwmValue = map(rotaryValue, 0, 1023, 0, 255);

  // Write the mapped value to the PWM pin
  pwm[0].write(pwmValue);

  // Print the rotary and PWM values for debugging
  Serial.print("Rotary Value: ");
  Serial.print(rotaryValue);
  Serial.print(" -> PWM Value: ");
  Serial.println(pwmValue);

  delay(50); // Small delay for stability
}