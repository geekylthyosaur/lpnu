#include "blood.h"

#include "QStringList"
#include "QDebug"

Blood::Blood(int pressureH, int pressureL, bool rhd, int type)
{
    this->mPressureLow = pressureL;
    this->mPressureHigh = pressureH;
    this->mRhD = rhd;
    this->mType = type;
}

Blood::Blood(QString s)
{
    QStringList tokens = s.split(" ");
    auto pressure_tokens = tokens[0].split("/");
    this->mPressureHigh = pressure_tokens[0].toInt();
    this->mPressureLow = pressure_tokens[1].toInt();
    if (tokens[1].right(1) == "+")
        this->mRhD = true;
    else if (tokens[1].right(1) == "-")
        this->mRhD = false;
    tokens[1].chop(1);
    if (tokens[1] == "O")
        this->mType = 1;
    else if (tokens[1] == "A")
        this->mType = 2;
    else if (tokens[1] == "B")
        this->mType = 3;
    else if (tokens[1] == "AB")
        this->mType = 4;
}

QString Blood::getPressure()
{
    return QString::number(this->mPressureHigh) + "/" + QString::number(this->mPressureLow);
}

QString Blood::getRhD()
{
    if (this->mRhD)
        return QString::fromStdString("+");
    else
        return QString::fromStdString("-");
}

QString Blood::getType()
{
    switch (this->mType)
    {
    case 1:
        return QString::fromStdString("O");
    case 2:
        return QString::fromStdString("A");
    case 3:
        return QString::fromStdString("B");
    case 4:
        return QString::fromStdString("AB");
    default:
        return QString::fromStdString("ERROR");
    }
}
