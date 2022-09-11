#include "myarray.h"
#include "QFileDialog"
#include "QTextStream"
#include "iostream"

using namespace std;

MyArray::MyArray(QString s) noexcept(false) {
    if (s.isEmpty()) throw 3;
    QStringList list = s.split(" ");
    this->size = list.first().toInt();
    if (list.count() < this->size) throw 4;
    this->array = new double[this->size];
    int i = 0;
    bool ok;
    list.removeFirst();
    for (QString s : list) {
        this->array[i] = s.toDouble(&ok);
        if (!ok) throw 2;
        i++;
    }
}

double MyArray::max() {
    double max = -1000;
    for (int i = 0; i < this->size; i++)
        if (max < this->array[i]) max = array[i];
    return max;
}

double MyArray::min() {
    double min = 1000;
    for (int i = 0; i < this->size; i++)
        if (min > this->array[i]) min = array[i];
    return min;
}

double MyArray::avg() {
    double avg = 0;
    for (int i = 0; i < this->size; i++)
        avg += this->array[i];
    return avg / this->size;
}

double MyArray::get(int i) noexcept(false) {
    if (i >= this->size) throw 5;
    return this->array[i];
}

void MyArray::set(int i, double v) noexcept(false) {
    if (i >= this->size) throw 6;
    this->array[i] = v;
}

MyArray * MyArray::read(QString filename) noexcept(false) {
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw(1);

    QTextStream in(&file);
    QString line = in.readLine();
    file.close();
    return new MyArray(line);
}

void MyArray::write(QString filename) noexcept(false) {
    QFile file(filename);
    if (!file.open(QIODevice::Append | QIODevice::Text) || filename.isEmpty())
        throw(1);

    QString text = QString::number(this->size) + " ";
    for (int i = 0; i < this->size; i++)
        text += QString::number(this->get(i)) + " ";
    text = text.trimmed();
    text += "\nMax: " + QString::number(this->max()) + "\n";
    text += "Min: " + QString::number(this->min()) + "\n";
    text += "Avg: " + QString::number(this->avg());

    QTextStream out(&file);
    out << text << "\n";
    file.close();
}
