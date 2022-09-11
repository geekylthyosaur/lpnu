#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "triangle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

Triangle t;

void MainWindow::on_setButton_clicked() {
    t = Triangle(t.set(ui).a,
                 t.set(ui).b,
                 t.set(ui).c);
}

void MainWindow::on_areaPushButton_clicked() {
    ui->areaResultLabel->setText(QString::number(t.area()));
}

void MainWindow::on_anglesPushButton_clicked() {
    Values angles = t.angles();
    ui->anglesResultLabel->setText(QString::fromStdString(" a: ") + QString::number(angles.a) +
                                   QString::fromStdString(" b: ") + QString::number(angles.b) +
                                   QString::fromStdString(" c: ") + QString::number(angles.c));
}

void MainWindow::on_perimeterPushButton_clicked() {
    ui->perimeterResultLabel->setText(QString::number(t.perimeter()));
}

void MainWindow::on_mediansPushButton_clicked() {
    Values medians = t.medians();
    ui->mediansResultLabel->setText(QString::fromStdString(" a: ") + QString::number(medians.a) +
                                   QString::fromStdString(" b: ") + QString::number(medians.b) +
                                   QString::fromStdString(" c: ") + QString::number(medians.c));
}

void MainWindow::on_isRightPushButton_clicked() {
    ui->isRightLabel->setText(t.isRight() ? QString::fromStdString("true") : QString::fromStdString("false"));
}

void MainWindow::on_increasePushButton_clicked() {
    t.increaseSides(ui->increaseLineEdit->text().toDouble());
    t.get(ui);
}
