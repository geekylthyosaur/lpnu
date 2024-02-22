#ifndef ARRAY_H
#define ARRAY_H

#include "QLabel"
#include "iostream"
template<class T>
class Array {
private:
    T * array;
    int lastIndex;
public:
    Array(int size) {
        array = new T[size];
        lastIndex = 0;
    };

    double sum() {
        double sum = 0;
        for (int i = 0; i < this->lastIndex; i++) {
            sum += this->get(i).length();
        }
        return sum;
    };
    T max() {
        T max;
        for (int i = 0; i < this->lastIndex; i++)
            if (this->get(i) > max) max = this->get(i);
        return max;
    };
    void print(QLabel * label) {
        label->clear();
        if (this->lastIndex == 0) return;
        for (int i = 0; i < this->lastIndex; i++) {
            label->setText(label->text() + this->get(i).print() + " ");
        }
    };
    T get(int i) { return this->array[i]; };
    void set(int i, T v) { this->lastIndex += 1; this->array[i] = v; };
};

#endif // ARRAY_H
