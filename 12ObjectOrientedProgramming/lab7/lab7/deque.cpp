#include "deque.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Deque::~Deque() {
    Node* head = this->head;
    while (head != nullptr) {
        Node* tmp = head;
        head = head->getNext();
        free(tmp);
    }
    this->head = this->tail = nullptr;
}

bool Deque::isEmpty() const {
    return head == nullptr && tail == nullptr;
}

void Deque::display() const {
    Node* head = this->head;
    while (head != nullptr) {
        cout << head->getValue() << " ";
        head = head->getNext();
    }
    cout << endl;
    Node* tail = this->tail;
    while (tail != nullptr) {
        cout << tail->getValue() << " ";
        tail = tail->getPrev();
    }
    cout << endl;
}

void Deque::clear() {
    Deque::~Deque();
}

int Deque::countValues() const {
    Node* head = this->head;
    int count = 0;
    while (head != nullptr) {
        count++;
        head = head->getNext();
    }
    return count;
}

int Deque::maxValue() const {
    Node* head = this->head;
    int max = INT32_MIN;
    while (head != nullptr) {
        if (head->getValue() > max) max = head->getValue();
        head = head->getNext();
    }
    return max;
}

int Deque::minValue() const {
    Node* head = this->head;
    int min = INT32_MAX;
    while (head != nullptr) {
        if (head->getValue() < min) min = head->getValue();
        head = head->getNext();
    }
    return min;
}

double Deque::avgValue() const {
    Node* head = this->head;
    if (this->countValues() == 0) return 0.f;
    double sum = 0;
    while (head != nullptr) {
        sum += head->getValue();
        head = head->getNext();
    }
    return sum / this->countValues();
}

void Deque::multiply(int n) {
    Node* head = this->head;
    while (head != nullptr) {
        head->setValue(head->getValue() * n);
        head = head->getNext();
    }
}

void Deque::operator<(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == nullptr) return;
    node = new(node) Node(value);
    if (head == nullptr && tail == nullptr) {
        head = node;
        tail = head;
        return;
    }
    Node* tmp = head;
    head = node;
    head->setNext(tmp);
    tmp->setPrev(head);
}

void Deque::operator>(int value) {
    if (head == nullptr && tail == nullptr) {
        Node* node = (Node*)malloc(sizeof(Node));
        if (node == nullptr) return;
        tail = new(node) Node(value);
        head = tail;
        return;
    }
    Node* tmp = tail;
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == nullptr) return;
    tail->setNext(new(node) Node(value));
    tail = tail->getNext();
    tail->setPrev(tmp);
}

void Deque::operator--() {
    if (head == nullptr) return;
    Node* tmp = head;
    head = head->getNext();
    if (head != nullptr) head->setPrev(nullptr);
    else tail = head = nullptr;
    free(tmp);
}

void Deque::operator--(int) {
    if (tail == nullptr) return;
    Node* tmp = tail;
    tail = tail->getPrev();
    if (tail != nullptr) tail->setNext(nullptr);
    else tail = head = nullptr;
    free(tmp);
}

void Deque::operator*=(int n) {
    Node* head = this->head;
    while (head != nullptr) {
        head->setValue(head->getValue() * n);
        head = head->getNext();
    }
}

Deque* Deque::operator=(Deque& d) {
    Deque* deq = new Deque(d.head, d.tail);
    return deq;
}

void Deque::operator>>(QTableWidget* table) {
    Node* head = this->head;
    int i = 0;
    table->setColumnCount(0);
    while (head != nullptr) {
        table->insertColumn(i);
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(QString::number(head->getValue()));
        table->setItem(0, i, item);
        i += 1;
        head = head->getNext();
    }
}

void Deque::operator<<(QTableWidget* table) {
    for (int i = 0; i < table->columnCount(); i++) {
        *this < table->item(0, i)->text().toInt();
    }
}

void Deque::operator>>(QListWidget* list) {
    Node* head = this->head;
    list->clear();
    while (head != nullptr) {
        QListWidgetItem* item = new QListWidgetItem();
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setText(QString::number(head->getValue()));
        list->addItem(item);
        head = head->getNext();
    }
}

void Deque::operator<<(QListWidget* list) {
    for (int i = 0; i < list->count(); i++) {
        *this < list->item(i)->text().toInt();
    }
}

void Deque::operator>>(QLineEdit* line) {
    Node* head = this->head;
    line->clear();
    while (head != nullptr) {
        line->setText(line->text() + " " + QString::number(head->getValue()));
        head = head->getNext();
    }
}

void Deque::operator<<(QLineEdit *line) {
    stringstream ss(line->text().toStdString());
    string n;
    while (ss >> n) {
        *this < QString::fromStdString(n).toInt();
    }
}
