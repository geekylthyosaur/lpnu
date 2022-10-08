#ifndef LIST_H
#define LIST_H

#include "QVector"
#include "QFile"

#include "person.h"

class List
{
private:
    QVector<Person> mVec;
    int      partition(int columnIndex, int start, int end);

public:
    List() = default;

    void     quickSort(int columnIndex, int start, int end);
    void     push(Person p);
    void     clear();
    Person * get(int i);
    int      len() const;

    friend void operator << (QFile &output, const List* l);
    friend void operator >> (QFile &input, List* l);
};

#endif // LIST_H
