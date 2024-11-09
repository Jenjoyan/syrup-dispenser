#include <SoftwareSerial.h>

// Define RX and TX pins for the HC-05 module
const int rxPin = 8;
const int txPin = 9;

// Set up SoftwareSerial on pins 8 (RX) and 9 (TX) for Bluetooth
SoftwareSerial bluetooth(rxPin, txPin);

// Define IR sensor and motor control pins
const int irSensorPin = 2;    // IR sensor input pin
const int motorPin1 = 13;     // Motor control pin 1 (for L293D IN1)
const int motorPin2 = 11;     // Motor control pin 2 (for L293D IN2)
const int enable = 12;

// Calibration constant: Amount of time (ms) the pump needs to run to dispense 1 ml of fluid
const int pumpCalibrationTimePerML = 500; // Adjust this value based on your calibration

void setup() {
  // Initialize pin modes
  pinMode(irSensorPin, INPUT);      // IR sensor pin set as input
  pinMode(motorPin1, OUTPUT);       // Motor pin 1 set as output
  pinMode(motorPin2, OUTPUT);       // Motor pin 2 set as output
  pinMode(enable, OUTPUT);          // Motor enable pin set as output

  // Start serial communications for debugging
  Serial.begin(9600);               // Serial monitor baud rate
  bluetooth.begin(9600);            // Bluetooth module baud rate

  Serial.println("Syrup Dispenser Ready. Waiting for Bluetooth input...");
}

void loop() {
  // Check if there's data available on Bluetooth
  if (bluetooth.available() > 0) {
    String input = bluetooth.readStringUntil('\n'); // Read input from Bluetooth
    int fluidAmountML = input.toInt();              // Convert input to integer (amount in ml)

    if (fluidAmountML > 0) {
      Serial.print("Dispensing ");
      Serial.print(fluidAmountML);
      Serial.println(" ml of fluid.");

      // Wait for the cup to be placed
      while (digitalRead(irSensorPin) == HIGH) {
        Serial.println("Waiting for cup...");
        delay(500);  // Wait half a second before checking again
      }

      Serial.println("Cup detected.");
      delay(2000); // Short delay before dispensing
      Serial.println("Dispensing fluid.");
      dispenseFluid(fluidAmountML); // Call function to dispense fluid

      Serial.println("Dispensing complete. Waiting for next Bluetooth input...");
    } else {
      Serial.println("Invalid input received via Bluetooth. Please send a positive integer.");
    }
  }
}

void dispenseFluid(int amountML) {
  int dispenseTime = amountML * pumpCalibrationTimePerML; // Calculate the dispense time in ms
  
  // Activate the motor to pump fluid in one direction using L293D
  digitalWrite(enable, HIGH);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  delay(dispenseTime); // Run the pump for the calculated time
  
  // Stop the motor (pump)
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(enable, LOW); // Turn off the motor enable pin
}
