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
    int mPressureLow;
    int mPressureHigh;
    bool mRhD;
    Type mType;

public:
    Blood(int pressureL, int pressureH, bool rhd, Type type);

    QString getPressure(); // -> 120/80
    QString getType(); // -> AB+

    bool operator > (Blood* b) { return this->mPressureLow + this->mPressureHigh > b->mPressureHigh + b->mPressureLow; }
    bool operator < (Blood* b);
    bool operator == (Blood* b);
};

#endif // BLOOD_H
