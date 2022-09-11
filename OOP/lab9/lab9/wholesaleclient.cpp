#include "wholesaleclient.h"

double WholeSaleClient::summarize() {
    double sum = 0;
    for (double i : getCheck()) sum += i;
    return sum;
}

void WholeSaleClient::buy(QString item, double price) {
    addToCart(item);
    addToCheck(item, price);
    withdrawMoney(price);
}

void WholeSaleClient::addToCart(QString item) {
    this->cart.append(item);
}

void WholeSaleClient::removeFromCart(QString item) {
    this->cart.removeAt(this->cart.indexOf(item));
}

bool WholeSaleClient::isInCart(QString item) {
    return this->cart.contains(item);
}

bool WholeSaleClient::isEverythingBought() {
    return this->cart == this->list ? true : false;
}
