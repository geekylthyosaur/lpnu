#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "person.h"
#include "list.h"
#include "app.h"
#include "QFileDialog"

App* app;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    app = new App(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{/*
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "/home/dmytro/", tr("Data file (*.csv)"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        file >> list;
    }*/
}

void MainWindow::on_actionSave_triggered()
{/*
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"), "/home/dmytro/", tr("Data file (*.csv)"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        file << list;
    }*/
}

void MainWindow::on_addPersonBtn_clicked()
{
    app->addPerson();
    app->updateTable();
}

