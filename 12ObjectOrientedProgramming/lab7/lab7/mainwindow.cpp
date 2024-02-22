#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "deque.h"
#include <iostream>

using namespace std;

Deque d = Deque();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_clearDequeButton_clicked() {
    d.clear();
}

void MainWindow::on_addColPushButton_clicked() {
    ui->tableWidget->setColumnCount(ui->tableWidget->columnCount() + 1);
}

void MainWindow::on_rmColPushButton_clicked() {
    ui->tableWidget->removeColumn(ui->tableWidget->columnCount() - 1);
}

void MainWindow::on_addRowPushButton_clicked() {
    QListWidgetItem* item = new QListWidgetItem();
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->listWidget->insertItem(ui->listWidget->count(), item);
}

void MainWindow::on_rmRowPushButton_clicked() {
    ui->listWidget->takeItem(ui->listWidget->count() - 1);
}

void MainWindow::on_getTablePushButton_clicked() {
    d >> ui->tableWidget;
}

void MainWindow::on_setTablePushButton_clicked() {
    d.clear();
    d << ui->tableWidget;
}

void MainWindow::on_getListPushButton_clicked() {
    d >> ui->listWidget;
}

void MainWindow::on_setListPushButton_clicked() {
    d.clear();
    d << ui->listWidget;
}

void MainWindow::on_getLinePushButton_clicked() {
    d >> ui->lineEdit;
}

void MainWindow::on_setLinePushButton_clicked() {
    d.clear();
    d << ui->lineEdit;
}

void MainWindow::on_minPushButton_clicked() {
    ui->minResLineEdit->setText(QString::number(d.minValue()));
}

void MainWindow::on_maxPushButton_clicked() {
    ui->maxResLineEdit->setText(QString::number(d.maxValue()));
}

void MainWindow::on_avgPushButton_clicked() {
    ui->avgLineEdit->setText(QString::number(d.avgValue()));
}

void MainWindow::on_multiplyPushButton_clicked() {
    d.multiply(ui->multiplyLineEdit->text().toInt());
}

void MainWindow::on_nPushButton_clicked() {
    ui->nResLineEdit->setText(QString::number(d.countValues()));
}

void MainWindow::on_emptyPushButton_clicked() {
    ui->emptyResLineEdit->setText(d.isEmpty() ? "true" : "false");
}

void MainWindow::on_rmHeadPushButton_clicked() {
    --d;
}

void MainWindow::on_rmTailPushButton_clicked() {
    d--;
}

