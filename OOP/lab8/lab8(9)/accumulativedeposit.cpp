#include "accumulativedeposit.h"

AccumulativeDeposit::AccumulativeDeposit() {}

double AccumulativeDeposit::calculateProfit() {
    double money = this->money;
    for (int m = 0; m < term; m++) {
        money += (money * (rate / 100)) / 2;
    }
    return (money * (rate / 100)) / 2;
}

double AccumulativeDeposit::calculateProfit(int months) {
    double money = this->money;
    for (int m = 0; m < months; m++) {
        money += (money * (rate / 100)) / 2;
    }
    return (money * (rate / 100)) * (months / double(term)) / 2;
}
