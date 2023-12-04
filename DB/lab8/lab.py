import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget, QPushButton, QTableWidget, QTableWidgetItem, QLineEdit, QMessageBox
import psycopg2

class DatabaseApp(QMainWindow):
    def __init__(self):
        super().__init__()

        self.initUI()
        self.connect_to_database()

    def initUI(self):
        self.setWindowTitle('Database App')
        self.setGeometry(100, 100, 800, 600)

        self.central_widget = QWidget(self)
        self.setCentralWidget(self.central_widget)

        self.layout = QVBoxLayout()

        self.select_button = QPushButton('Execute Select', self)
        self.select_button.clicked.connect(self.execute_select)
        self.layout.addWidget(self.select_button)

        self.select_input = QLineEdit(self)
        self.select_input.setPlaceholderText('What to select...')
        self.layout.addWidget(self.select_input)

        self.insert_button = QPushButton('Execute Insert', self)
        self.insert_button.clicked.connect(self.execute_insert)
        self.layout.addWidget(self.insert_button)

        self.insert_input = QLineEdit(self)
        self.insert_input.setPlaceholderText('What to insert...')
        self.layout.addWidget(self.insert_input)

        self.call_procedure_button = QPushButton('Call Procedure', self)
        self.call_procedure_button.clicked.connect(self.call_procedure)
        self.layout.addWidget(self.call_procedure_button)

        self.procedure_input = QLineEdit(self)
        self.procedure_input.setPlaceholderText('Arguments...')
        self.layout.addWidget(self.procedure_input)

        self.table_widget = QTableWidget(self)
        self.layout.addWidget(self.table_widget)

        self.central_widget.setLayout(self.layout)

    def connect_to_database(self):
        dbname = "my"
        user = "user"
        password = "password"
        host = "192.168.122.1"
        port = 5432

        try:
            self.connection = psycopg2.connect(
                dbname=dbname, user=user, password=password, host=host, port=port
            )
            print("Connected to the database")
        except psycopg2.Error as e:
            self.show_error_popup("Unable to execute query", e)

    def execute_insert(self):
        input = self.insert_input.text()
        query = f"INSERT INTO stop VALUES {input};"

        try:
            with self.connection.cursor() as cursor:
                cursor.execute(query)
        except psycopg2.Error as e:
            self.show_error_popup("Unable to execute query", e)
            self.connection.rollback()
        finally:
            cursor.close()

    def execute_select(self):
        input = self.select_input.text()
        query = f"SELECT * FROM stop {input};"

        try:
            with self.connection.cursor() as cursor:
                cursor.execute(query)
                rows = cursor.fetchall()

                self.display_results(rows, cursor)
        except psycopg2.Error as e:
            self.show_error_popup("Unable to execute query", e)
            self.connection.rollback()
        finally:
            cursor.close()

    def call_procedure(self):
        a, b = self.procedure_input.text().split()
        query = f"CALL validate_coords({float(a)}, {float(b)});"

        try:
            with self.connection.cursor() as cursor:
                cursor.execute(query)
        except psycopg2.Error as e:
            self.show_error_popup("Unable to execute query", e)
            self.connection.rollback()
        finally:
            cursor.close()
        
    def display_results(self, rows, cursor):
        self.table_widget.clear()

        if not rows:
            print("No results to display.")
            return

        self.table_widget.setRowCount(len(rows))
        self.table_widget.setColumnCount(len(rows[0]))

        headers = [str(desc[0]) for desc in cursor.description]
        self.table_widget.setHorizontalHeaderLabels(headers)

        for i, row in enumerate(rows):
            for j, value in enumerate(row):
                item = QTableWidgetItem(str(value))
                self.table_widget.setItem(i, j, item)

    def show_error_popup(self, title, message):
        msg_box = QMessageBox()
        msg_box.setIcon(QMessageBox.Icon.Critical)
        msg_box.setWindowTitle(title)
        msg_box.setText(str(message))
        msg_box.exec()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = DatabaseApp()
    window.show()
    sys.exit(app.exec())

