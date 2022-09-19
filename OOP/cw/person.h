#ifndef PERSON_H
#define PERSON_H

#include "QString"
#include "blood.h"

class Person
{
private:
    int     mN;
    QString mSurname;
    QString mName;
    int     mAge;
    Blood   blood;
    int     mHeartRate;
public:
    Person();
    Person(int n, QString surname, QString name, int age, Blood blood, int hr);
    Person(const Person &other);
    friend ostream & operator << (ostream &out, const Person &p);
    friend istream & operator >> (istream &in,  Person &p);
};

#endif // PERSON_H
