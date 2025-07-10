import tkinter as tk
from tkinter import messagebox
import serial
import csv
import threading
import time

# Serial port configuration
SERIAL_PORT = "COM4"  # Replace with your Arduino's COM port
BAUD_RATE = 9600

class FanSpeedApp:
    def __init__(self, master):
        self.master = master
        self.master.title("Fan Speed Controller")
        
        # Initialize serial connection
        try:
            self.arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        except Exception as e:
            messagebox.showerror("Error", f"Could not connect to Arduino: {e}")
            self.master.destroy()
            return
        
        # GUI elements
        self.speed_label = tk.Label(master, text="Fan Speed: 0 RPM", font=("Arial", 14))
        self.speed_label.pack(pady=10)
        
        self.log_button = tk.Button(master, text="Start Logging", command=self.start_logging, font=("Arial", 12))
        self.log_button.pack(pady=10)
        
        self.stop_button = tk.Button(master, text="Stop Logging", command=self.stop_logging, font=("Arial", 12), state=tk.DISABLED)
        self.stop_button.pack(pady=10)
        
        self.logging = True
        self.log_file = open("fan_speed_log.csv", "w", newline="")
        self.csv_writer = csv.writer(self.log_file)
        self.csv_writer.writerow(["Timestamp", "Fan Speed (RPM)"])
        
        # Start reading fan speed
        self.read_thread = threading.Thread(target=self.read_fan_speed, daemon=True)
        self.read_thread.start()

    def read_fan_speed(self):
        while True:
            try:
                if self.arduino.in_waiting > 0:
                    speed = self.arduino.readline().decode().strip()
                    print(f"Received speed: {speed}")  # Debug: Print received data
                    if speed.isdigit():
                        self.speed_label.config(text=f"Fan Speed: {speed} RPM")
                        print(f"GUI updated with speed: {speed}")  # Debug
                        if self.logging:
                            self.csv_writer.writerow([time.strftime("%Y-%m-%d %H:%M:%S"), speed])
                            print(f"Logged speed: {speed}")  # Debug
            except Exception as e:
                print(f"Error reading fan speed: {e}")

    def start_logging(self):
        self.logging = True
        print("Logging started")  # Debug
        self.log_button.config(state=tk.DISABLED)
        self.stop_button.config(state=tk.NORMAL)

    def stop_logging(self):
        self.logging = False
        print("Logging stopped")  # Debug
        self.log_button.config(state=tk.NORMAL)
        self.stop_button.config(state=tk.DISABLED)

    def close(self):
        self.logging = False
        self.log_file.close()
        self.arduino.close()
        self.master.destroy()

# Main application
if __name__ == "__main__":
    root = tk.Tk()
    app = FanSpeedApp(root)
    root.protocol("WM_DELETE_WINDOW", app.close)
    root.mainloop()