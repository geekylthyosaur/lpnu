#ifndef LIST_H
#define LIST_H

#include "QVector"
#include "QFile"

#include "person.h"

class List
{
private:
    QVector<Person*> mVec;

public:
    List() = default;

    void push(Person* p);
    Person* get(int i);

    friend void operator << (QFile &output, const List* l);
    friend void operator >> (QFile &input, List* l);
};

#endif // LIST_H
