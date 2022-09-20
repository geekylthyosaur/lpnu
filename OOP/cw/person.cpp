#include "person.h"

Person::Person(int n, QString surname, QString name, int age, Blood* blood, int hr)
{
    this->mN = n;
    this->mSurname = surname;
    this->mName = name;
    this->mAge = age;
    this->mBlood = blood;
    this->mHeartRate = hr;
}

