#include "list.h"
#include "QTextStream"
#include "QDebug"

using namespace std;

void List::push(Person * p)
{
    this->mVec.append(p);
}

Person * List::get(int i) const
{
    return this->mVec[i];
}

int List::len() const
{
    return this->mVec.length();
}

void List::quickSort(int columnIndex, int start, int end)
{
    if (start >= end)
        return;

    int p = this->partition(start, end);
    this->quickSort(columnIndex, start, p - 1);
    this->quickSort(columnIndex, p + 1, end);
}

int List::partition(int start, int end)
{
    Person * pivot = this->mVec[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (this->mVec[i] <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    std::swap(this->mVec[pivotIndex], this->mVec[start]);

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (this->mVec[i] <= pivot) {
            i++;
        }

        while (this->mVec[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            std::swap(this->mVec[i++], this->mVec[j--]);
        }
    }

    return pivotIndex;
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
