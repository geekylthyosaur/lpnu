#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "person.h"
#include "list.h"
#include "app.h"
#include "QFileDialog"
#include "QInputDialog"
#include "QDebug"
#include "QMessageBox"

App* app;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableHealthy->setVisible(false);
    ui->tableDonorsAndRecipients->setVisible(false);
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
        try
        {
            app->readFromFile(fileName);
            app->updateTable();
        }
        catch (int err)
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("Error");
            if (err == 1) msgBox.setText("This file is corrupted!");
            msgBox.exec();
            return;
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"), "/home/dmytro/", tr("Data file (*.csv)"));
    if (!fileName.isEmpty())
    {
        try
        {
            app->writeToFile(fileName);
        }
        catch (int err)
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("Warning");
            if (err == 1) msgBox.setText("Nothing to save!");
            msgBox.exec();
            return;
        }
    }
}

void MainWindow::on_addPersonBtn_clicked()
{
    try
    {
        app->addPerson();
        app->updateTable();
    }
    catch (int err)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error");
        if (err == 1) msgBox.setText("N field has invalid value!");
        else if (err == 2) msgBox.setText("Surname field has invalid value!");
        else if (err == 3) msgBox.setText("Age field has invalid value!");
        else if (err == 4) msgBox.setText("Blood Type field has invalid value!");
        else if (err == 5) msgBox.setText("Blood Pressure field has invalid value!");
        else if (err == 6) msgBox.setText("RhD field has invalid value!");
        else if (err == 7) msgBox.setText("Heart Rate field has invalid value!");
        msgBox.exec();
        return;
    }
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

void MainWindow::on_healthyPeople_triggered()
{
    app->healthyPeople();
}

void MainWindow::on_highPressureAndRate_triggered()
{
    int age = QInputDialog::getInt(this, "Enter", "Enter Age:");
    app->highPressureAndRate(age);
}

void MainWindow::on_actionDefault_triggered()
{
    app->updateTable();
}

void MainWindow::on_bestDonors_triggered()
{
    app->bestDonors();
}

void MainWindow::on_bestRecipients_triggered()
{
    app->bestRecipients();
}

void MainWindow::on_donorsRecepients_triggered()
{
    app->donorsAndRecipients();
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    if (ui->tableWidget->columnCount() == 5) {
        if (column == 3) app->showDonorsTo(row);
        else if (column == 4) app->showRecipientsFrom(row);
    }
}
