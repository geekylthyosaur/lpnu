import tkinter as tk
from tkinter import messagebox
from PIL import Image, ImageTk

# Decision matrix from Table 1 in lab2.pdf
decision_matrix = [
    {"water": "high", "temperature": None, "snow": None, "rain": "heavy", "conclusion": "Евакуювати місто"},
    {"water": "high", "temperature": "high", "snow": "much", "rain": None, "conclusion": "Евакуювати місто"},
    {"water": "high", "temperature": None, "snow": "much", "rain": None, "conclusion": "Посиліть увагу"},
    {"water": "high", "temperature": None, "snow": "much", "rain": "moderate", "conclusion": "Не турбуватися"},
    {"water": "high", "temperature": "high", "snow": None, "rain": None, "conclusion": "Не турбуватися"},
    {"water": "moderate", "temperature": "high", "snow": "much", "rain": "heavy", "conclusion": "Посиліть увагу"},
    {"water": "moderate", "temperature": None, "snow": "much", "rain": "heavy", "conclusion": "Не турбуватися"},
    {"water": "moderate", "temperature": None, "snow": None, "rain": "heavy", "conclusion": "Не турбуватися"},
    {"water": "high", "temperature": None, "snow": None, "rain": None, "conclusion": "Не турбуватися"}
]

# Image filenames for different states
image_files = {
    "water": {
        "high": "./icons/high_water.png",
        "moderate": "./icons/moderate_water.png"
    },
    "temperature": {
        "high": "./icons/high_temp.png",
        "moderate": "./icons/moderate_temp.png"
    },
    "snow": {
        "much": "./icons/much_snow.png",
        "little": "./icons/little_snow.png"
    },
    "rain": {
        "heavy": "./icons/heavy_rain.png",
        "moderate": "./icons/moderate_rain.png",
        "none": "./icons/no_rain.png"
    },
    "conclusion": {
        "Евакуювати місто": "./icons/emergency.png",
        "Посиліть увагу": "./icons/alert.png",
        "Не турбуватися": "./icons/calm.png"
    }
}

# Translations for parameter values
translations = {
    "high": "високий",
    "moderate": "помірний",
    "much": "багато",
    "little": "мало",
    "heavy": "сильний",
    "none": "немає"
}

