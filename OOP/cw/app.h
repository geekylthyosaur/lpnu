#ifndef APP_H
#define APP_H

#include "list.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

class App
{
private:
    List* list;
    Ui::MainWindow* ui;

public:
    App() = default;
    App(Ui::MainWindow* ui);

    void addPerson();
    void removePerson();
    void updateTable();
    void healthyPeople();
    void highPressureAndRate(int age);
    void bestDonors();
    void bestRecipients();
    void donorsAndRecipients();
    void clearTable();
    void readFromFile(QString fileName);
    void writeToFile(QString fileName);
    void sort(int columnIndex);
};

#endif // APP_H
