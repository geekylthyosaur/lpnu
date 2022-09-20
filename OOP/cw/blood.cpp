#include "blood.h"

Blood::Blood(int pressureH, int pressureL, bool rhd, Type type)
{
    this->mPressureLow = pressureL;
    this->mPressureHigh = pressureH;
    this->mRhD = rhd;
    this->mType = type;
}

QString Blood::getPressure()
{
    return QString::number(this->mPressureHigh) + "/" + QString::number(this->mPressureLow);
}

QString Blood::getType()
{
    return QString::fromStdString("");
}
