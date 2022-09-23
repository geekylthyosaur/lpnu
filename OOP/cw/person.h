#ifndef PERSON_H
#define PERSON_H

#include "QString"
#include "QFile"
#include "blood.h"

class Person
{
private:
    int     mN;
    QString mSurname;
    int     mAge;
    Blood * mBlood;
    int     mHeartRate;
public:
    Person() = default;
    Person(int n, QString surname, int age, Blood* blood, int hr);
    Person(const Person &other);
};

#endif // PERSON_H
