#include "multizone_electricity_bill.h"

MultizoneElectricityBill::MultizoneElectricityBill() {}

double MultizoneElectricityBill::calculate() {
    double res = 0;
    for (Period p : list) {
        QDateTime start = p.getStartDateTime();
        QDateTime end = p.getEndDateTime();

        for (QDateTime dt = start; dt < end; dt = dt.addSecs(3600)) {
            if (dt.time() >= QTime::fromString("00:00", "HH:mm") && dt.time() < QTime::fromString("06:00", "HH:mm")) {
                res += p.getConsumption() * this->lowestPrice;
            } else if (dt.time() >= QTime::fromString("06:00", "HH:mm") && dt.time() < QTime::fromString("18:00", "HH:mm")) {
                res += p.getConsumption() * this->commonPrice;
            } else if (dt.time() >= QTime::fromString("18:00", "HH:mm") && dt.time() < QTime::fromString("23:59", "HH:mm")) {
                res += p.getConsumption() * this->highestPrice;
            }
        }
    }

    return res;
}

QString MultizoneElectricityBill::print() {
    return "MultizoneElectricityBill";
}

