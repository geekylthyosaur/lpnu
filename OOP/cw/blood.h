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

    int     getPressureHigh()   const { return this->mPressureHigh; }
    int     getPressureLow()    const { return this->mPressureLow; }
    bool    getRhD()            const { return this->mRhD; }
    int     getType()           const { return this->mType; }

    QString getPressureStr();
    QString getRhDStr();
    QString getTypeStr();

    bool operator > (const Blood& other) const { return this->mPressureLow + this->mPressureHigh > other.mPressureHigh + other.mPressureLow; }
    bool operator < (const Blood& other) const { return this->mPressureLow + this->mPressureHigh < other.mPressureHigh + other.mPressureLow; }
};

#endif // BLOOD_H
