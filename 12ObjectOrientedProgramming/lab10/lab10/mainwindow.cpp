#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "array.h"
#include "vector2d.h"

Array<Vector2D> * a = new Array<Vector2D>(10);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_set1Button_clicked() {
    double x = ui->vec1xEdit->text().toDouble();
    double y = ui->vec1yEdit->text().toDouble();
    Vector2D * vec1 = new Vector2D(x, y);
    a->set(0, *vec1);
}

void MainWindow::on_set2Button_clicked() {
    double x = ui->vec2xEdit->text().toDouble();
    double y = ui->vec2yEdit->text().toDouble();
    Vector2D * vec2 = new Vector2D(x, y);
    a->set(1, *vec2);
}

void MainWindow::on_compareButton_clicked() {
    if (a->get(0) > a->get(1))
        ui->compareButton->setText(QString::fromStdString(">"));
    else if (a->get(0) < a->get(1))
        ui->compareButton->setText(QString::fromStdString("<"));
    else if (a->get(0) == a->get(1))
        ui->compareButton->setText(QString::fromStdString("=="));
}

void MainWindow::on_print2Button_clicked() {
    a->print(ui->array2Label);
}

void MainWindow::on_max1Button_clicked() {
    ui->max1Button->setText(QString::number(a->max().length()));
}

void MainWindow::on_sum1Button_clicked() {
    ui->sum1Button->setText(QString::number(a->sum()));
}

