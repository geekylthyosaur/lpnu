#include "calculator.h"

Calculator::Calculator() {}

void Calculator::calculate() {
    switch (this->op) {
    case Divide:
        this->result = this->lValue / this->rValue;
        break;
    case Multiply:
        this->result = this->lValue * this->rValue;
        break;
    case Substract:
        this->result = this->lValue - this->rValue;
        break;
    case Add:
        this->result = this->lValue + this->rValue;
        break;
    case Sqrt:
        this->result = sqrt(this->lValue);
        break;
    case Mod:
        this->result = fmod(this->lValue, this->rValue);
        break;
    case Pow:
        this->result = pow(this->lValue, this->rValue);
        break;
    case Sin:
        this->result = sin(this->lValue);
        break;
    case Cos:
        this->result = cos(this->lValue);
        break;
    case Tan:
        this->result = tan(this->lValue);
        break;
    };
}

void Calculator::reset() {
    this->lValue = NAN;
    this->rValue = NAN;
    this->result = NAN;
}
