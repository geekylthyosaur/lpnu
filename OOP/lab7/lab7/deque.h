#ifndef DEQUE_H
#define DEQUE_H

#include "ui_mainwindow.h"
#include "QTableWidget"
#include "QListWidget"
#include "QLineEdit"

class Node {
private:
    int value;
    Node* prev;
    Node* next;
public:
    Node(int v):
        value(v),
        prev(nullptr),
        next(nullptr)
    {};
    int getValue() { return value; };
    Node* getPrev() { return prev; };
    Node* getNext() { return next; };
    void setValue(int v) { value = v; };
    void setPrev(Node* p) { prev = p; };
    void setNext(Node* n) { next = n; };
};

class Deque {
private:
    Node* head;
    Node* tail;
public:
    Deque():
        head(nullptr),
        tail(nullptr)
    {};
    Deque(Node* head, Node* tail) {
        this->head = head;
        this->tail = tail;
    };
    Deque(const Deque& d) { head = d.head; tail = d.tail; };
    ~Deque();
    void display() const;
    void clear();
    void multiply(int n);
    bool isEmpty() const;
    int countValues() const;
    int maxValue() const;
    int minValue() const;
    double avgValue() const;

    void operator<(int value); // pushFront
    void operator>(int value); // pushBack
    void operator--();          // prefix popFront
    void operator--(int);       // postfix popBack
    void operator *=(int n);
    Deque* operator=(Deque& d);

    void operator>>(QTableWidget* table);
    void operator<<(QTableWidget* table);
    void operator>>(QListWidget* list);
    void operator<<(QListWidget* list);
    void operator>>(QLineEdit* line);
    void operator<<(QLineEdit* line);
};

#endif // DEQUE_H
