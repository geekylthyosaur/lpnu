import sys
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QLabel, QLineEdit, QPushButton, QMessageBox
from PyQt6.QtSql import QSqlDatabase, QSqlQuery

class TransportApp(QWidget):
    def __init__(self):
        super().__init__()

        # Initialize the database connection
        self.db = QSqlDatabase.addDatabase("QPSQL")
        self.db.setDatabaseName("my")
        self.db.setUserName("user")
        self.db.setPassword("password")
        self.db.setHostName("192.168.122.1")
        self.db.setPort(5432)

        if not self.db.open():
            QMessageBox.critical(self, "Database Error", "Unable to open the database")
            sys.exit(1)

        # Set up the GUI
        self.init_ui()

    def init_ui(self):
        # Widgets
        self.label = QLabel("Enter stop name:")
        self.stop_name_edit = QLineEdit()
        self.result_label = QLabel("Query result will be displayed here.")
        self.query_button = QPushButton("Execute Query")
        self.query_button.clicked.connect(self.execute_query)

        # Layout
        layout = QVBoxLayout()
        layout.addWidget(self.label)
        layout.addWidget(self.stop_name_edit)
        layout.addWidget(self.query_button)
        layout.addWidget(self.result_label)

        self.setLayout(layout)
        self.setWindowTitle("Transport Application")
        self.show()

    def execute_query(self):
        stop_name = self.stop_name_edit.text()

        # Start a transaction
        self.db.transaction()

        try:
            # Example query 1: Insert a new stop
            insert_query_text = "INSERT INTO stop (name, lat, lon) VALUES (:name, 0.0, 0.0)"
            insert_query = QSqlQuery()
            insert_query.prepare(insert_query_text)
            insert_query.bindValue(":name", stop_name)

            if not insert_query.exec():
                raise ValueError(f"Error executing query: {insert_query.lastError().text()}")

            # Example query 2: Select the inserted stop
            select_query_text = "SELECT * FROM stop WHERE name = :name"
            select_query = QSqlQuery()
            select_query.prepare(select_query_text)
            select_query.bindValue(":name", stop_name)

            if not select_query.exec():
                raise ValueError(f"Error executing query: {select_query.lastError().text()}")

            # Process query results
            result_text = ""
            while select_query.next():
                result_text += f"Stop ID: {select_query.value(0)}, Name: {select_query.value(1)}, Lat: {select_query.value(2)}, Lon: {select_query.value(3)}\n"

            # Update the interface with the results
            self.result_label.setText(result_text)

            # Simulate a concurrent transaction that may conflict
            # (e.g., another process updates the same record)
            conflicting_update_query_text = f"UPDATE stop SET lat = 1.0 WHERE name = '{stop_name}'"
            conflicting_update_query = QSqlQuery()
            if not conflicting_update_query.exec(conflicting_update_query_text):
                raise ValueError(f"Error executing conflicting query: {conflicting_update_query.lastError().text()}")

            # Commit the transaction
            self.db.commit()

        except ValueError as e:
            # Handle errors
            QMessageBox.critical(self, "Query Error", str(e))
            # Rollback the transaction
            self.db.rollback()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = TransportApp()
    sys.exit(app.exec())
