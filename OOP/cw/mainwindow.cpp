#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "person.h"
#include "list.h"
#include "app.h"
#include "QFileDialog"
#include "QDebug"

App* app;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth( 0, 40 );
    ui->tableWidget->setColumnWidth( 1, 400 );
    ui->tableWidget->setColumnWidth( 2, 40 );
    ui->tableWidget->setColumnWidth( 3, 40 );
    ui->tableWidget->setColumnWidth( 4, 20 );
    ui->tableWidget->setColumnWidth( 5, 80 );
    ui->tableWidget->setColumnWidth( 6, 40 );
    QStringList labels;
    labels << "N" << "Surname" << "Age" << "Type" << "RhD" << "Pressure" << "Rate";
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode (QHeaderView::Fixed);
    app = new App(ui);
    auto header = ui->tableWidget->horizontalHeader();
    connect(header, &QHeaderView::sectionClicked, [this](int columnIndex) {
        app->sort(columnIndex);
        app->updateTable();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "/home/dmytro/", tr("Data file (*.csv)"));
    if (!fileName.isEmpty())
    {
        app->readFromFile(fileName);
        app->updateTable();
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"), "/home/dmytro/", tr("Data file (*.csv)"));
    if (!fileName.isEmpty())
    {
        app->writeToFile(fileName);
    }
}

void MainWindow::on_addPersonBtn_clicked()
{
    app->addPerson();
    app->updateTable();
}


void MainWindow::on_actionby_Blood_Pressure_triggered()
{
    app->sort(0);
    app->updateTable();
}


void MainWindow::on_actionType_and_RhD_triggered()
{
    app->sort(1);
    app->updateTable();
}


void MainWindow::on_actionRhD_and_Heart_Rate_triggered()
{
    app->sort(2);
    app->updateTable();
}

