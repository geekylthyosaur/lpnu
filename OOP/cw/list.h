#ifndef LIST_H
#define LIST_H

#include "QVector"
#include "person.h"

class List
{
private:
    QVector<Person*> mVec;

public:
    List() = default;

    friend void operator << (QFile &out, const Person &p);
    friend void operator >> (Person &p, QFile &in);
};

#endif // LIST_H
