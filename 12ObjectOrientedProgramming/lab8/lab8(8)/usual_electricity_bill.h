#ifndef USUALELECRICITYBILL_H
#define USUALELECRICITYBILL_H

#include "electricity_bill.h"

class UsualElectricityBill : public ElectricityBill
{
public:
    const double price = 1.44;
    UsualElectricityBill();
    double calculate();
    static QString print();
};

#endif // USUALELECRICITYBILL_H
