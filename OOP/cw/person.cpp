#include "person.h"
#include "QDebug";

Person::Person(int n, QString surname, int age, Blood* blood, int hr)
{
    this->mN = n;
    this->mSurname = surname;
    this->mAge = age;
    this->mBlood = blood;
    this->mHeartRate = hr;
}

Person::Person(QString person)
{
    auto tokens = person.split(",");
    this->mN = tokens[0].toInt();
    this->mSurname = tokens[1];
    this->mAge = tokens[2].toInt();
    this->mBlood = new Blood(tokens[3]);
    this->mHeartRate = tokens[4].toInt();
    qDebug() << this->mN << this->mSurname << this->mAge << this->mBlood->getPressure() << this->mBlood->getType() << this->mHeartRate << Qt::endl;
}

