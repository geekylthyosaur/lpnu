import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QTabWidget, QWidget, QVBoxLayout, QTableWidget, QTableWidgetItem, QHeaderView, QComboBox
from PyQt5.QtGui import QColor
import pandas as pd
from statistics import mean
import random
import numpy as np

class RiskManagementApp(QMainWindow):
    def __init__(self):
        super(RiskManagementApp, self).__init__()

        # Create the outer tab widget
        self.outer_tab_widget = QTabWidget(self)
        self.selected_mitigations = []

        # Create the tabs for the outer tab widget
        self.tab1 = QWidget()
        self.tab2 = QWidget()
        self.tab3 = QWidget()
        self.tab4 = QWidget()

        # Set up the content for each outer tab
        self.setup_tab_identification(self.tab1)
        self.setup_tab_analysis(self.tab2)
        self.setup_tab_mitigation(self.tab3)
        self.setup_tab_monitoring(self.tab4)

        # Add the tabs to the outer tab widget
        self.outer_tab_widget.addTab(self.tab1, "Ідентифікація ризиків")
        self.outer_tab_widget.addTab(self.tab2, "Аналіз ризиків")
        self.outer_tab_widget.addTab(self.tab3, "Усунення ризиків")
        self.outer_tab_widget.addTab(self.tab4, "Моніторинг ризиків")

        # Set the central widget of the main window to the outer tab widget
        self.setCentralWidget(self.outer_tab_widget)

    def setup_tab_identification(self, tab):
        # Create the inner tab widget for "Ідентифікація ризиків"
        inner_tab_widget = QTabWidget(tab)

        # Create tabs for the inner tab widget
        inner_tab1 = QWidget()
        inner_tab2 = QWidget()

        # Set up the content for each inner tab
        self.setup_tab_sources(inner_tab1)
        self.setup_tab_potential_events(inner_tab2)

        # Add the inner tabs to the inner tab widget
        inner_tab_widget.addTab(inner_tab1, "Джерела появи")
        inner_tab_widget.addTab(inner_tab2, "Потенційні ризикові події")

        # Add the inner tab widget to the layout of the outer tab
        layout = QVBoxLayout(tab)
        layout.addWidget(inner_tab_widget)

    def setup_tab_analysis(self, tab):
        # Create the inner tab widget for "Аналіз ризиків"
        inner_tab_widget = QTabWidget(tab)

        # Create tabs for the inner tab widget
        inner_tab1 = QWidget()
        inner_tab2 = QWidget()

        # Set up the content for each inner tab
        self.setup_tab_probability(inner_tab1)
        self.setup_tab_priority(inner_tab2)

        # Add the inner tabs to the inner tab widget
        inner_tab_widget.addTab(inner_tab1, "Ймовірність настання ризикових подій")
        inner_tab_widget.addTab(inner_tab2, "Пріоритетність ризиків")

        # Add the inner tab widget to the layout of the outer tab
        layout = QVBoxLayout(tab)
        layout.addWidget(inner_tab_widget)

    def setup_tab_sources(self, tab):
        df = self.read_data("tdata/data11.csv")

        calc = df[df.columns[1]].round(0).astype(int)
        t = calc[:7].sum() * 100 / 18
        c = calc[7:10].sum() * 100 / 18
        p = calc[10:13].sum() * 100 / 18
        m = calc[13:].sum() * 100 / 18
        total = t + c + p + m

        df = self.insert_row(df, ["Множина джерел появи технічних ризиків", f"{t:.2f}%"], 0)
        df = self.insert_row(df, ["Множина джерел появи вартісних ризиків", f"{c:.2f}%"], 8)
        df = self.insert_row(df, ["Множина джерел появи планових ризиків", f"{p:.2f}%"], 12)
        df = self.insert_row(df, ["Множина джерел появи ризиків реалізації процесу управління програмним проектом", f"{m:.2f}%"], 16)
        df = self.insert_row(df, ["", f"{total:.2f}%"], 22)

        # Add content for "Джерела появи"
        title_row = ["Джерела ризиків", "Ймовірність появи"]
        data = df.values.tolist()
        highlighted_positions = [1, 9, 13, 17, 23]
        self.setup_table_content(tab, title_row, data, highlighted_positions)

    def setup_tab_potential_events(self, tab):
        df = self.read_data("tdata/data12.csv")

        calc = df[df.columns[1]].round(0).astype(int)
        t = calc[:11].sum() * 100 / 41
        c = calc[11:18].sum() * 100 / 41
        p = calc[18:27].sum() * 100 / 41
        m = calc[27:].sum() * 100 / 41
        total = t + c + p + m

        df = self.insert_row(df, ["Множина настання технічних ризикових подій", f"{t:.2f}%"], 0)
        df = self.insert_row(df, ["Множина настання вартісних ризикових подій", f"{c:.2f}%"], 12)
        df = self.insert_row(df, ["Множина настання планових ризикових подій", f"{p:.2f}%"], 20)
        df = self.insert_row(df, ["Множина настання ризикових подій реалізації процесу управління програмним проектом", f"{m:.2f}%"], 30)
        df = self.insert_row(df, ["", f"{total:.2f}%"], 45)

        # Add content for "Потенційні ризикові події"
        title_row = ["Потенційні ризикові події", "Ймовірність появи"]
        data = df.values.tolist()
        highlighted_positions = [1, 13, 21, 31, 46]  # Positions to highlight (1-based index)
        self.setup_table_content(tab, title_row, data, highlighted_positions)

    def setup_tab_probability(self, tab):
        df = self.read_data("tdata/data21.csv")

        er = df[df.columns[1:11]]
        self.insert_col(df, [round(mean(er.iloc[i]), 2) for i in range(0, 41)], 11)

        # Add content for "Ймовірність настання ризикових подій"
        title_row = ["Потенційні ризикові події", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "ER"]
        data = df.values.tolist()
        highlighted_positions = [0]  # Positions to highlight (1-based index)
        self.setup_table_content(tab, title_row, data, highlighted_positions)

    def setup_tab_priority(self, tab):
        df = self.read_data("tdata/data21.csv")
        er = df[df.columns[1:11]]
        prer = [round(mean(er.iloc[i]), 2) for i in range(0, 41)]

        df = self.read_data("tdata/data22.csv")
        random.seed("0")
        lrer = [round(random.uniform(0, 1), 2) for _ in range(0, 41)]
        vrer = [round(prer[i] * lrer[i], 2) for i in range(0, 41)]
        priority = ["Високий" if vrer[i] >= min(er.iloc[i, :]) and vrer[i] < min(er.iloc[i, :]) + (max(er.iloc[i, :])-min(er.iloc[i, :]))/3 else "Середній" if vrer[i] >= min(er.iloc[i, :]) + (max(er.iloc[i, :])-min(er.iloc[i, :]))/3 and vrer[i] < min(er.iloc[i, :]) + 2*(max(er.iloc[i, :])-min(er.iloc[i, :]))/3 else "Низький" for i in range(0, 41)]

        self.insert_col(df, prer, 1)
        self.insert_col(df, lrer, 2)
        self.insert_col(df, vrer, 3)
        self.insert_col(df, priority, 4)

        # Add content for "Пріоритетність ризиків"
        title_row = ["Потенційні ризикові події", "ER", "LRER", "VRER", "Пріоритет"]
        data = df.values.tolist()
        highlighted_positions = [0]  # Positions to highlight (1-based index)
        self.setup_table_content(tab, title_row, data, highlighted_positions)

    def setup_tab_mitigation(self, tab):
        df = self.read_data("tdata/data21.csv")
        df = df.iloc[:, :1]
        mitigations = self.read_data("tdata/data3.csv").values.tolist()
        mitigations = [mitigations[random.randint(0, 18)] for _ in range(0, 41)]
        mitigations = list(np.concatenate(mitigations))

        # Create a table with QComboBox for mitigation selection
        title_row = ["Потенційні ризикові події", "Рішення"]
        data = df.values.tolist()
        highlighted_positions = [0]  # Positions to highlight (1-based index)

        table_widget = QTableWidget(tab)
        table_widget.setColumnCount(len(title_row))
        table_widget.setHorizontalHeaderLabels(title_row)

        for row, (risk_event, mitigation) in enumerate(zip(data, mitigations)):
            table_widget.insertRow(row)

            # Set up the combo box for the mitigation column
            combo_box = QComboBox()
            combo_box.addItems(mitigations)  # You can add specific items to the combo box
            combo_box.setCurrentText(mitigation)  # Set the current text based on the mitigation value
            table_widget.setCellWidget(row, 1, combo_box)

            # Set up the risk event in the first column
            item = QTableWidgetItem(str(risk_event[0]))
            table_widget.setItem(row, 0, item)

            # Highlight specified positions
            if row + 1 in highlighted_positions:
                for col in range(table_widget.columnCount()):
                    item = table_widget.item(row, col)
                    item.setBackground(QColor(200, 200, 200))

        # Set the first column width to maximum
        table_widget.horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)
        # Set the other columns to fit the content
        for col in range(1, table_widget.columnCount()):
            table_widget.horizontalHeader().setSectionResizeMode(col, QHeaderView.ResizeToContents)

        # Connect a signal to handle combo box selection changes
        table_widget.cellWidget(0, 1).currentTextChanged.connect(self.onMitigationSelectionChanged)

        # Add the table widget to the layout of the tab
        layout = QVBoxLayout(tab)
        layout.addWidget(table_widget)

    def onMitigationSelectionChanged(self, text):
        # Update the selected mitigations list when a combo box selection changes
        self.selected_mitigations.append(text)

    def setup_tab_monitoring(self, tab):
        df = self.read_data("tdata/data21.csv")
        er = df[df.columns[1:11]]
        prer = [round(mean(er.iloc[i]), 2) for i in range(0, 41)]

        df = self.read_data("tdata/data22.csv")
        random.seed("0")
        lrer = [round(random.uniform(0, 1), 2) for _ in range(0, 41)]
        vrer = [round(prer[i] * lrer[i], 2) for i in range(0, 41)]
        priority = ["Високий" if vrer[i] >= min(er.iloc[i, :]) and vrer[i] < min(er.iloc[i, :]) + (max(er.iloc[i, :])-min(er.iloc[i, :]))/3 else "Середній" if vrer[i] >= min(er.iloc[i, :]) + (max(er.iloc[i, :])-min(er.iloc[i, :]))/3 and vrer[i] < min(er.iloc[i, :]) + 2*(max(er.iloc[i, :])-min(er.iloc[i, :]))/3 else "Низький" for i in range(0, 41)]

        mitigations = self.read_data("tdata/data3.csv").values.tolist()
        mitigations = [mitigations[random.randint(0, 18)] for _ in range(0, 41)]
        mitigations = list(np.concatenate(mitigations))

        self.insert_col(df, mitigations, 1)
        self.insert_col(df, vrer, 2)
        self.insert_col(df, priority, 3)

        random.seed("1")
        elrer = [round(random.uniform(0, prer[i] * lrer[i]), 2) for i in range(0, 41)]
        evrer = [round(prer[i] * elrer[i], 2) for i in range(0, 41)]
        epriority = ["Високий" if evrer[i] >= min(er.iloc[i, :]) and evrer[i] < min(er.iloc[i, :]) + (max(er.iloc[i, :])-min(er.iloc[i, :]))/3 else "Середній" if evrer[i] >= min(er.iloc[i, :]) + (max(er.iloc[i, :])-min(er.iloc[i, :]))/3 and evrer[i] < min(er.iloc[i, :]) + 2*(max(er.iloc[i, :])-min(er.iloc[i, :]))/3 else "Низький" for i in range(0, 41)]

        self.insert_col(df, evrer, 4)
        self.insert_col(df, epriority, 5)

        # Add content for "Моніторинг ризиків"
        title_row = ["Потенційні ризикові події", "Рішення", "VRER", "Пріоритет", "EVRER", "Пріоритет"]
        data = df.values.tolist()
        highlighted_positions = [0]  # Positions to highlight (1-based index)
        self.setup_table_content(tab, title_row, data, highlighted_positions)

    def setup_table_content(self, tab, title_row, data, highlighted_positions):
        # Create a table widget and set the column count
        table_widget = QTableWidget(tab)
        table_widget.setColumnCount(len(title_row))

        # Set the table headers
        table_widget.setHorizontalHeaderLabels(title_row)

        # Populate the table with data
        for row, row_data in enumerate(data):
            table_widget.insertRow(row)
            for col, col_data in enumerate(row_data):
                item = QTableWidgetItem(str(col_data))
                table_widget.setItem(row, col, item)

            # Highlight specified positions
            if row + 1 in highlighted_positions:
                for col in range(table_widget.columnCount()):
                    item = table_widget.item(row, col)
                    item.setBackground(QColor(200, 200, 200))

        # Set the first column width to maximum
        table_widget.horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)

        # Set the other columns to fit the content
        for col in range(1, table_widget.columnCount()):
            table_widget.horizontalHeader().setSectionResizeMode(col, QHeaderView.ResizeToContents)

        # Add the table widget to the layout of the tab
        layout = QVBoxLayout(tab)
        layout.addWidget(table_widget)

    def read_data(self, path):
        df = pd.read_csv(path, delimiter='\t', skip_blank_lines=True, header=None)
        return df

    def insert_row(self, df, row, index):
        # Convert the row data to a DataFrame
        new_row = pd.DataFrame([row], columns=df.columns)

        # Concatenate the DataFrame with the new row at the specified index
        df = pd.concat([df.loc[:index-1], new_row, df.loc[index:]]).reset_index(drop=True)

        return df

    def insert_col(self, df, col, index):
        df.insert(index, index, col)

def main():
    app = QApplication(sys.argv)
    window = RiskManagementApp()
    window.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()

