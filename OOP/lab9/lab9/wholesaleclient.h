#ifndef WHOLESALECLIENT_H
#define WHOLESALECLIENT_H

#include "regularwholesaleclient.h"
#include "vipwholesaleclient.h"

#include "QVector"
#include "QMap"
#include "QString"

class WholeSaleClient {
protected:
    QVector<QString> cart;
    QVector<QString> list;
    QMap<QString, double> check;
    double money;

    void withdrawMoney(double money) { this->money -= money; };

    void addToList(QString item) { this->list.append(item); };
    void addToCheck(QString item, double price) {this->check.insert(item, price); };

    QVector<QString> getCart() { return this->cart; };
    QVector<QString> getList() { return this->list; };
    QMap<QString, double> getCheck() { return this->check; };
public:
    virtual ~WholeSaleClient();

    virtual double summarize() = 0;

    void buy(QString item , double price);
    void addToCart(QString item);
    void removeFromCart(QString item);
    bool isInCart(QString item);
    bool isEverythingBought();

    double getMoney() { return this->money; };
};

#endif // WHOLESALECLIENT_H
