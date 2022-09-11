#ifndef ELECTRICITYBILL_H
#define ELECTRICITYBILL_H

#include <period.h>
#include "QTableWidget"

class ElectricityBill
{
protected:
    std::vector<Period> list;
public:
    ElectricityBill();
    void addPeriod(QDateTime start, QDateTime end, double consumpion);
    void printList(QTableWidget *table);
    std::vector<Period> * getList() { return &list; };
    static QString print();
};

#endif // ELECTRICITYBILL_H
