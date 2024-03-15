// Include the necessary libraries
#include <TimerOne.h>

// Define the analog pin for the LM35 temperature sensor
const int lm35Pin = A0;

// Define the onboard LED pin
const int ledPin = 13;

// Define temperature thresholds
const int lowerThreshold = 30;
const int upperThreshold = 30;

// Define variables to store temperature readings
float temperature = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Initialize Timer1
  Timer1.initialize(1000000); // Timer1 callback function will be called every 1 second
  Timer1.attachInterrupt(timerCallback); // Attach the callback function
}

void loop() {
  // Read the analog value from the LM35 temperature sensor
  float sensorValue = analogRead(lm35Pin);
  
  // Convert the analog value to temperature in degrees Celsius
  temperature = (sensorValue * 500) / 1023;

  // Print the temperature to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Check temperature thresholds and set LED blinking delay accordingly
  if (temperature < lowerThreshold) {
    Timer1.setPeriod(250000); // Set LED blinking interval to 250 milliseconds
  } else if (temperature > upperThreshold) {
    Timer1.setPeriod(500000); // Set LED blinking interval to 500 milliseconds
  }
}

void timerCallback() {
  // Toggle the LED state
  digitalWrite(ledPin, !digitalRead(ledPin));
}
