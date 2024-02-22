import sys
import psycopg2
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QLabel, QLineEdit, QTextEdit, QMessageBox

class MyApp(QWidget):
    def __init__(self):
        super().__init__()

        # Initialize the UI components
        self.init_ui()

        # Connect to the PostgreSQL database
        try:
            self.conn = psycopg2.connect(
                host='192.168.122.1',
                port=5432,
                user='user',
                password='password',
                database='my'
            )
        except Exception as e:
            self.show_error("Database Connection Error", str(e))
            sys.exit(1)

    def init_ui(self):
        # ... (unchanged code)
        self.setGeometry(100, 100, 600, 400)
        self.setWindowTitle('PyQt6 Database Example')

        # Create UI components
        self.label_result = QLabel('Result:', self)
        self.text_result = QTextEdit(self)

        # Input fields and labels for inserting data
        self.label_name = QLabel('Name:', self)
        self.label_lat = QLabel('Latitude:', self)
        self.label_lon = QLabel('Longitude:', self)

        self.input_name = QLineEdit(self)
        self.input_lat = QLineEdit(self)
        self.input_lon = QLineEdit(self)

        # Buttons for inserting data and calling procedure
        self.btn_select_data = QPushButton('Select Data', self)
        self.btn_select_data.clicked.connect(self.select_data)

        self.btn_insert_data = QPushButton('Insert Data', self)
        self.btn_insert_data.clicked.connect(self.insert_data)

        # Input fields and labels for calling validate_coords procedure
        self.label_validate_lat = QLabel('Validate Latitude:', self)
        self.label_validate_lon = QLabel('Validate Longitude:', self)

        self.input_validate_lat = QLineEdit(self)
        self.input_validate_lon = QLineEdit(self)

        # Button for calling validate_coords procedure
        self.btn_validate_coords = QPushButton('Validate Coordinates', self)
        self.btn_validate_coords.clicked.connect(self.validate_coords)

        # Layout
        layout = QVBoxLayout(self)
        layout.addWidget(self.label_result)
        layout.addWidget(self.text_result)
        layout.addWidget(self.label_name)
        layout.addWidget(self.input_name)
        layout.addWidget(self.label_lat)
        layout.addWidget(self.input_lat)
        layout.addWidget(self.label_lon)
        layout.addWidget(self.input_lon)
        layout.addWidget(self.btn_select_data)
        layout.addWidget(self.btn_insert_data)
        layout.addWidget(self.label_validate_lat)
        layout.addWidget(self.input_validate_lat)
        layout.addWidget(self.label_validate_lon)
        layout.addWidget(self.input_validate_lon)
        layout.addWidget(self.btn_validate_coords)

    def select_data(self):
        try:
            with self.conn.cursor() as cursor:
                cursor.execute("SELECT * FROM stop")
                self.display_result(cursor)
        except Exception as e:
            self.show_error("Error", str(e))

    def insert_data(self):
        name = self.input_name.text()
        lat = float(self.input_lat.text())
        lon = float(self.input_lon.text())

        try:
            with self.conn.cursor() as cursor:
                cursor.execute("INSERT INTO stop (name, lat, lon) VALUES (%s, %s, %s)", (name, lat, lon))
            self.conn.commit()
            self.display_result("Data inserted successfully.")
        except Exception as e:
            self.show_error("Error", str(e))

    def validate_coords(self):
        lat = float(self.input_validate_lat.text())
        lon = float(self.input_validate_lon.text())

        try:
            with self.conn.cursor() as cursor:
                cursor.execute("CALL validate_coords(%s, %s)", (lat, lon))
            self.conn.commit()
            self.display_result("Coordinates are valid.")
        except Exception as e:
            self.show_error("Error", str(e))

    def display_result(self, result):
        if isinstance(result, str):
            self.text_result.setPlainText(result)
        else:
            result_str = ""
            for row in result.fetchall():
                result_str += f"{row[0]} | {row[1]} | {row[2]}\n"
            self.text_result.setPlainText(result_str)

    def show_error(self, title, message):
        msg_box = QMessageBox()
        msg_box.setIcon(QMessageBox.Critical)
        msg_box.setWindowTitle(title)
        msg_box.setText(message)
        msg_box.exec()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    my_app = MyApp()
    my_app.show()
    sys.exit(app.exec())

