#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <math.h>

class Calculator
{
public:
    enum operation {
        Divide,
        Multiply,
        Add,
        Substract,
        Sqrt,
        Mod,
        Pow,
        Sin,
        Cos,
        Tan,
    };
    Calculator();
    const double PI = M_PI;
    const double E = M_E;
    double lValue = NAN;
    double rValue = NAN;
    double result = NAN;
    operation op;
    void calculate();
    void reset();
};

#endif // CALCULATOR_H
