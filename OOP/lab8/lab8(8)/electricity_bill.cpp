#include "electricity_bill.h"

ElectricityBill::ElectricityBill() {}

void ElectricityBill::addPeriod(QDateTime start, QDateTime end, double consumpion) {
    Period p = Period(start, end, consumpion);
    list.push_back(p);
}

void ElectricityBill::printList(QTableWidget *table) {
    table->setRowCount(0);
    int i = 0;
    for (Period p : list) {
        table->insertRow(i);
        for (int j = 0; j < 3; j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            if (j == 0) item->setText(p.getStartDateTime().toString("dd.MM.yyyy HH:mm"));
            else if (j == 1) item->setText(p.getEndDateTime().toString("dd.MM.yyyy HH:mm"));
            else if (j == 2) item->setText(QString::number(p.getConsumption()));
            table->setItem(i, j, item);
        }
        i += 1;
    }
}

QString ElectricityBill::print() {
    return "ElectricityBill";
}
