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
    Person(QString person);
    Person(int n, QString surname, int age, Blood* blood, int hr);
    Person(const Person &other);

    int     getN()          const { return this->mN; }
    QString getSurname()    const { return this->mSurname; }
    int     getAge()        const { return this->mAge; }
    Blood*  getBlood()      const { return this->mBlood; }
    int     getHeartRate()  const { return this->mHeartRate; }
};

#endif // PERSON_H
