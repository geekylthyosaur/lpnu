#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "triangle.h"

Triangle * t1 = new Triangle(1,1,1);
Triangle * t2 = new Triangle(1,1,1);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    Triangle::objectCountIncreased(ui);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_set1Button_clicked() {
    Triangle * triangle = new Triangle();
    Triangle::objectCountIncreased(ui);
    ui >> *triangle;
    delete t1;
    t1 = triangle;
}

void MainWindow::on_set2Button_clicked() {
    Triangle * triangle = new Triangle();
    Triangle::objectCountIncreased(ui);
    triangle->setA(ui->a2LineEdit->text().toDouble());
    triangle->setB(ui->b2LineEdit->text().toDouble());
    triangle->setC(ui->c2LineEdit->text().toDouble());
    delete t2;
    t2 = triangle;
    ui->a2LineEdit->setText(QString::number((*t2)[0]));
    ui->b2LineEdit->setText(QString::number((*t2)[1]));
    ui->c2LineEdit->setText(QString::number((*t2)[2]));
}

void MainWindow::on_areaPushButton_clicked() {
    ui->areaResultLabel->setText(QString::number(t1->area()));
}

void MainWindow::on_anglesPushButton_clicked() {
    ui->anglesResultLabel->setText(QString::fromStdString(" a: ") + QString::number(t1->angles(0)) +
                                   QString::fromStdString(" b: ") + QString::number(t1->angles(1)) +
                                   QString::fromStdString(" c: ") + QString::number(t1->angles(2)));
}

void MainWindow::on_perimeterPushButton_clicked() {
    (*t1).medians(0);
    ui->perimeterResultLabel->setText(QString::number((double)(*t1)));
}

void MainWindow::on_mediansPushButton_clicked() {
    ui->mediansResultLabel->setText(QString::fromStdString(" a: ") + QString::number(t1->medians(0)) +
                                   QString::fromStdString(" b: ") + QString::number(t1->medians(1)) +
                                   QString::fromStdString(" c: ") + QString::number(t1->medians(2)));
}

void MainWindow::on_isRightPushButton_clicked() {
    ui->isRightLabel->setText(t1->isRight() ? QString::fromStdString("true") : QString::fromStdString("false"));
}

void MainWindow::on_increasePushButton_clicked() {
    (*t1) + ui->increaseLineEdit->text().toDouble();
    ui << (*t1);
}

void MainWindow::on_increaseMPushButton_clicked() {
    (*t1) * ui->increaseMLineEdit->text().toDouble();
    ui << (*t1);
}

void MainWindow::on_comparePushButton_clicked() {
    if ((*t1) > (*t2)) ui->compareResultLabel->setText(QString::fromStdString("Triangle 1 is bigger."));
    if ((*t2) > (*t1)) ui->compareResultLabel->setText(QString::fromStdString("Triangle 2 is bigger."));
    if ((*t1) == (*t2)) ui->compareResultLabel->setText(QString::fromStdString("Triangle 1 and 2 are equal."));
}
