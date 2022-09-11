#ifndef PERIOD_H
#define PERIOD_H

#include "QDateTime"
#include "QString"

class Period {
private:
    QDateTime startDateTime;
    QDateTime endDateTime;
    double consumption;
public:
    Period(QDateTime start, QDateTime end, double consumption):
        startDateTime(start),
        endDateTime(end),
        consumption(consumption)
    {};
    double asHours();
    QDateTime getStartDateTime() { return startDateTime; };
    QDateTime getEndDateTime() { return endDateTime; };
    double getConsumption() { return consumption; };
};

#endif // PERIOD_H
