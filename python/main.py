import speech_recognition as sr
import re
import serial
import time

# Configure the serial connection (replace 'COM7' with your port if necessary)
bluetooth_serial = serial.Serial('COM7', 9600)  # 9600 is the default baud rate for HC-05
time.sleep(2)  # Give some time to establish the connection

def extract_dose(text):
    match = re.search(r'(\d+)', text)  # Find any numbers in the text
    return int(match.group(1)) if match else None

def main():
    recognizer = sr.Recognizer()
    failed_attempts = 0  # Counter for failed attempts

    while True:
        if failed_attempts < 3:
            with sr.Microphone() as source:
                print("Please specify the dose:")
                try:
                    # Adjust microphone sensitivity to ambient noise
                    recognizer.adjust_for_ambient_noise(source, duration=1)
                    print("Listening...")
                    audio_data = recognizer.listen(source, timeout=5)  # Timeout for listening
                    print("Audio recorded, processing...")
                    
                    # Recognize speech using Google Speech Recognition
                    dose_text = recognizer.recognize_google(audio_data)
                    print("You said:", dose_text)

                    # Extract the dose amount from the recognized text
                    dose_amount = extract_dose(dose_text)
                    if dose_amount is not None:
                        print(f"Dose amount detected: {dose_amount} ml")
                        # Convert dose amount to string, encode, and send it over Bluetooth
                        bluetooth_serial.write(f"{dose_amount}\n".encode())
                        print(f"Sent via Bluetooth: {dose_amount} ml")
                        break  # Exit the loop if dose is successfully detected
                    else:
                        print("No valid dose amount found. Please try again.")
                        failed_attempts += 1

                except sr.UnknownValueError:
                    print("Sorry, I couldn't understand the audio. Please try again.")
                    failed_attempts += 1
                except sr.RequestError as e:
                    print(f"Could not request results from Google Speech Recognition service: {e}")
                    failed_attempts += 1
                except Exception as e:
                    print(f"An error occurred: {e}")
                    failed_attempts += 1
        else:
            # After 3 failed attempts, ask the user to enter the dose manually
            try:
                dose_amount = int(input("Please enter the dose amount manually in ml: "))
                if dose_amount > 0:
                    bluetooth_serial.write(f"{dose_amount}\n".encode())
                    print(f"Sent via Bluetooth: {dose_amount} ml")
                    break
                else:
                    print("Please enter a positive integer for the dose.")
            except ValueError:
                print("Invalid input. Please enter a valid integer.")

    # Close the Bluetooth serial connection when done
    bluetooth_serial.close()
    print("Bluetooth connection closed.")

if __name__ == "__main__":
    main()
