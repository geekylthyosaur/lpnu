#include "triangle.h"
#include <math.h>

int Triangle::objectCount = 0;

double Triangle::area() {
    double p = 0.5 * (a + b + c);
    double S = sqrt(p*(p-a)*(p-b)*(p-c));
    return S;
}

Values Triangle::angles() {
    Values angles;
    angles.a = acos((a*a - b*b - c*c) / ((-2)*b*c)) * 180/M_PI;
    angles.b = acos((b*b - a*a - c*c) / ((-2)*a*c)) * 180/M_PI;
    angles.c = acos((c*c - a*a - b*b) / ((-2)*a*b)) * 180/M_PI;
    return angles;
}

double Triangle::angles(int n) {
    double angle;
    if (n == 0) angle = acos((a*a - b*b - c*c) / ((-2)*b*c)) * 180/M_PI;
    else if (n == 1) angle = acos((b*b - a*a - c*c) / ((-2)*a*c)) * 180/M_PI;
    else if (n == 2) angle = acos((c*c - a*a - b*b) / ((-2)*a*b)) * 180/M_PI;
    else return 0.f;
    return angle;
}

double Triangle::perimeter() {
    return (double)*this;
}

Values Triangle::medians() {
    Values medians;
    medians.a = sqrt((2*b*b + 2*c*c - a*a) / 4);
    medians.b = sqrt((2*a*a + 2*c*c - b*b) / 4);
    medians.c = sqrt((2*a*a + 2*b*b - c*c) / 4);
    return medians;
}

double Triangle::medians(int n) {
    double median;
    if (n == 0) median = sqrt((2*b*b + 2*c*c - a*a) / 4);
    else if (n == 1) median = sqrt((2*a*a + 2*c*c - b*b) / 4);
    else if (n == 2) median = sqrt((2*a*a + 2*b*b - c*c) / 4);
    else return 0.f;
    return median;
}

bool Triangle::isRight() {
    return isRight(0) || isRight(1) || isRight(2);
}

bool Triangle::isRight(int n) {
    return angles(n) == 90.f;
}

void Triangle::increaseSides(double n) {
    *this + n;
}

void Triangle::operator+(double n) {
    a += n;
    b += n;
    c += n;
}

void Triangle::operator*(double n) {
    a *= n;
    b *= n;
    c *= n;
}

double Triangle::operator[](int i) {
    if (i==0) return a;
    else if (i==1) return b;
    else if (i==2) return c;
    else return 0;
}

Triangle::operator double() {
    return a + b + c;
}

void operator<<(Ui::MainWindow *ui, Triangle &t) {
    ui->a1LineEdit->setText(QString::number(t.getA()));
    ui->b1LineEdit->setText(QString::number(t.getB()));
    ui->c1LineEdit->setText(QString::number(t.getC()));
}

void operator>>(Ui::MainWindow *ui, Triangle &t) {
    t.setA(ui->a1LineEdit->text().toDouble());
    t.setB(ui->b1LineEdit->text().toDouble());
    t.setC(ui->c1LineEdit->text().toDouble());
}

bool operator>(Triangle &t1, Triangle &t2) {
    return (double)t1 > (double)t2;
}

bool operator<(Triangle &t1, Triangle &t2) {
    return (double)t1 < (double)t2;
}

bool operator==(Triangle &t1, Triangle &t2) {
    return (double)t1 == (double)t2;
}

void Triangle::objectCountIncreased(Ui::MainWindow *ui) {
    ui->objectCountLabel->setText(QString::number(Triangle::getObjectCount()));
}
