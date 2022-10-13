#include "person.h"
#include "QDebug"

Person::Person(int n, QString surname, int age, Blood* blood, int heartRate)
{
    this->mN = n;
    this->mSurname = surname;
    this->mAge = age;
    this->mBlood = blood;
    this->mHeartRate = heartRate;
}

Person::Person(QString person)
{
    QStringList tokens = person.split(",");
    if (tokens.length() != 5)
        throw 1;
    this->mN = tokens[0].toInt();
    this->mSurname = tokens[1];
    this->mAge = tokens[2].toInt();
    this->mBlood = new Blood(tokens[3]);
    this->mHeartRate = tokens[4].toInt();
}

Person::Person(const Person &other)
{
    this->mN = other.getN();
    this->mSurname = other.getSurname();
    this->mAge = other.getAge();
    this->mBlood = other.getBlood();
    this->mHeartRate = other.getHeartRate();
}

bool Person::compare(const Person& other, const int flag) const
{
    int thisPressure;
    int otherPressure;
    bool thisRhD;
    bool otherRhD;
    int thisType;
    int otherType;
    int thisHeartRate;
    int otherHeartRate;
    switch (flag)
    {
    case 0: // pressure
        thisPressure = this->getBlood()->getPressureHigh() + this->getBlood()->getPressureLow();
        otherPressure = other.getBlood()->getPressureHigh() + other.getBlood()->getPressureLow();
        return thisPressure > otherPressure;
    case 1: // rhd + type
        thisRhD = this->getBlood()->getRhD();
        otherRhD = other.getBlood()->getRhD();
        thisType = this->getBlood()->getType();
        otherType = other.getBlood()->getType();
        return thisRhD > otherRhD || thisType > otherType;
    case 2: //rhd + rate
        thisRhD = this->getBlood()->getRhD();
        otherRhD = other.getBlood()->getRhD();
        thisHeartRate = this->getHeartRate();
        otherHeartRate = other.getHeartRate();
        return thisRhD > otherRhD || thisHeartRate > otherHeartRate;
    }
    return false;
}

void operator << (QTextStream &output, const Person* p)
{
    output << p->getN()
           << ","
           << p->getSurname()
           << ","
           << p->getAge()
           << ","
           << p->getBlood()->getPressureStr()
           << " "
           << p->getBlood()->getType()
           << p->getBlood()->getRhD()
           << ","
           << p->getHeartRate()
           << Qt::endl;
}

void operator >> (QTextStream &input, Person * p)
{

}
