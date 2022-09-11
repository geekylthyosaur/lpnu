#include "usual_electricity_bill.h"

UsualElectricityBill::UsualElectricityBill() {}

double UsualElectricityBill::calculate() {
    double res = 0;
    for (Period p : this->list) {
        res += this->price * p.asHours() * p.getConsumption();
    }
    return res;
}

QString UsualElectricityBill::print() {
    return "UsualElectricityBill";
}
