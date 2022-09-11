#include "special_electricity_bill.h"

SpecialElectricityBill::SpecialElectricityBill() {}

double SpecialElectricityBill::calculate() {
    double res = 0;
    double consumption = 0;
    bool more = false;
    for (Period p : this->list) {
        double tmp = p.getConsumption();
        for (int i = 0; tmp > 0; i++) {
            consumption += 0.01;
            tmp -= 0.01;
            if (consumption > 250) more = true;
        }

        if (!more) res += this->specialPrice * p.asHours() * consumption;
        else res += this->commonPrice * p.asHours() * (consumption - 250);
    }
    return res;
}


QString SpecialElectricityBill::print() {
    return "SpecialElectricityBill";
}


