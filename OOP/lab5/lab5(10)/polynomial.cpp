#include "polynomial.h"
#include <math.h>

double Polynomial::find(double x) {
    return m_a0*x*x + m_a1*x + m_a2;
}

double Polynomial::findDerivative(double x) {
    return 2*m_a0*x + m_a1;
}

double Polynomial::findIntegral(double a, double b) {
    return (m_a0/3)*(b*b*b-a*a*a) + (m_a1/2)*(b*b-a*a) + m_a2;
}

Roots Polynomial::findRoots() {
    double d = m_a1*m_a1 - 4*m_a0*m_a2;
    if (d < 0) return Roots {0, NAN, NAN};
    double x1 = ((-1)*m_a1 + sqrt(d)) / (2*m_a0);
    double x2 = ((-1)*m_a1 - sqrt(d)) / (2*m_a0);
    return Roots {2, x1, x2};
}

void Polynomial::add(Polynomial polynomial) {
    m_a0 += polynomial.getA0();
    m_a1 += polynomial.getA1();
    m_a2 += polynomial.getA2();
}

void Polynomial::multiply(double n) {
    m_a0 *= n;
    m_a1 *= n;
    m_a2 *= n;
}

void Polynomial::setA0(double a0) { m_a0 = a0; }
void Polynomial::setA1(double a1) { m_a1 = a1; }
void Polynomial::setA2(double a2) { m_a2 = a2; }
