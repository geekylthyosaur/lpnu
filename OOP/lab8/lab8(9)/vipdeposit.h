#ifndef VIPDEPOSIT_H
#define VIPDEPOSIT_H

#include "deposit.h"

class VIPDeposit : public Deposit {
private:
    double rateIncCoef;
    double maxRate;
public:
    VIPDeposit();
    VIPDeposit(double rateIncCoef, double maxRate, double money, double rate, int term):
        Deposit(money, rate, term),
        rateIncCoef(rateIncCoef),
        maxRate(maxRate)
    {};

    double getRateIncCoef() { return rateIncCoef; };
    double getMaxRate() { return maxRate; };


    void setMoney(double money) { this->money = money; };
    void setRate(double rate) { this->rate = rate; };
    void setRateIncCoef(double rateIncCoef) { this->rateIncCoef = rateIncCoef; };
    void setMaxRate(double maxRate) { this->maxRate = maxRate; };

    void putMoney(double money) { Deposit::money = Deposit::money + money; };
    static QString print() { return "VIPDeposit"; };

    double calculateProfit();
    double calculateProfit(int months);
};

#endif // VIPDEPOSIT_H
