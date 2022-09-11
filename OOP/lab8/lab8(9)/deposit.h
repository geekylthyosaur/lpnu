#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "QString"

class Deposit {
protected:
    double money;
    double rate;
    int term;
public:
    Deposit();
    Deposit(double money, double rate, int term):
        money(money),
        rate(rate),
        term(term)
    {};
    double getMoney() { return money; };
    double getRate() { return rate; };
    int getTerm() { return term; };

    static QString print() { return "Deposit"; };
};

#endif // DEPOSIT_H
