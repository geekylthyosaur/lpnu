#include "list.h"
#include "QTextStream"

void List::push(Person* p)
{
    this->mVec.append(p);
}

Person* List::get(int i)
{
    return this->mVec.at(i);
}

// file << list
void operator << (QFile &output, const List* l)
{
    if (output.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&output);
        for (Person* p : l)
        {
            stream << p->mN << "," << p->mSurname << "," << p->mAge << "," << p->mBlood->getPressure() << " " << p->mBlood->getType() << p->mHeartRate << endl;
        }
    }
}

// file >> list
void operator >> (QFile &input, List* l)
{
    if (input.open(QIODevice::ReadOnly))
    {
        QTextStream in(&input);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            auto tokens = line.split(",");
            int n = tokens[0].toInt();
            QString surname = tokens[1];
            int age = tokens[2].toInt();
            Blood* blood = new Blood(tokens[3]);
            int heart_rate = tokens[4].toInt();
            Person* p = new Person(n, surname, age, blood, heart_rate);
            l->push(p);
        }
        input.close();
    }
}
