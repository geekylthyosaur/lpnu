#ifndef BLOOD_H
#define BLOOD_H

#include "QString"

const QString UNIVERSAL_DONOR = "O-";
const QString UNIVERSAL_RECIPIENT = "AB+";

class Blood
{
private:
    int mPressureHigh;
    int mPressureLow;
    bool mRhD;
    int mType;

public:
    Blood() = default;
    Blood(QString s);
    Blood(int pressureH, int pressureL, bool rhd, int type);

    QString getPressure();
    QString getRhD();
    QString getType();

    bool operator > (Blood b) { return this->mPressureLow + this->mPressureHigh > b.mPressureHigh + b.mPressureLow; }
    bool operator < (Blood b) { return this->mPressureLow + this->mPressureHigh < b.mPressureHigh + b.mPressureLow; }
};

#endif // BLOOD_H
