#include <MsTimer2.h>

int buttonPin = 2;       // Button connected to D2
int blinkLED = 4;        // LED connected to D4
volatile bool ledOn = false; // Flag to indicate LED state

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with pull-up resistor
  pinMode(blinkLED, OUTPUT);       // Set blink LED pin as output
  Serial.begin(9600);              // Start serial communication

  // Attach interrupt to the button pin
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, RISING);

  // Initialize MsTimer2 but don't start it yet
  MsTimer2::set(30, turnOffLED); // Set timer for 5 seconds (5000 ms)
}

void buttonInterrupt() {
  if (!ledOn) { // Only trigger if the LED is off
    Serial.println("Button pressed! LED ON for 5 seconds.");
    digitalWrite(blinkLED, HIGH); // Turn on the LED
    ledOn = true;

    // Start the timer to turn off the LED after 5 seconds
    MsTimer2::start();
  }
}

void turnOffLED() {
  digitalWrite(blinkLED, LOW); // Turn off the LED
  ledOn = false;
  Serial.println("LED OFF after 5 seconds.");

  // Stop the timer to prevent it from running repeatedly
  MsTimer2::stop();
}

void loop() {delay(1000);
  // Main loop can remain empty or handle other tasks
}