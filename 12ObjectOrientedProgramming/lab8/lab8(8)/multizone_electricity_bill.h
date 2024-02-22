#ifndef MULTIZONEELECTRICITYBILL_H
#define MULTIZONEELECTRICITYBILL_H

#include "electricity_bill.h"

class MultizoneElectricityBill : public ElectricityBill
{
public:
    double const lowestPrice = 0.58;    // 00:00 - 06:00
    double const commonPrice = 1.44;    // 06:00 - 18:00
    double const highestPrice = 2.16;   // 18:00 - 00:00
    MultizoneElectricityBill();
    double calculate();
    static QString print();
};

#endif // MULTIZONEELECTRICITYBILL_H
