#include <MsTimer2.h>

const int buttonPin = 2; // Button connected to pin 2 (interrupt pin)
const int ledPin = 4;   // LED connected to pin 13
volatile bool buttonPressed = false; // Flag to track button state
volatile bool ledOn = false;         // Flag to track LED state
int ledOnTime = 1000;                // Default LED ON time in milliseconds

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with pull-up resistor
  pinMode(ledPin, OUTPUT);         // Set LED pin as output
  Serial.begin(9600);              // Start serial communication

  // Attach interrupt to the button pin
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING);

  // Initialize MsTimer2 but dont start it yet
  MsTimer2::set(ledOnTime, turnOffLED);
}

void loop() {
  // Check for incoming serial data
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Read input until newline
    ledOnTime = input.toInt();                  // Convert input to integer
    Serial.print("I received: ");
    Serial.println(ledOnTime);

    // Update the timer with the new LED ON time
    MsTimer2::set(ledOnTime + 1, turnOffLED); // Add ms to account for bug
  }

  // Send LED state to the serial port
  if (ledOn) {
    Serial.println("1"); // LED ON
  } else if (buttonPressed) {
    Serial.println("2"); // Button pressed but LED OFF
  } else {
    Serial.println("0"); // LED OFF
  }

  delay(100); // Small delay to avoid flooding the serial port
}

void buttonInterrupt() {
  if (!ledOn) { // Only trigger if the LED is off
    buttonPressed = true;
    ledOn = true;
    digitalWrite(ledPin, HIGH); // Turn on the LED
    MsTimer2::start();          // Start the timer
  }
}

void turnOffLED() {
  digitalWrite(ledPin, LOW); // Turn off the LED
  ledOn = false;
  buttonPressed = false;
  MsTimer2::stop();          // Stop the timer
}