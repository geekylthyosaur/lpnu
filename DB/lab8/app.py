import sys
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QLabel, QLineEdit, QTextEdit, QMessageBox
from PyQt6.QtSql import QSqlDatabase, QSqlQuery

class MyApp(QWidget):
    def __init__(self):
        super().__init__()

        # Initialize the UI components
        self.init_ui()

        # Connect to the PostgreSQL database
        self.db = QSqlDatabase.addDatabase('QPSQL')
        self.db.setHostName('192.168.122.1')
        self.db.setPort(5432)
        self.db.setUserName('user')
        self.db.setPassword('password')
        self.db.setDatabaseName('my')

        if not self.db.open():
            self.show_error("Database Connection Error", self.db.lastError().text())
            sys.exit(1)

    def init_ui(self):
        self.setGeometry(100, 100, 600, 400)
        self.setWindowTitle('PyQt6 Database Example')

        # Create UI components
        self.label_result = QLabel('Result:', self)
        self.text_result = QTextEdit(self)

        # Input fields
        self.input_name = QLineEdit(self)
        self.input_lat = QLineEdit(self)
        self.input_lon = QLineEdit(self)

        # Buttons
        self.btn_select_data = QPushButton('Select Data', self)
        self.btn_select_data.clicked.connect(self.select_data)

        self.btn_insert_data = QPushButton('Insert Data', self)
        self.btn_insert_data.clicked.connect(self.insert_data)

        self.btn_call_procedure = QPushButton('Call Procedure', self)
        self.btn_call_procedure.clicked.connect(self.call_procedure)

        # Layout
        layout = QVBoxLayout(self)
        layout.addWidget(self.label_result)
        layout.addWidget(self.text_result)
        layout.addWidget(self.input_name, placeholderText="Name")
        layout.addWidget(self.input_lat, placeholderText="Latitude")
        layout.addWidget(self.input_lon, placeholderText="Longitude")
        layout.addWidget(self.btn_select_data)
        layout.addWidget(self.btn_insert_data)
        layout.addWidget(self.btn_call_procedure)

    def select_data(self):
        query = QSqlQuery("SELECT * FROM stop")
        self.display_result(query)

    def insert_data(self):
        name = self.input_name.text()
        lat = float(self.input_lat.text())
        lon = float(self.input_lon.text())

        query = QSqlQuery()
        query.prepare("INSERT INTO stop (name, lat, lon) VALUES (?, ?, ?)")
        query.bindValue(0, name)
        query.bindValue(1, lat)
        query.bindValue(2, lon)

        if query.exec():
            self.display_result("Data inserted successfully.")
        else:
            self.show_error("Error", query.lastError().text())

    def call_procedure(self):
        # Replace this with the actual procedure call
        query = QSqlQuery("SELECT * FROM vehicle")
        self.display_result(query)

    def display_result(self, result):
        if isinstance(result, QSqlQuery):
            result_str = ""
            while result.next():
                result_str += f"{result.value(0)} | {result.value(1)} | {result.value(2)}\n"
        else:
            result_str = str(result)

        self.text_result.setPlainText(result_str)

    def show_error(self, title, message):
        msg_box = QMessageBox()
        msg_box.setIcon(QMessageBox.Icon.Critical)
        msg_box.setWindowTitle(title)
        msg_box.setText(message)
        msg_box.exec()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    my_app = MyApp()
    my_app.show()
    sys.exit(app.exec())

