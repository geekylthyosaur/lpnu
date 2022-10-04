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
    void readFromFile(QString fileName);
    void writeToFile(QString fileName);
};

#endif // APP_H
