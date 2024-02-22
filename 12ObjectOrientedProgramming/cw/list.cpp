#include "list.h"
#include "QTextStream"
#include "QDebug"

using namespace std;

void List::push(Person p)
{
    this->mVec.append(p);
}

Person * List::get(int i)
{
    return &this->mVec[i];
}

int List::len() const
{
    return this->mVec.length();
}

int List::partition(int columnIndex, int start, int end)
{
    int pivotIndex = end;

    int i = (start - 1);

    for (int j = start; j < end; j++) {
        if (this->mVec[pivotIndex].compare(this->mVec[j], columnIndex)) {
          i++;
          this->mVec.swapItemsAt(i, j);
        }
    }

    this->mVec.swapItemsAt(i + 1, end);

    return (i + 1);
}

void List::quickSort(int columnIndex, int start, int end)
{
    if (start < end)
    {
        int pivot = this->partition(columnIndex, start, end);

        this->quickSort(columnIndex, start, pivot-1);
        this->quickSort(columnIndex, pivot+1, end);
    }
}

void List::clear()
{
    this->mVec.clear();
}

// file << list
void operator << (QFile &output, const List* l)
{
    if (output.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&output);
        for (Person p : l->mVec)
        {
            stream << &p;
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
            Person p = Person(line);
            l->push(p);
        }
        input.close();
    }
}
