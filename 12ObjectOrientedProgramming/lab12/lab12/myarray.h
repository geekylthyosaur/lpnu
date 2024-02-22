#ifndef MYARRAY_H
#define MYARRAY_H

#include "QString"

class MyArray {
private:
    double * array;
    int size;
public:
    MyArray(int size):
        array(new double[size]),
        size(size)
    {};
    MyArray(QString s) noexcept(false);
    double max();
    double min();
    double avg();

    void write(QString filename) noexcept(false);
    static MyArray * read(QString filename) noexcept(false);

    int getSize() { return this->size; };

    double get(int i) noexcept(false);
    void set(int i, double v) noexcept(false);
};

#endif // MYARRAY_H
