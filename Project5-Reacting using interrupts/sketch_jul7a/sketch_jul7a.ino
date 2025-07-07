int buttonPin = 6;       // Button connected to D6
int interruptPin = 2;    // Interrupt pin connected to D2
int led = 4;             // LED connected to D4
int i;
volatile bool interruptFlag = false; // Flag to signal interrupt

void handleInterrupt() {
    interruptFlag = true; // Set the flag when interrupt occurs
}

void setup() {
    pinMode(buttonPin, INPUT); // Set button pin as input with pull-up resistor
    pinMode(interruptPin, INPUT); // Set interrupt pin as input with internal pull-up resistor
    pinMode(led, OUTPUT);              // Set LED pin as output
    Serial.begin(9600);                // Start serial communication

    // Attach interrupt to the interrupt pin
    attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
}

void loop() {
    i = i+1;
    Serial.println(i);
    if (interruptFlag) {
    interruptFlag = false; // Reset the flag
        Serial.println("Interrupt triggered!");
        digitalWrite(led, HIGH); // Turn on the LED
        delay(500);             // Keep LED on for a short time
    } else{digitalWrite(led, LOW); }
}



