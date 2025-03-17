import tkinter as tk
from PIL import Image, ImageTk
import threading
import time

class ImageWindow:
    def __init__(self, root, image_path, text, seconds):
        self.root = root
        self.image_path = image_path
        self.text = text
        self.seconds = seconds

        self.window = tk.Toplevel(root)
        self.window.title("Увага!")

        # Завантаження та обрізання зображення до однакових розмірів
        self.image = Image.open(image_path)
        self.image = self.image.resize((300, 300), Image.LANCZOS)
        self.photo = ImageTk.PhotoImage(self.image)

        # Відображення зображення
        self.image_label = tk.Label(self.window, image=self.photo)
        self.image_label.pack()

        # Відображення тексту
        self.text_label = tk.Label(self.window, text=self.text, font=("Arial", 14))
        self.text_label.pack()

        # Відображення зворотного відліку
        self.countdown_label = tk.Label(self.window, text=str(self.seconds), font=("Arial", 16))
        self.countdown_label.pack()

        # Запуск зворотного відліку
        self.start_countdown()

    def start_countdown(self):
        def update_countdown():
            for i in range(self.seconds, 0, -1):
                self.countdown_label.config(text=str(i))
                self.window.update()
                time.sleep(1)
            self.window.destroy()

        threading.Thread(target=update_countdown).start()

def open_windows(root, items):
    for item in items:
        image_path, text, seconds, wait_time = item

        # Чекаємо вказаний час перед відкриттям вікна
        time.sleep(wait_time)

        # Відкриваємо вікно
        window = ImageWindow(root, image_path, text, seconds)

        # Чекаємо, поки вікно закриється
        while window.window.winfo_exists():
            time.sleep(0.1)

if __name__ == "__main__":
    # Приклад списку з даними
    items = [
        ("icons/small_fire.png", "Виявлено займання", 5, 5),
        ("icons/smoke_fire.png", "Сильне задимлення", 5, 5),
        ("icons/house_fire.png", "Обширне займання", 5, 5),
    ]

    root = tk.Tk()
    # root.withdraw()  # Приховуємо головне вікно

    # Запускаємо відкриття вікон в окремому потоці
    threading.Thread(target=open_windows, args=(root, items)).start()

    root.mainloop()
