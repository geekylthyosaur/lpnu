#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QTimer"
#include "QDebug"
#include "QStringList"

#include "threadargs.h"
#include "task.h"

#include "semaphore.h"

int threadCount;
int arrLen;
int* arr;
int sum;

Task** tasks;

sem_t sem;
pthread_spinlock_t spin;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    timer->start(50);
}

MainWindow::~MainWindow() {
    sem_destroy(&sem);
    pthread_spin_destroy(&spin);
    for (int i = 0; i < threadCount; i++) {
        tasks[i]->cancel();
    }
    delete ui;
}

void MainWindow::on_bStart_clicked() {
    threadCount = ui->leThreadCount->text().toInt();
    if (threadCount < 1) return;
    arrLen = ui->leArrLen->text().toInt();
    int semCount = ui->leSemCount->text().toInt();

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(threadCount);

    QStringList labels;
    labels << "Index" << "Status" << "Piority" << "Affinity";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    for (int i = 0; i < threadCount; i++) {
        for (int j = 0; j < 4; j++) {
            QTableWidgetItem * item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
            item->setText(QString());
            ui->tableWidget->setItem(i, j, item);
        }
    }

    if (sem_init(&sem, 0, semCount)) {
        qDebug() << "sem_init error!";
        return;
    }
    if (pthread_spin_init(&spin, 0)) {
        qDebug() << "spin_init error!";
        return;
    }

    tasks = new Task*[threadCount];
    arr = new int[arrLen];
    for (int i = 0; i < threadCount; i++) {
        tasks[i] = new Task(threadCount, i, arrLen, &sum, arr, &sem, &spin);
    }
}

void MainWindow::update() {
    ui->leSum->setText(QString::number(sum));

    for (int i = 0; i < threadCount; i++) {
        for (int j = 0; j < 4; j++) {
            QTableWidgetItem * item = ui->tableWidget->item(i, j);
            item->setTextAlignment(Qt::AlignCenter);
            switch (j) {
            case 0:
                item->setText(QString::number(tasks[i]->getThreadIndex()));
                break;
            case 1:
                if (tasks[i]->getStatus() == Running) item->setText(QString::fromStdString("Running"));
                if (tasks[i]->getStatus() == Detached) item->setText(QString::fromStdString("Detached"));
                if (tasks[i]->getStatus() == Canceled) item->setText(QString::fromStdString("Canceled"));
                if (tasks[i]->getStatus() == Done) item->setText(QString::fromStdString("Done"));
                if (tasks[i]->getStatus() == Waiting) item->setText(QString::fromStdString("Waiting"));
                break;
            case 2:
                item->setText(QString::number(tasks[i]->getPriority()));
                break;
            case 3:
                item->setText(QString::number(tasks[i]->getAffinity()));
                break;
            }
        }
    }
}

void MainWindow::on_bCheck_clicked() {
    int s = 0;
    for (int i = 0; i < arrLen; i++) {
        s += arr[i];
    }
    ui->leCorrectSum->setText(QString::number(s));
}

void MainWindow::on_bSetPriority_clicked() {
    int index = ui->tableWidget->selectedItems()[0]->row();
    tasks[index]->setPriority(ui->lePriority->text().toInt());
}

void MainWindow::on_bDetach_clicked() {
    int index = ui->tableWidget->selectedItems()[0]->row();
    tasks[index]->detach();
}

void MainWindow::on_bCancel_clicked() {
    int index = ui->tableWidget->selectedItems()[0]->row();
    tasks[index]->cancel();
}

void MainWindow::on_bSetAffinity_clicked() {
    int index = ui->tableWidget->selectedItems()[0]->row();
    tasks[index]->setAffinity(ui->leAffinity->text().toInt());
}
