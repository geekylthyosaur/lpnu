#include "termdeposit.h"

TermDeposit::TermDeposit() {}

double TermDeposit::calculateProfit() {
    return money * (rate / 100);
}

double TermDeposit::calculateProfit(int months) {
    if (months <= term)
        return (money * (rate / 100)) * (months / double(term));
    else
        return money * (rate / 100);
}
