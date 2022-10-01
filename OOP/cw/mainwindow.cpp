#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "person.h"
#include "list.h"
#include "QFileDialog"

List* list = new List();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
        QFile file(fileName);
        file >> list;
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"), "/home/dmytro/", tr("Data file (*.csv)"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        file << list;
    }
}

void MainWindow::on_addPersonBtn_clicked()
{
    list->push(new Person(
                   ui->nLE->text().toInt(),
                   ui->surnameLE->text(),
                   ui->ageLE->text().toInt(),
                   new Blood(
                           ui->bloodpressureLE->text().split("/")[0].toInt(),
                           ui->bloodpressureLE->text().split("/")[1].toInt(),
                           ui->rhdLE->text().isEmpty(),
                           ui->bloodtypeLE->text()
                       ),
                   ui->heartrateLE->text().toInt(),
                   ));
}

