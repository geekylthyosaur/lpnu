#ifndef ACCUMULATIVEDEPOSIT_H
#define ACCUMULATIVEDEPOSIT_H

#include "deposit.h"

class AccumulativeDeposit : public Deposit
{
public:
    AccumulativeDeposit();
    AccumulativeDeposit(double money, double rate, int term):
        Deposit(money, rate, term)
    {};

    static QString print() { return "AccumulativeDeposit"; };

    double calculateProfit();
    double calculateProfit(int months);
};

#endif // ACCUMULATIVEDEPOSIT_H
