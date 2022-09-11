#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "array.h"
#include "math.h"

class Vector2D {
private:
    double x;
    double y;
public:
    Vector2D():
        x(0),
        y(0)
    {};
    Vector2D(double x, double y):
        x(x),
        y(y)
    {};
    double getX() { return x; };
    double getY() { return y; };
    double length() { return sqrt(getX()*getX() + getY()*getY()); };
    QString print() { return QString::number(x) + " " +  QString::number(y);};
    bool operator>(Vector2D v) { return this->length() > v.length(); };
    bool operator<(Vector2D v) { return this->length() < v.length(); };
    bool operator==(Vector2D v) { return this->length() == v.length(); };
};

#endif // VECTOR2D_H
