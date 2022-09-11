#ifndef SPECIALELECTRICITYBILL_H
#define SPECIALELECTRICITYBILL_H

#include "electricity_bill.h"

class SpecialElectricityBill : public ElectricityBill
{
public:
    const double specialPrice = 1.44;
    const double commonPrice = 1.68;
    SpecialElectricityBill();
    double calculate();
    static QString print();
};

#endif // SPECIALELECTRICITYBILL_H
