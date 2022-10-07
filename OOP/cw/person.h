#ifndef PERSON_H
#define PERSON_H

#include "QString"
#include "QTextStream"
#include "blood.h"
#include "QDebug"

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

    int     getN()          const { return this->mN;         }
    QString getSurname()    const { return this->mSurname;   }
    int     getAge()        const { return this->mAge;       }
    Blood * getBlood()      const { return this->mBlood;     }
    int     getHeartRate()  const { return this->mHeartRate; }

    friend void operator << (QTextStream &output, const Person* p);
    friend void operator >> (QTextStream &input, Person* p);

    bool operator < (const Person& other) const
    {
        return this->mHeartRate < other.getHeartRate()
               &&
               this->mBlood->getRhD() == other.getBlood()->getRhD();
    }
    bool operator > (const Person& other) const { return this->mN > other.getN(); }

    bool operator <= (const Person& other) const { return this->mN <= other.getN(); }
    bool operator >= (const Person& other) const { return this->mN >= other.getN(); }
};

#endif // PERSON_H
