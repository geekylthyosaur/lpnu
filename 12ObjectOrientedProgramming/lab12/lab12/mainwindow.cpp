#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QTextStream"
#include "QMessageBox"
#include "myarray.h"
#include "iostream"
using namespace std;
MyArray * a;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_inputButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Select input file"), "/home/dmytro/", tr("(*)"));
    try {
        a = MyArray::read(filename);
    }  catch (int err) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error");
        if (err == 1) msgBox.setText("File with name '" + filename + "' does not exist!");
        else if (err == 2) msgBox.setText("File is broken!");
        else if (err == 3) msgBox.setText("File is empty!");
        else if (err == 4) msgBox.setText("Overflow!");
        msgBox.exec();
        return;
    }
    ui->table->setColumnCount(0);
    for (int i = 0; i < a->getSize(); i++) {
        ui->table->insertColumn(i);
        QTableWidgetItem * item = new QTableWidgetItem();
        item->setText(QString::number(a->get(i)));
        ui->table->setItem(0, i, item);
    }
    ui->inputButton->setText(filename.split("/").back());
}

void MainWindow::on_outputButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Select output file"), "/home/dmytro/", tr("(*)"));
    try {
        a->write(filename);
    } catch (int) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error");
        msgBox.setText("File with name '" + filename + "' does not exist!");
        msgBox.exec();
        return;
    }

    ui->outputButton->setText(filename.split("/").back());
}

void MainWindow::on_minButton_clicked() {
    ui->minLine->setText(QString::number(a->min()));
}

void MainWindow::on_maxButton_clicked() {
    ui->maxLine->setText(QString::number(a->max()));
}

void MainWindow::on_avgButton_clicked() {
    ui->avgLine->setText(QString::number(a->avg()));
}

void MainWindow::on_clearButton_clicked() {
    ui->table->setColumnCount(0);
    delete a;
}

void MainWindow::on_createButton_clicked() {
    int size = ui->table->columnCount();
    a = new MyArray(size);
    for (int i = 0; i < size; i++)
        a->set(i, ui->table->item(0, i)->text().toDouble());
}

void MainWindow::on_addColButton_clicked() {
    ui->table->setColumnCount(ui->table->columnCount() + 1);
}

void MainWindow::on_rmColButton_clicked() {
    ui->table->setColumnCount(ui->table->columnCount() - 1);
}

void MainWindow::on_getButton_clicked() {
    int i = ui->iLine->text().toInt();
    try {
        ui->iAnsLine->setText(QString::number(a->get(i)));
    }  catch (int) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error");
        msgBox.setText("No item with index " + QString::number(i) + "!");
        msgBox.exec();
        return;
    }
}

void MainWindow::on_setButton_clicked() {
    int i = ui->iLine_2->text().toInt();
    double v = ui->valLine->text().toDouble();
    try {
        a->set(i, v);
        ui->table->item(0, i)->setText(QString::number(v));
    }  catch (int) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error");
        msgBox.setText("Can't set to index " + QString::number(i) + "!");
        msgBox.exec();
        return;
    }
}
