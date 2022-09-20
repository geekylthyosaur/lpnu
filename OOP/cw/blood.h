#ifndef BLOOD_H
#define BLOOD_H

#include "QString"

const QString UNIVERSAL_DONOR = "O-";
const QString UNIVERSAL_RECIPIENT = "AB+";

enum Type {
    O   = 1,
    A   = 2,
    B   = 3,
    AB  = 4,
};

class Blood
{
private:
    int mPressureHigh;
    int mPressureLow;
    bool mRhD;
    Type mType;

public:
    Blood() = default;
    Blood(int pressureH, int pressureL, bool rhd, Type type);

    QString getPressure();
    QString getType();

    bool operator > (Blood b) { return this->mPressureLow + this->mPressureHigh > b.mPressureHigh + b.mPressureLow; }
    bool operator < (Blood b) { return this->mPressureLow + this->mPressureHigh < b.mPressureHigh + b.mPressureLow; }
};

#endif // BLOOD_H
