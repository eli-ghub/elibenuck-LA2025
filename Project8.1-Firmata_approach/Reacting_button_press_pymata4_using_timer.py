import tkinter as tk
from tkinter import messagebox
from pymata4 import pymata4
from threading import Timer
import time

# Arduino setup
LED_PIN = 4  # Pin for LED
BUTTON_PIN = 2  # Pin for button

class ArduinoApp:
    def __init__(self, master):
        self.master = master
        self.master.title("Arduino Button Press GUI")
        
        # Initialize pymata4
        self.board = pymata4.Pymata4()
        self.board.set_pin_mode_digital_input_pullup(BUTTON_PIN, callback=self.button_callback)
        self.board.set_pin_mode_digital_output(LED_PIN)
        
        # GUI elements
        self.label = tk.Label(master, text="Button State: Not Pressed", font=("Arial", 14))
        self.label.pack(pady=10)
        
        self.timer_label = tk.Label(master, text="Set Timer Interval (ms):", font=("Arial", 12))
        self.timer_label.pack(pady=5)
        
        self.timer_entry = tk.Entry(master, font=("Arial", 12))
        self.timer_entry.pack(pady=5)
        self.timer_entry.insert(0, "30")  # Default to 30 ms
        
        self.set_button = tk.Button(master, text="Set Timer", command=self.set_timer, font=("Arial", 12))
        self.set_button.pack(pady=10)
        
        self.timer_interval = 0.03  # Default timer interval in seconds
        self.button_pressed = False

    def button_callback(self, data):
        if data[2] == 0:  # Button pressed
            self.button_pressed = True
            self.label.config(text="Button State: Not Pressed")
            self.turn_on_led()  # Turn on the LED immediately
        else:  # Button released
            self.button_pressed = False
            self.label.config(text="Button State: Pressed")

    def turn_on_led(self):
        self.board.digital_write(LED_PIN, 1)
        Timer(self.timer_interval, self.turn_off_led).start()

    def turn_off_led(self):
        self.board.digital_write(LED_PIN, 0)

    def set_timer(self):
        try:
            interval_ms = int(self.timer_entry.get())
            if interval_ms <= 0:
                raise ValueError("Interval must be positive.")
            self.timer_interval = interval_ms / 1000.0
            messagebox.showinfo("Success", f"Timer interval set to {interval_ms} ms.")
        except ValueError as e:
            messagebox.showerror("Error", f"Invalid input: {e}")

    def close(self):
        self.board.shutdown()
        self.master.destroy()

# Main application
if __name__ == "__main__":
    root = tk.Tk()
    app = ArduinoApp(root)
    root.protocol("WM_DELETE_WINDOW", app.close)
    root.mainloop()