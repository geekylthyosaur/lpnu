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

int List::partition(int start, int end)
{
    Person pivot = this->mVec[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (*this->get(i) <= pivot)
            count++;
    }

    int pivotIndex = start + count;
    this->mVec.swapItemsAt(pivotIndex, start);

    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (this->mVec[i] <= pivot) {
            i++;
        }

        while (this->mVec[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            this->mVec.swapItemsAt(i, j);
            i += 1;
            j -= 1;
        }
    }

    return pivotIndex;
}

void List::quickSort(int columnIndex, int start, int end)
{
    if (start < end)
    {
        int pivot = this->partition(start, end);

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
