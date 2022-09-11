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
    static int objectCount;
public:
    Triangle():
        Triangle(1.f, 1.f, 1.f)
    {};
    Triangle(double a, double b):
        Triangle(a, b, 1.f)
    {};
    Triangle(double a, double b, double c) {
        this->a = a;
        this->b = b;
        this->c = c;
        objectCount++;
    };

    double area();
    Values angles();
    double angles(int n);
    double perimeter();
    Values medians();
    double medians(int n);
    bool isRight();
    bool isRight(int n);
    void increaseSides(double n);

    double getA() const { return a; };
    double getB() const { return b; };
    double getC() const { return c; };
    static int getObjectCount() { return objectCount; };
    static void objectCountIncreased(Ui::MainWindow *ui);
    void setA(double a) { this->a = a; };
    void setB(double b) { this->b = b; };
    void setC(double c) { this->c = c; };

    void operator+(double n);
    void operator*(double n);
    double operator[](int i);
    operator double();
    friend void operator<<( Ui::MainWindow *ui, Triangle &t );
    friend void operator>>(Ui::MainWindow *ui, Triangle &t);
    friend bool operator>(Triangle &t1, Triangle &t2);
    friend bool operator<(Triangle &t1, Triangle &t2);
    friend bool operator==(Triangle &t1, Triangle &t2);
};

#endif // TRIANGLE_H
