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
    auto tokens = person.split(",");
    this->mN = tokens[0].toInt();
    this->mSurname = tokens[1];
    this->mAge = tokens[2].toInt();
    this->mBlood = new Blood(tokens[3]);
    this->mHeartRate = tokens[4].toInt();
}

void operator << (QTextStream &output, const Person* p)
{
    output << p->getN()
           << ","
           << p->getSurname()
           << ","
           << p->getAge()
           << ","
           << p->getBlood()->getPressure()
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
