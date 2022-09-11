#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polynomial.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

Polynomial p = Polynomial(1, 1, 1);

void MainWindow::on_createButton_clicked() {
    p.setA0(ui->a0LineEdit->text().toDouble());
    p.setA1(ui->a1LineEdit->text().toDouble());
    p.setA2(ui->a2LineEdit->text().toDouble());
    updatePolynomial();
}

void MainWindow::on_findButton_clicked() {
    ui->findResultLabel->setText(QString::number(p.find(ui->findXLineEdit->text().toDouble())));
}

void MainWindow::on_multiplyButton_clicked() {
    p.multiply(ui->nLineEdit->text().toDouble());
    updatePolynomial();
}

void MainWindow::on_findDerButton_clicked() {
    ui->findDerResultLabel->setText(QString::number(p.findDerivative(ui->findDerXLineEdit->text().toDouble())));
}

void MainWindow::on_findIntegralButton_clicked() {
    ui->findIntegralResultLabel->setText(QString::number(p.findIntegral(ui->aLineEdit->text().toDouble(), ui->bLineEdit->text().toDouble())));
}

void MainWindow::on_findRootsButton_clicked() {
    Roots roots = p.findRoots();
    if (roots.n == 0) ui->findRootsResultLabel->setText(QString::fromStdString("No Roots."));
    else ui->findRootsResultLabel->setText(QString::number(roots.x1) + QString::fromStdString(" ") + QString::number(roots.x2));
}

void MainWindow::on_addButton_clicked() {
    Polynomial tmp = Polynomial(ui->addA0LineEdit->text().toDouble(),
                                ui->addA1LineEdit->text().toDouble(),
                                ui->addA2LineEdit->text().toDouble());
    p.add(tmp);
    updatePolynomial();
}

void MainWindow::updatePolynomial() {
    ui->a0LineEdit->setText(QString::number(p.getA0()));
    ui->a1LineEdit->setText(QString::number(p.getA1()));
    ui->a2LineEdit->setText(QString::number(p.getA2()));
}
