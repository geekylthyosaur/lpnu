#include "list.h"
#include "QTextStream"
#include "QDebug"

void List::push(Person * p)
{
    this->mVec.append(p);
}

Person * List::get(int i)
{
    return this->mVec[i];
}

int List::len()
{
    return this->mVec.length();
}

// file << list
void operator << (QFile &output, const List* l)
{
    if (output.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&output);
        for (Person* p : l->mVec)
        {
            stream << p;
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
            QString line = input.readLine();
            Person * p = new Person(line);
            l->push(p);
        }
        input.close();
    }
}