class FloodMonitoringApp:
    def __init__(self, root):
        self.root = root
        self.root.withdraw()  # Hide the root window

        # Initialize parameters
        self.water_level = tk.StringVar(value="moderate")
        self.temperature = tk.StringVar(value="moderate")
        self.snow = tk.StringVar(value="little")
        self.rain = tk.StringVar(value="none")

        # Create main monitoring window
        self.create_monitoring_window()

    def create_monitoring_window(self):
        # Window 1: Monitor the current state of the flood parameters
        self.monitor_window = tk.Toplevel(self.root)
        self.monitor_window.title("Моніторинг параметрів повені")
        self.monitor_window.geometry("400x300")  # Fixed size
        self.monitor_window.resizable(False, False)  # Disable resizing

        # Store references to dynamic widgets
        self.parameter_labels = {}
        self.parameter_images = {}

        # Display current state of parameters with images
        self.display_parameter("Рівень води:", self.water_level.get(), "water", 0)
        self.display_parameter("Температура:", self.temperature.get(), "temperature", 1)
        self.display_parameter("Сніг:", self.snow.get(), "snow", 2)
        self.display_parameter("Дощ:", self.rain.get(), "rain", 3)

        # Button to update parameters
        tk.Button(self.monitor_window, text="Оновити параметри", command=self.create_input_window).grid(row=4, column=0, columnspan=2)

        # Button to check flood risk
        tk.Button(self.monitor_window, text="Перевірити ризик повені", command=self.check_flood_risk).grid(row=5, column=0, columnspan=2)

        # Handle window close event
        self.monitor_window.protocol("WM_DELETE_WINDOW", self.on_close)

    def display_parameter(self, label_text, value, parameter_type, row):
        # Translate the value to Ukrainian
        translated_value = translations.get(value, value)

        # Display parameter label
        if f"label_{parameter_type}" not in self.parameter_labels:
            self.parameter_labels[f"label_{parameter_type}"] = tk.Label(self.monitor_window, text=label_text)
            self.parameter_labels[f"label_{parameter_type}"].grid(row=row, column=0)

        # Display parameter value
        if f"value_{parameter_type}" not in self.parameter_labels:
            self.parameter_labels[f"value_{parameter_type}"] = tk.Label(self.monitor_window, text=translated_value)
            self.parameter_labels[f"value_{parameter_type}"].grid(row=row, column=1)
        else:
            self.parameter_labels[f"value_{parameter_type}"].config(text=translated_value)

        # Display corresponding image
        image_file = image_files[parameter_type][value]
        image = Image.open(image_file)
        image = image.resize((50, 50), Image.LANCZOS)
        photo = ImageTk.PhotoImage(image)

        if f"image_{parameter_type}" not in self.parameter_images:
            self.parameter_images[f"image_{parameter_type}"] = tk.Label(self.monitor_window, image=photo)
            self.parameter_images[f"image_{parameter_type}"].grid(row=row, column=2)
        else:
            self.parameter_images[f"image_{parameter_type}"].config(image=photo)
        self.parameter_images[f"image_{parameter_type}"].image = photo  # Keep a reference to avoid garbage collection

    def create_input_window(self):
        # Window 2: Input or update the state of the flood parameters
        self.input_window = tk.Toplevel(self.root)
        self.input_window.title("Оновлення параметрів повені")
        self.input_window.geometry("300x200")  # Fixed size
        self.input_window.resizable(False, False)  # Disable resizing

        # Water level input
        tk.Label(self.input_window, text="Рівень води:").grid(row=0, column=0)
        tk.OptionMenu(self.input_window, self.water_level, "high", "moderate").grid(row=0, column=1)

        # Temperature input
        tk.Label(self.input_window, text="Температура:").grid(row=1, column=0)
        tk.OptionMenu(self.input_window, self.temperature, "high", "moderate").grid(row=1, column=1)

        # Snow input
        tk.Label(self.input_window, text="Сніг:").grid(row=2, column=0)
        tk.OptionMenu(self.input_window, self.snow, "much", "little").grid(row=2, column=1)

        # Rain input
        tk.Label(self.input_window, text="Дощ:").grid(row=3, column=0)
        tk.OptionMenu(self.input_window, self.rain, "heavy", "moderate", "none").grid(row=3, column=1)

        # Button to save changes
        tk.Button(self.input_window, text="Зберегти", command=self.update_parameters).grid(row=4, column=0, columnspan=2)

    def update_parameters(self):
        # Update parameters dynamically
        self.display_parameter("Рівень води:", self.water_level.get(), "water", 0)
        self.display_parameter("Температура:", self.temperature.get(), "temperature", 1)
        self.display_parameter("Сніг:", self.snow.get(), "snow", 2)
        self.display_parameter("Дощ:", self.rain.get(), "rain", 3)

        # Close the input window
        self.input_window.destroy()

    def check_flood_risk(self):
        # Determine the flood risk based on the decision matrix
        water = self.water_level.get()
        temperature = self.temperature.get()
        snow = self.snow.get()
        rain = self.rain.get()

        conclusion = "Не турбуватися"  # Default conclusion
        for rule in decision_matrix:
            if (rule["water"] == water or rule["water"] is None) and \
               (rule["temperature"] == temperature or rule["temperature"] is None) and \
               (rule["snow"] == snow or rule["snow"] is None) and \
               (rule["rain"] == rain or rule["rain"] is None):
                conclusion = rule["conclusion"]
                break

        # Display the conclusion in Window 3
        self.display_alert(conclusion)

    def display_alert(self, conclusion):
        # Window 3: Display alerts based on the flood risk level
        self.alert_window = tk.Toplevel(self.root)
        self.alert_window.title("Попередження про повінь")
        self.alert_window.geometry("300x200")  # Fixed size
        self.alert_window.resizable(False, False)  # Disable resizing

        # Display the conclusion
        tk.Label(self.alert_window, text=conclusion, font=("Arial", 16)).pack()

        # Load and display the corresponding image
        image_file = image_files["conclusion"][conclusion]
        image = Image.open(image_file)
        image = image.resize((100, 100), Image.LANCZOS)
        photo = ImageTk.PhotoImage(image)
        tk.Label(self.alert_window, image=photo).pack()
        tk.Label(self.alert_window, image=photo).image = photo  # Keep a reference to avoid garbage collection

    def on_close(self):
        # Handle window close event
        self.root.quit()  # Terminate the application

# Run the application
if __name__ == "__main__":
    root = tk.Tk()
    app = FloodMonitoringApp(root)
    root.mainloop()
