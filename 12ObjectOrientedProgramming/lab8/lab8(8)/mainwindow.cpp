#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QMessageBox"
#include "QFileDialog"
#include "QTextStream"

#include <period.h>
#include <electricity_bill.h>
#include <usual_electricity_bill.h>
#include <special_electricity_bill.h>
#include <multizone_electricity_bill.h>
#include <iostream>
#include <cstring>
using namespace std;

ElectricityBill * bill;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addPeriodButton_clicked() {
    if (ui->startPeriodDateTimeEdit->dateTime() >= ui->endPeriodDateTimeEdit->dateTime()) {
        QMessageBox msgBox;
        msgBox.setText("The end date is less or equal than the start date!");
        msgBox.exec();
        return;
    }
    if (ui->periodTypeComboBox->isEnabled() == true) {
        if (ui->periodTypeComboBox->currentText() == "Usual") {
            bill = new UsualElectricityBill();
        } else if (ui->periodTypeComboBox->currentText() == "Special") {
            bill = new SpecialElectricityBill();
        } else if (ui->periodTypeComboBox->currentText() == "Multizone") {
            bill = new MultizoneElectricityBill();
        }
    }

    ui->periodTypeComboBox->setEnabled(false);
    bill->addPeriod(
            ui->startPeriodDateTimeEdit->dateTime(),
            ui->endPeriodDateTimeEdit->dateTime(),
            ui->consumptionLineEdit->text().toDouble()
    );
    bill->printList(ui->tableWidget);

    ui->startPeriodDateTimeEdit->setDateTime(ui->endPeriodDateTimeEdit->dateTime());
    ui->startPeriodDateTimeEdit->setMinimumDateTime(ui->endPeriodDateTimeEdit->dateTime());
}

void MainWindow::on_writePushButton_clicked() {
    if (ui->tableWidget->rowCount() == 0) {
        QMessageBox msgBox;
        msgBox.setText("Nothing to write!");
        msgBox.exec();
        return;
    }
    QString filename= QFileDialog::getSaveFileName(this, "Save As");

    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << ui->periodTypeComboBox->currentText() << "\n";

    for (Period p : *bill->getList()) {
        out << p.getStartDateTime().toString("dd.MM.yyyy HH:mm") + "," + p.getEndDateTime().toString("dd.MM.yyyy HH:mm") + "," + QString::number(p.getConsumption()) << "\n";
    }

    file.close();
}

void MainWindow::on_readPushButton_clicked() {
    QFile file(QFileDialog::getOpenFileName(this, tr("Open File"), "/home/dmytro/", tr("(*)")));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QDateTime start;
    QDateTime end;
    int consumption;
    QTextStream in(&file);
    QString line = in.readLine();
    delete bill;

    if (line == "Usual") {
        bill = new UsualElectricityBill();
        ui->periodTypeComboBox->setCurrentIndex(0);
        ui->periodTypeComboBox->setEnabled(false);
    } else if (line == "Special") {
        bill = new SpecialElectricityBill();
        ui->periodTypeComboBox->setCurrentIndex(1);
        ui->periodTypeComboBox->setEnabled(false);
    } else if (line == "Multizone") {
        bill = new MultizoneElectricityBill();
        ui->periodTypeComboBox->setCurrentIndex(2);
        ui->periodTypeComboBox->setEnabled(false);
    }
    line = in.readLine();

    while (!line.isEmpty()) {
        QStringList list = line.split(",");
        start = QDateTime::fromString(list[0], "dd.MM.yyyy HH:mm");
        end = QDateTime::fromString(list[1], "dd.MM.yyyy HH:mm");
        consumption = list[2].toInt();
        ui->startPeriodDateTimeEdit->setMinimumDateTime(end);
        ui->endPeriodDateTimeEdit->setMinimumDateTime(end);
        bill->addPeriod(start, end, consumption);
        line = in.readLine();
    }
    file.close();
    bill->printList(ui->tableWidget);
}

void MainWindow::on_clearPushButton_clicked() {
    delete bill;
    ui->tableWidget->setRowCount(0);
    ui->periodTypeComboBox->setEnabled(true);
    ui->startPeriodDateTimeEdit->setMinimumDateTime(QDateTime::fromString("01.01.2022 00:00", "dd.MM.yyyy HH:mm"));
    ui->endPeriodDateTimeEdit->setMinimumDateTime(QDateTime::fromString("01.01.2022 00:00", "dd.MM.yyyy HH:mm"));
    ui->startPeriodDateTimeEdit->setDateTime(QDateTime::fromString("01.01.2022 00:00", "dd.MM.yyyy HH:mm"));
    ui->endPeriodDateTimeEdit->setDateTime(QDateTime::fromString("01.01.2022 00:00", "dd.MM.yyyy HH:mm"));
    ui->periodTypeComboBox->setCurrentIndex(0);
    ui->consumptionLineEdit->setText("");
    ui->resultLabel->clear();
}

void MainWindow::on_calculateButton_clicked() {
    if (ui->tableWidget->rowCount() == 0) {
        QMessageBox msgBox;
        msgBox.setText("Nothing to calculate!");
        msgBox.exec();
        return;
    }
    if (ui->periodTypeComboBox->currentText() == "Usual")
        ui->resultLabel->setText(QString::number(static_cast<UsualElectricityBill*>(bill)->calculate()) + " UAH");
    else if (ui->periodTypeComboBox->currentText() == "Special")
        ui->resultLabel->setText(QString::number(static_cast<SpecialElectricityBill*>(bill)->calculate()) + " UAH");
    else if (ui->periodTypeComboBox->currentText() == "Multizone")
        ui->resultLabel->setText(QString::number(static_cast<MultizoneElectricityBill*>(bill)->calculate()) + " UAH");
}

void MainWindow::on_pushButton_clicked() {
    ui->printLabel->setText(ElectricityBill::print() + " " + UsualElectricityBill::print() + "\n"
                            + SpecialElectricityBill::print() + " " + MultizoneElectricityBill::print());
}

