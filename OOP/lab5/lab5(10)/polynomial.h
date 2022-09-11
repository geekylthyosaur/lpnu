#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

struct Roots{
    int n;
    double x1;
    double x2;
};

class Polynomial {
private:
    double m_a0;
    double m_a1;
    double m_a2;
public:
    Polynomial():
        Polynomial(0.f, 0.f, 0.f)
    {};
    Polynomial(double a0, double a1):
        Polynomial(a0, a1, 0.f)
    {};
    Polynomial(double a0, double a1, double a2):
        m_a0(a0),
        m_a1(a1),
        m_a2(a2)
    {};

    double find(double x);
    double findDerivative(double x);
    double findIntegral(double a, double b);
    Roots findRoots();
    void add(Polynomial polynomial);
    void multiply(double n);

    double getA0() const { return m_a0; };
    double getA1() const { return m_a1; };
    double getA2() const { return m_a2; };
    void setA0(double a0);
    void setA1(double a1);
    void setA2(double a2);
};

#endif // POLYNOMIAL_H
