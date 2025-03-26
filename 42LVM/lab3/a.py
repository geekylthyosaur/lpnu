import tkinter as tk
from tkinter import ttk, messagebox
from PIL import Image, ImageTk
import math
import os

class Transport:
    def __init__(self, name, capacity, min_units, max_units, image_path):
        self.name = name
        self.capacity = capacity
        self.min_units = min_units
        self.max_units = max_units
        self.image_path = image_path
        self.used_units = 0
        self.image = None

class EvacuationApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Система планування евакуації")
        
        # Шляхи до зображень транспорту
        self.image_paths = {
            "Mercedes Sprinter": "images/sprinter.png",
            "БАЗ «Волошка»": "images/voloshka.png",
            "«Богдан» А-064": "images/bogdan_a064.png",
            "AeroLAZ": "images/aerolaz.png",
            "«Богдан» А-069": "images/bogdan_a069.png",
            "«Богдан» А-091": "images/bogdan_a091.png",
            "ЗАЗ A10C I-Bан": "images/zaz_a10c.png"
        }
        
        # Початкові дані про транспорт
        self.initial_transports = [
            {"name": "Mercedes Sprinter", "capacity": 12, "max_units": 12},
            {"name": "БАЗ «Волошка»", "capacity": 15, "max_units": 5},
            {"name": "«Богдан» А-064", "capacity": 17, "max_units": 6},
            {"name": "AeroLAZ", "capacity": 17, "max_units": 8},
            {"name": "«Богдан» А-069", "capacity": 18, "max_units": 2},
            {"name": "«Богдан» А-091", "capacity": 21, "max_units": 5},
            {"name": "ЗАЗ A10C I-Bан", "capacity": 23, "max_units": 2}
        ]
        
        # Ініціалізація транспорту
        self.transports = []
        self.initialize_transports()
        
        # Завантаження зображень
        self.load_transport_images()
        
        # Прапорець для відстеження виконання розрахунків
        self.calculations_done = False
        
        # Основний інтерфейс
        self.create_main_interface()
        
    def initialize_transports(self):
        """Ініціалізує список транспорту з початковими даними"""
        self.transports = []
        for item in self.initial_transports:
            self.transports.append(
                Transport(
                    name=item["name"],
                    capacity=item["capacity"],
                    min_units=0,
                    max_units=item["max_units"],
                    image_path=self.image_paths[item["name"]]
                )
            )
    
    def load_transport_images(self):
        """Завантажує зображення транспорту"""
        for transport in self.transports:
            try:
                if os.path.exists(transport.image_path):
                    img = Image.open(transport.image_path)
                    img = img.resize((150, 100), Image.Resampling.LANCZOS)
                    transport.image = ImageTk.PhotoImage(img)
                else:
                    transport.image = None
            except Exception as e:
                print(f"Помилка завантаження зображення {transport.image_path}: {e}")
                transport.image = None
    
    def create_main_interface(self):
        """Створює основний інтерфейс програми"""
        # Фрейм для введення даних
        input_frame = ttk.LabelFrame(self.root, text="Введіть дані для евакуації")
        input_frame.pack(padx=10, pady=10, fill="x")
        
        # Поле для введення кількості людей
        ttk.Label(input_frame, text="Кількість людей для евакуації:").grid(row=0, column=0, padx=5, pady=5)
        self.people_entry = ttk.Entry(input_frame)
        self.people_entry.grid(row=0, column=1, padx=5, pady=5)
        
        # Кнопка розрахунку
        calculate_btn = ttk.Button(input_frame, text="Розрахувати", command=self.calculate_transport)
        calculate_btn.grid(row=0, column=2, padx=5, pady=5)
        
        # Фрейм для відображення результатів
        self.result_frame = ttk.LabelFrame(self.root, text="Результати розподілу транспорту")
        self.result_frame.pack(padx=10, pady=10, fill="both", expand=True)
        
        # Фрейм для кнопок управління
        self.control_frame = ttk.Frame(self.root)
        self.control_frame.pack(padx=10, pady=10, fill="x")
        
        # Кнопка для відображення деталей (спочатку прихована)
        self.details_btn = ttk.Button(self.control_frame, text="Показати деталі", 
                                    command=self.show_details, state="disabled")
        self.details_btn.pack(side="left", padx=5)
        
        # Кнопка конфігурації автопарку
        config_btn = ttk.Button(self.control_frame, text="Налаштування автопарку", 
                              command=self.show_config_window)
        config_btn.pack(side="left", padx=5)
        
        # Кнопка виходу
        exit_btn = ttk.Button(self.control_frame, text="Вихід", command=self.root.quit)
        exit_btn.pack(side="right", padx=5)
    
    def show_config_window(self):
        """Показує вікно конфігурації автопарку"""
        config_window = tk.Toplevel(self.root)
        config_window.title("Налаштування автопарку")
        config_window.geometry("600x400")
        
        # Фрейм для таблиці транспорту
        table_frame = ttk.Frame(config_window)
        table_frame.pack(padx=10, pady=10, fill="both", expand=True)
        
        # Створення Treeview для відображення транспорту
        columns = ("Тип транспорту", "Місткість", "Доступна кількість")
        self.config_tree = ttk.Treeview(table_frame, columns=columns, show="headings")
        
        for col in columns:
            self.config_tree.heading(col, text=col)
            self.config_tree.column(col, width=150, anchor="center")
        
        # Додавання даних про транспорт
        for t in self.transports:
            self.config_tree.insert("", "end", values=(t.name, t.capacity, t.max_units))
        
        # Додавання Scrollbar
        scrollbar = ttk.Scrollbar(table_frame, orient="vertical", command=self.config_tree.yview)
        self.config_tree.configure(yscrollcommand=scrollbar.set)
        
        self.config_tree.pack(side="left", fill="both", expand=True)
        scrollbar.pack(side="right", fill="y")
        
        # Фрейм для кнопок редагування
        edit_frame = ttk.Frame(config_window)
        edit_frame.pack(padx=10, pady=5, fill="x")
        
        # Поля для редагування
        ttk.Label(edit_frame, text="Нова кількість:").pack(side="left", padx=5)
        self.new_quantity_entry = ttk.Entry(edit_frame, width=10)
        self.new_quantity_entry.pack(side="left", padx=5)
        
        # Кнопка оновлення
        update_btn = ttk.Button(edit_frame, text="Оновити", 
                              command=lambda: self.update_transport_quantity(config_window))
        update_btn.pack(side="left", padx=5)
        
        # Кнопка закриття
        close_btn = ttk.Button(edit_frame, text="Закрити", command=config_window.destroy)
        close_btn.pack(side="right", padx=5)
    
    def update_transport_quantity(self, config_window):
        """Оновлює кількість транспорту в автопарку"""
        selected_item = self.config_tree.selection()
        if not selected_item:
            messagebox.showwarning("Увага", "Будь ласка, виберіть тип транспорту для оновлення")
            return
        
        try:
            new_quantity = int(self.new_quantity_entry.get())
            if new_quantity < 0:
                raise ValueError("Кількість не може бути від'ємною")
            
            # Оновлення даних у списку транспорту
            item_values = self.config_tree.item(selected_item, "values")
            transport_name = item_values[0]
            
            for t in self.transports:
                if t.name == transport_name:
                    t.max_units = new_quantity  # Виправлено помилку (було new_units)
                    break
            
            # Оновлення Treeview
            self.config_tree.item(selected_item, values=(item_values[0], item_values[1], new_quantity))
            
            # Очищення поля введення
            self.new_quantity_entry.delete(0, tk.END)
            
            messagebox.showinfo("Успіх", "Кількість транспорту успішно оновлено")
            
            # Оновлення стану кнопки "Показати деталі"
            self.calculations_done = False
            self.details_btn.config(state="disabled")
            
        except ValueError as e:
            messagebox.showerror("Помилка", f"Невірне значення: {str(e)}")
    
    def calculate_transport(self):
        """Розраховує оптимальний розподіл транспорту"""
        try:
            N_con = int(self.people_entry.get())
            if N_con <= 0:
                raise ValueError("Кількість людей має бути більше 0")
                
            # Обчислення мінімального та максимального ресурсу
            min_resource = sum(t.capacity * t.min_units for t in self.transports)
            max_resource = sum(t.capacity * t.max_units for t in self.transports)
            
            if N_con > max_resource:
                messagebox.showerror("Помилка", "Недостатньо транспорту для евакуації всіх людей")
                self.calculations_done = False
                self.details_btn.config(state="disabled")
                return
            elif N_con < min_resource:
                messagebox.showwarning("Увага", "Занадто мала кількість людей для мінімального парку транспорту")
                self.calculations_done = False
                self.details_btn.config(state="disabled")
                return
            
            # Обчислення коефіцієнта p
            sum_nK_max = sum(t.capacity * t.max_units for t in self.transports)
            sum_nK_min = sum(t.capacity * t.min_units for t in self.transports)
            
            if (sum_nK_max - sum_nK_min) == 0:
                p = 1
            else:
                p = (sum_nK_max - sum_nK_min) / (N_con - sum_nK_min)
            
            # Обчислення кількості для кожного типу транспорту
            for t in self.transports:
                K_i = (t.capacity * t.max_units + (p - 1) * t.capacity * t.min_units) / p
                t.used_units = round(K_i / t.capacity)
                
                # Перевірка меж
                if t.used_units < t.min_units:
                    t.used_units = t.min_units
                elif t.used_units > t.max_units:
                    t.used_units = t.max_units
            
            # Корекція загальної кількості
            self.adjust_units(N_con)
            
            # Відображення результатів
            self.display_results()
            
            # Активуємо кнопку "Показати деталі"
            self.calculations_done = True
            self.details_btn.config(state="normal")
            
        except ValueError as e:
            messagebox.showerror("Помилка", f"Невірні вхідні дані: {str(e)}")
            self.calculations_done = False
            self.details_btn.config(state="disabled")
    
    def adjust_units(self, N_con):
        """Корегує кількість одиниць транспорту для точного досягнення N_con"""
        current_total = sum(t.capacity * t.used_units for t in self.transports)
        difference = N_con - current_total
        
        while difference != 0:
            for t in self.transports:
                if difference > 0 and t.used_units < t.max_units:
                    t.used_units += 1
                    difference -= t.capacity
                    if difference <= 0:
                        break
                elif difference < 0 and t.used_units > t.min_units:
                    t.used_units -= 1
                    difference += t.capacity
                    if difference >= 0:
                        break
            
            # Запобігання нескінченному циклу
            if abs(difference) < min(t.capacity for t in self.transports if t.max_units > 0):
                break
    
    def display_results(self):
        """Відображає результати розрахунків"""
        # Очищення попередніх результатів
        for widget in self.result_frame.winfo_children():
            widget.destroy()
        
        # Відображення загальної інформації
        total_people = sum(t.capacity * t.used_units for t in self.transports)
        total_units = sum(t.used_units for t in self.transports)
        
        info_label = ttk.Label(self.result_frame, 
                             text=f"Загальна кількість транспорту: {total_units} одиниць\n"
                                 f"Загальна місткість: {total_people} людей")
        info_label.pack(pady=5)
        
        # Таблиця результатів
        columns = ("Тип транспорту", "Місткість", "Кількість", "Загальна місткість")
        tree = ttk.Treeview(self.result_frame, columns=columns, show="headings")
        
        for col in columns:
            tree.heading(col, text=col)
            tree.column(col, width=120, anchor="center")
        
        for t in self.transports:
            if t.used_units > 0:
                tree.insert("", "end", values=(t.name, t.capacity, t.used_units, t.capacity * t.used_units))
        
        tree.pack(fill="both", expand=True, padx=5, pady=5)
    
    def show_details(self):
        """Показує детальну інформацію про транспорт"""
        if not self.calculations_done:
            return
        
        # Створення нового вікна для детального відображення
        details_window = tk.Toplevel(self.root)
        details_window.title("Детальний розподіл транспорту")
        
        # Створення вкладок для кожного типу транспорту
        notebook = ttk.Notebook(details_window)
        
        for t in self.transports:
            if t.used_units > 0:
                frame = ttk.Frame(notebook)
                notebook.add(frame, text=t.name)
                
                # Відображення інформації про транспорт
                ttk.Label(frame, text=f"Тип: {t.name}", font=('Arial', 12, 'bold')).pack(pady=5)
                ttk.Label(frame, text=f"Місткість: {t.capacity} людей").pack()
                ttk.Label(frame, text=f"Кількість одиниць: {t.used_units}").pack()
                ttk.Label(frame, text=f"Загальна місткість: {t.capacity * t.used_units} людей").pack()
                
                # Відображення зображення транспорту
                if t.image:
                    img_label = ttk.Label(frame, image=t.image)
                    img_label.pack(pady=10)
                else:
                    ttk.Label(frame, text="Зображення недоступне", foreground="red").pack(pady=10)
        
        notebook.pack(fill="both", expand=True, padx=10, pady=10)
        
        # Кнопка закриття
        close_btn = ttk.Button(details_window, text="Закрити", command=details_window.destroy)
        close_btn.pack(pady=5)

if __name__ == "__main__":
    root = tk.Tk()
    app = EvacuationApp(root)
    root.mainloop()
