import tkinter as tk
from PIL import Image, ImageTk

# Define the rules and their corresponding conditions and conclusions
rules = [
    {
        "number": 1,
        "conditions": [("high_water.png", "Високий рівень води"), ("little_snow.png", "Мало снігу")],
        "conclusion": "Евакуювати"
    },
    {
        "number": 2,
        "conditions": [("high_water.png", "Високий рівень води"), ("high_temp.png", "Висока температура"), ("much_snow.png", "Багато снігу"), ("moderate_rain.png", "Помірний дощ")],
        "conclusion": "Евакуювати"
    },
    {
        "number": 3,
        "conditions": [("high_water.png", "Високий рівень води"), ("moderate_water.png", "Середній рівень води"), ("much_snow.png", "Багато снігу"), ("moderate_rain.png", "Помірний дощ")],
        "conclusion": "Посилити увагу"
    },
    {
        "number": 4,
        "conditions": [("high_water.png", "Високий рівень води"), ("moderate_water.png", "Середній рівень води"), ("much_snow.png", "Багато снігу"), ("no_rain.png", "Немає дощу")],
        "conclusion": "Не турбуватися"
    },
    {
        "number": 5,
        "conditions": [("high_water.png", "Високий рівень води"), ("high_temp.png", "Висока температура"), ("little_snow.png", "Мало снігу"), ("no_rain.png", "Немає дощу")],
        "conclusion": "Не турбуватися"
    },
    {
        "number": 6,
        "conditions": [("moderate_water.png", "Середній рівень води"), ("high_temp.png", "Висока температура"), ("much_snow.png", "Багато снігу"), ("moderate_rain.png", "Помірний дощ")],
        "conclusion": "Посилити увагу"
    },
    {
        "number": 7,
        "conditions": [("moderate_water.png", "Середній рівень води"), ("high_temp.png", "Висока температура"), ("moderate_rain.png", "Помірний дощ"), ("little_snow.png", "Мало снігу")],
        "conclusion": "Не турбуватися"
    },
    {
        "number": 8,
        "conditions": [("moderate_water.png", "Середній рівень води"), ("little_snow.png", "Мало снігу"), ("moderate_rain.png", "Помірний дощ")],
        "conclusion": "Не турбуватися"
    },
    {
        "number": 9,
        "conditions": [("high_water.png", "Високий рівень води"), ("moderate_rain.png", "Помірний дощ")],
        "conclusion": "Не турбуватися"
    }
]

# Initialize the main window
root = tk.Tk()
root.title("Правила")
root.geometry("500x400")  # Increased window size to fit more content
root.resizable(False, False)

# Create a label for the rule number
rule_number_label = tk.Label(root, text="", font=("Arial", 16))
rule_number_label.pack(pady=10)

# Create a frame to hold the conditions
conditions_frame = tk.Frame(root)
conditions_frame.pack()

# Create a label for the conclusion
conclusion_label = tk.Label(root, text="", font=("Arial", 14))
conclusion_label.pack(pady=10)

# Function to update the display with a new rule
def update_rule(rule_index):
    rule = rules[rule_index]
    rule_number_label.config(text=f"Правило {rule['number']}")
    
    # Clear previous conditions
    for widget in conditions_frame.winfo_children():
        widget.destroy()
    
    # Add new conditions with labels
    for condition_image, condition_text in rule['conditions']:
        # Create a frame for each condition (label + image)
        condition_item_frame = tk.Frame(conditions_frame)
        condition_item_frame.pack(side="top", pady=5)
        
        # Load and resize the image
        img = Image.open(f"./icons/{condition_image}")
        img = img.resize((50, 50), Image.LANCZOS)
        img = ImageTk.PhotoImage(img)
        
        # Add the Ukrainian label
        label = tk.Label(condition_item_frame, text=condition_text, font=("Arial", 12), anchor="w")
        label.pack(side="left", padx=10)
        
        # Add the image
        image_label = tk.Label(condition_item_frame, image=img)
        image_label.image = img  # Keep a reference to avoid garbage collection
        image_label.pack(side="left")
    
    # Update the conclusion
    conclusion_label.config(text=rule['conclusion'])
    
    # Schedule the next rule update
    root.after(5000, update_rule, (rule_index + 1) % len(rules))

# Start the cycle with the first rule
update_rule(0)

# Start the main loop
root.mainloop()
