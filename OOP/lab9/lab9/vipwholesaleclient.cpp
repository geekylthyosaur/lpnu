#include "vipwholesaleclient.h"

VIPWholeSaleClient::VIPWholeSaleClient(double money) {
    this->money = money;
}

double VIPWholeSaleClient::summarize() {
    double sum = 0;
    for (double i : this->getCheck()) sum += i;
    return sum * 0.95;
}
