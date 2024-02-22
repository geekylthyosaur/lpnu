#ifndef TERMDEPOSIT_H
#define TERMDEPOSIT_H

#include "deposit.h"

class TermDeposit : public Deposit
{
public:
    TermDeposit();
    TermDeposit(double money, double rate, int term):
        Deposit(money, rate, term)
    {};

    static QString print() { return "TermDeposit"; };

    double calculateProfit();
    double calculateProfit(int months);
};

#endif // TERMDEPOSIT_H
