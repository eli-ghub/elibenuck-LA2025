import serial
import FreeSimpleGUI as sg
import threading

# Initialize serial communication
arduino = serial.Serial('COM4', 9600, timeout=1)  # Replace 'COM3' with your Arduino's port

# Function to continuously read from the serial port
def read_from_serial(window):
    while True:
        if arduino.in_waiting > 0:
            data = arduino.readline().decode('utf-8').strip()
            if data == "0":
                window['output'].update("LED OFF")
            elif data == "1":
                window['output'].update("Button Pressed, LED ON")
            elif data == "2":
                window['output'].update("Button Released, LED OFF")

# GUI layout
layout = [
    [sg.Text("Enter LED ON time (ms):"), sg.Input(key='input', size=(10, 1))],
    [sg.Button("Send"), sg.Button("Exit")],
    [sg.Text("Status:"), sg.Text("", key='output', size=(30, 1))]
]

# Create the window
window = sg.Window("Arduino LED Controller", layout)

# Start the serial reading thread
thread = threading.Thread(target=read_from_serial, args=(window,), daemon=True)
thread.start()

# Event loop
while True:
    event, values = window.read()
    if event == sg.WINDOW_CLOSED or event == "Exit":
        break
    if event == "Send":
        led_time = values['input']
        if led_time.isdigit():
            arduino.write((led_time + '\n').encode('utf-8'))  # Send the LED ON time to Arduino
            window['output'].update(f"Sent {led_time} ms to Arduino")
        else:
            window['output'].update("Invalid input. Please enter a number.")

# Close the window and serial connection
window.close()
arduino.close()