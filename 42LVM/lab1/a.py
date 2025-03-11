import tkinter as tk
from tkinter import messagebox
from PIL import Image, ImageTk
import random

# List of local image filenames
IMAGE_FILES = {
    "пожежа": "fire.png",          # Replace with actual filenames
    "витік_газу": "gas_leak.png",
    "замикання": "short_circuit.png",
    "alert_icon": "alert_icon.png",
    "ok": "ok.png",
}

# Function to load and resize images from local files
def load_image(filename, size=(32, 32)):
    try:
        image = Image.open(filename)
        image = image.resize(size, Image.LANCZOS)  # Resize the image
        return ImageTk.PhotoImage(image)
    except Exception as e:
        print(f"Failed to load or resize image {filename}: {e}")
        return None

class MonitoringWindow(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Моніторинг загроз")
        self.geometry("500x350")  # Increased height to accommodate the new button
        self.configure(bg="#CCCCCC")  # Background color from the image

        # Load and resize images from local files
        self.images = {}
        for key, filename in IMAGE_FILES.items():
            self.images[key] = load_image(filename, size=(32, 32))  # Resize to 32x32 pixels

        # Create UI elements
        self.status_labels = []
        self.icon_labels = []
        for i in range(3):
            frame = tk.Frame(self, bg="#CCCCCC")
            frame.pack(fill=tk.X, padx=10, pady=10)
            
            # Workshop icon
            icon_label = tk.Label(frame, image=self.images["ok"], bg="#CCCCCC")
            icon_label.pack(side=tk.LEFT, padx=10)
            self.icon_labels.append(icon_label)
            
            # Workshop status
            label = tk.Label(frame, text=f"Цех {i+1}: Немає загрози", width=30, bg="#CCCCCC", fg="#000000")
            label.pack(side=tk.LEFT, padx=10)
            self.status_labels.append(label)
            
            # Change status button
            button = tk.Button(frame, text="Змінити", command=lambda i=i: self.report_threat(i), bg="#0051CC", fg="#FFFFFF")
            button.pack(side=tk.RIGHT, padx=10)
        
        # Button to create or remove random alert
        self.random_alert_button = tk.Button(self, text="Створити/Видалити випадкову загрозу", command=self.toggle_random_alert, bg="#0051CC", fg="#FFFFFF")
        self.random_alert_button.pack(side=tk.BOTTOM, pady=10)
    
    def report_threat(self, workshop_id):
        ReportWindow(self, workshop_id)
    
    def update_status(self, workshop_id, threat, cancel):
        status_text = "Немає загрози" if cancel else f"Загроза: {threat}"
        self.status_labels[workshop_id].config(text=f"Цех {workshop_id+1}: {status_text}")
        
        # Update the icon based on the alert status
        if cancel:
            self.icon_labels[workshop_id].config(image=self.images["ok"])
        else:
            self.icon_labels[workshop_id].config(image=self.images[threat.lower().replace(" ", "_")])
        
        AlertWindow(workshop_id, threat, cancel, self.images["ok"] if cancel else self.images["alert_icon"])

    def toggle_random_alert(self):
        # Randomly select a workshop and a threat type
        workshop_id = random.randint(0, 2)  # Random workshop (0, 1, or 2)
        threat = random.choice(["Пожежа", "Витік газу", "Замикання"])  # Random threat
        
        # Check if the selected workshop already has an alert
        current_status = self.status_labels[workshop_id].cget("text")
        if "Загроза" in current_status:
            # If there's already an alert, remove it
            self.update_status(workshop_id, threat, cancel=True)
        else:
            # If there's no alert, create one
            self.update_status(workshop_id, threat, cancel=False)

class ReportWindow(tk.Toplevel):
    def __init__(self, master, workshop_id):
        super().__init__(master)
        self.master = master
        self.workshop_id = workshop_id
        self.title("Повідомлення про загрозу")
        self.geometry("400x200")
        self.configure(bg="#CCCCCC")

        tk.Label(self, text="Оберіть загрозу:", bg="#CCCCCC", fg="#000000").pack(pady=10)
        
        self.threat_var = tk.StringVar()
        self.threat_var.set("Пожежа")
        threats = ["Пожежа", "Витік газу", "Замикання"]
        tk.OptionMenu(self, self.threat_var, *threats).pack(pady=10)
        
        tk.Button(self, text="Підтвердити", command=self.confirm_threat, bg="#0051CC", fg="#FFFFFF").pack(pady=5)
        tk.Button(self, text="Відбій", command=self.cancel_threat, bg="#FF0000", fg="#FFFFFF").pack(pady=5)
    
    def confirm_threat(self):
        self.master.update_status(self.workshop_id, self.threat_var.get(), cancel=False)
        self.destroy()
    
    def cancel_threat(self):
        self.master.update_status(self.workshop_id, self.threat_var.get(), cancel=True)
        self.destroy()

class AlertWindow(tk.Toplevel):
    def __init__(self, workshop_id, threat, cancel, alert_icon):
        super().__init__()
        self.title("Оповіщення")
        self.geometry("400x200")
        self.configure(bg="#CCCCCC")

        message = f"Відбій загрози в цеху {workshop_id+1}" if cancel else f"Загроза {threat} в цеху {workshop_id+1}!"
        tk.Label(self, text=message, fg="#FF0000" if not cancel else "#00CC00", bg="#CCCCCC").pack(pady=20)
        
        icon_label = tk.Label(self, image=alert_icon, bg="#CCCCCC")
        icon_label.pack(pady=10)
        
        tk.Button(self, text="OK", command=self.destroy, bg="#0051CC", fg="#FFFFFF").pack(pady=10)
        
if __name__ == "__main__":
    app = MonitoringWindow()
    app.mainloop()
