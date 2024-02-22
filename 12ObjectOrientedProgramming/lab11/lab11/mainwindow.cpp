#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <queue>
#include <stack>
#include <iostream>

using namespace std;

priority_queue<int> * q;
priority_queue<int> * q2;
stack<int> * s = new stack<int>();
vector<int> * v = new vector<int>();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_b1_clicked() {
    q = new priority_queue<int>();
    for (QString item : ui->edit1->text().split(" ")) q->push(item.toInt());
}

void MainWindow::on_b2_clicked() {
    priority_queue<int> queue = *q;
    ui->label2->clear();
    for (; !queue.empty(); queue.pop())
        ui->label2->setText(ui->label2->text() + " " + QString::number(queue.top()));
}

void MainWindow::on_b3_clicked() {
    q->pop();
    q->pop();
    q->push(142);
}

void MainWindow::on_b4_clicked() {
    priority_queue<int> queue = *q;
    ui->label4->clear();
    vector<int> v;
    while (!queue.empty()) {
      v.push_back(queue.top());
      queue.pop();
    }
    for (vector<int>::iterator i = v.begin(); i != v.end(); i++)
        ui->label4->setText(ui->label4->text() + " " + QString::number(*i));
}

void MainWindow::on_b5_clicked() {
    q2 = new priority_queue<int>();
    for (QString item : ui->edit5->text().split(" ")) q2->push(item.toInt());
}

void MainWindow::on_b6_clicked() {
    priority_queue<int> queue = *q;
    priority_queue<int> queue2 = *q2;
    priority_queue<int> * nq = new priority_queue<int>();
    for (int i = 0; i<ui->edit62->text().toInt(); i++) {
        nq->push(queue.top());
        queue.pop();
    }
    for (int n = 0; n<ui->edit6->text().toInt(); n++) {
        queue.pop();
    }
    while (!queue.empty()) {
        nq->push(queue.top());
        queue.pop();
    }
    while (!queue2.empty()) {
        nq->push(queue2.top());
        queue2.pop();
    }
    q = new priority_queue<int>(*nq);
}

void MainWindow::on_b7_clicked() {
    priority_queue<int> queue = *q;
    priority_queue<int> queue2 = *q2;
    ui->label7->clear();
    ui->label7->setText("(1) ");
    for (; !queue.empty(); queue.pop())
        ui->label7->setText(ui->label7->text() + " " + QString::number(queue.top()));
    ui->label7->setText(ui->label7->text() + " (2) ");
    for (; !queue2.empty(); queue2.pop())
        ui->label7->setText(ui->label7->text() + " " + QString::number(queue2.top()));
}

void MainWindow::on_b8_clicked() {
    priority_queue<int> queue = *q;

    ui->label8->clear();
    for (; !queue.empty(); queue.pop())
        ui->label8->setText(ui->label8->text() + " " + QString::number(queue.top()));
}

void MainWindow::on_b9_clicked() {
    priority_queue<int> queue = *q;
    ui->label9->clear();
    vector<int> v;
    while (!queue.empty()) {
        if (queue.top() > ui->edit9->text().toInt()) v.push_back(queue.top());
        queue.pop();
    }
    for (int i : v)
        ui->label9->setText(ui->label9->text() + " " + QString::number(i));
}

void MainWindow::on_b10_clicked() {
    priority_queue<int> queue = *q;
    while (!queue.empty()) {
        if (queue.top() > ui->edit10->text().toInt()) s->push(queue.top());
        queue.pop();
    }
}

void MainWindow::on_b11_clicked() {
    stack<int> stack = *s;

    ui->label11->clear();
    for (; !stack.empty(); stack.pop())
        ui->label11->setText(ui->label11->text() + " " + QString::number(stack.top()));
}

void MainWindow::on_b12_clicked() {
    priority_queue<int> queue = *q;

    vector<int> v;
    while (!queue.empty()) {
        v.push_back(queue.top());
        queue.pop();
    }
    std::priority_queue<int, std::vector<int>, std::greater<int>> sq(v.begin(), v.end());
    ui->label13->clear();
    for (; !sq.empty(); sq.pop())
        ui->label13->setText(ui->label13->text() + " " + QString::number(sq.top()));
}

void MainWindow::on_b13_clicked() {
    priority_queue<int> queue = *q;
    stack<int> stack = *s;

    while (!queue.empty()) {
        v->push_back(queue.top());
        queue.pop();
    }
    while (!stack.empty()) {
        v->push_back(stack.top());
        stack.pop();
    }
}

void MainWindow::on_b14_clicked() {
    ui->label16->clear();
    for (int i : *v)
        ui->label16->setText(ui->label16->text() + " " + QString::number(i));
}

void MainWindow::on_b15_clicked() {
    ui->label17->setText(QString::number(std::count_if(v->begin(), v->end(), [](int i){return i > 5;})));
}

