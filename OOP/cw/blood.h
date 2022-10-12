#ifndef BLOOD_H
#define BLOOD_H

#include "QString"

class Blood
{
private:
    int mPressureHigh;
    int mPressureLow;
    bool mRhD;
    int mType;

public:
    const QString BEST_DONOR = "O-";
    const QString BEST_RECIPIENT = "AB+";

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
