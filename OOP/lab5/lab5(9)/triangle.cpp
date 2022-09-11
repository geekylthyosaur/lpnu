#include "triangle.h"
#include <math.h>

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

double Triangle::perimeter() {
    return a + b + c;
}

Values Triangle::medians() {
    Values medians;
    medians.a = sqrt((2*b*b + 2*c*c - a*a) / 4);
    medians.b = sqrt((2*a*a + 2*c*c - b*b) / 4);
    medians.c = sqrt((2*a*a + 2*b*b - c*c) / 4);
    return medians;
}

int Triangle::isRight() {
    return angles().a == 90.f || angles().b == 90.f || angles().c == 90.f;
}

void Triangle::increaseSides(double n) {
    a += n;
    b += n;
    c += n;
}
