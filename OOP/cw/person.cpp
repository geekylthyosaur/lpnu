#include "person.h"

Person::Person(int n, QString surname, int age, Blood* blood, int hr)
{
    this->mN = n;
    this->mSurname = surname;
    this->mAge = age;
    this->mBlood = blood;
    this->mHeartRate = hr;
}

