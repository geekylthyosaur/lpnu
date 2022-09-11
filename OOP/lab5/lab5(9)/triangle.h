#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "ui_mainwindow.h"

struct Values {
    double a;
    double b;
    double c;
};

class Triangle {
private:
    double a;
    double b;
    double c;
public:
    Triangle():
        Triangle(1.f, 1.f, 1.f)
    {};
    Triangle(double a, double b):
        Triangle(a, b, 1.f)
    {};
    Triangle(double a, double b, double c):
        a(a),
        b(b),
        c(c)
    {};

    double area();
    Values angles();
    double perimeter();
    Values medians();
    int isRight();
    void increaseSides(double n);

    double getA() const { return a; };
    double getB() const { return b; };
    double getC() const { return c; };
    void setA(double a) { this->a = a; };
    void setB(double b) { this->b = b; };
    void setC(double c) { this->c = c; };

    Values set(Ui::MainWindow *ui) {
        return Values {
            ui->aLineEdit->text().toDouble(),
            ui->bLineEdit->text().toDouble(),
            ui->cLineEdit->text().toDouble(),
        };
    }
    void get(Ui::MainWindow *ui) {
        ui->aLineEdit->setText(QString::number(this->getA()));
        ui->bLineEdit->setText(QString::number(this->getB()));
        ui->cLineEdit->setText(QString::number(this->getC()));
    }
};
#endif // TRIANGLE_H
