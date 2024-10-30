import speech_recognition as sr
import re

def extract_dose(text):
    match = re.search(r'(\d+)\s*ml', text.lower())  # Find all numbers in the text
    return int(match.group(1)) if match else None

def main():
    recognizer = sr.Recognizer()
    
    while True:
        with sr.Microphone() as source:
            print("Please specify the dose:")
            try:
                # Adjust the microphone sensitivity
                recognizer.adjust_for_ambient_noise(source, duration=1)
                print("Listening...")
                audio_data = recognizer.listen(source, timeout=5)  # Set a timeout for listening
                print("Audio recorded, processing...")
                dose_text = recognizer.recognize_google(audio_data)
                print("You said:", dose_text)

                dose_amount = extract_dose(dose_text)
                if dose_amount is not None:
                    print(f"Dose amount detected: {dose_amount} ml")
                    break  # Exit loop if dose is detected
                else:
                    print("No valid dose amount found. Please try again.")

            except sr.UnknownValueError:
                print("Sorry, I couldn't understand the audio. Please try again.")
            except sr.RequestError as e:
                print(f"Could not request results from Google Speech Recognition service: {e}")
            except Exception as e:
                print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
