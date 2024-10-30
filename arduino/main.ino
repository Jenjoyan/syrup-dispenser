const int irSensorPin = 2; // IR sensor input pin
const int motorPin1 = 13;   // Motor control pin 1 (for L293D IN1)
const int motorPin2 = 8;   // Motor control pin 2 (for L293D IN2)
const int enable = 12;
const int ready_LED = 4;
const int waiting_LED = 6;

// Calibration constant: Amount of time (ms) the pump needs to run to dispense 1 ml of fluid
const int pumpCalibrationTimePerML = 500; // Adjust this value based on your calibration

void setup() {
  pinMode(irSensorPin, INPUT);      // IR sensor pin set as input
  pinMode(motorPin1, OUTPUT);       // Motor pin 1 set as output
  pinMode(motorPin2, OUTPUT);       // Motor pin 2 set as output
  pinMode(enable, OUTPUT);
  pinMode(ready_LED,OUTPUT);
  pinMode(waiting_LED,OUTPUT);
  Serial.begin(9600);               // Begin serial communication at 9600 baud
  Serial.println("Syrup Dispenser Ready. Please specify the amount of fluid to dispense (in ml):");
  digitalWrite(ready_LED,HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Read user input from serial
    int fluidAmountML = input.toInt();           // Convert input to integer (amount in ml)
    
    if (fluidAmountML > 0) {
      Serial.print("Dispensing ");
      Serial.print(fluidAmountML);
      Serial.println(" ml of fluid.");
      
      // Wait for the cup to be placed
      while (digitalRead(irSensorPin) == HIGH) {
        
        digitalWrite(waiting_LED,HIGH);
        Serial.println("Waiting for cup...");
        delay(500);  // Wait half a second before checking again
      }
      
      Serial.println("Cup detected.");
      delay(2000);
      Serial.println("Dispensing fluid.");
      dispenseFluid(fluidAmountML); // Call function to dispense fluid
      
      Serial.println("Dispensing complete. Please specify the next amount of fluid (in ml):");
    } else {
      Serial.println("Invalid input. Please enter a positive integer for the amount of fluid to dispense (in ml):");
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
}
