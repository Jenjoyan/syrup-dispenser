# Automatic Syrup Dispenser with Voice Control

## Project Overview
This project assists elderly individuals with administering liquid medications by automatically dispensing precise doses. Designed for ease of use, the dispenser takes voice commands to specify the desired dose, making it highly accessible.

## Key Features

- **Voice-Controlled Dosage**: Uses the system microphone to capture voice commands for specifying the dosage amount.
- **Precision Dispensing**: A peristaltic pump accurately dispenses liquid medication based on the specified dose.
- **Cup Detection**: An IR sensor ensures a cup is in place before dispensing to prevent spillage.
- **Bluetooth Connectivity**:
  - **HC-05 Bluetooth Module**: Receives dosage information from Python code and transmits it to the Arduino controlling the pump. The Bluetooth communication operates on COM3.

## Project Components

1. **Hardware**
   - Peristaltic Pump for accurate dispensing
   - IR Sensor for cup detection
   - HC-05 Bluetooth Module (COM3 for communication)
   - Arduino for processing and pump control

2. **Software**
   - Python (Voice recognition to capture dosage instructions)
   - Arduino Code (Controls the peristaltic pump and Bluetooth communication)

## How It Works
1. **User Input**: The user specifies the dosage using voice commands, which are processed through Python.
2. **Data Transmission**: The specified dosage is sent from Python to the Arduino via Bluetooth.
3. **Dispensing**: The Arduino activates the peristaltic pump to dispense the set amount after verifying the presence of a cup.

## Installation and Setup
- Set up the Python environment for voice recognition.
- Configure the Arduino with the necessary libraries for Bluetooth communication.

## Usage
1. Power on the dispenser.
2. Specify the desired dose using a voice command.
3. The dispenser will automatically dispense the exact dose once it detects a cup.
