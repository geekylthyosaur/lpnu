#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0, 50);

}

MainWindow::~MainWindow()
{
    delete ui;
}

class MyException : public exception
{
    string _msg;
public:
    MyException(string msg) : _msg(msg) {}

    virtual const char* what() const noexcept override
    {
        return _msg.c_str();
    }
};

void MainWindow::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Monitor directory", QString(), QFileDialog::ShowDirsOnly);
    ui->textEdit_directories->setText(ui->textEdit_directories->toPlainText() + dir + '\n');
}

void MainWindow::on_pushButton_Find_clicked()
{
    //forming the request
    int myId = rand();
    QString request = QString::number(myId) + '\n';
    QStringList dirList = ui->textEdit_directories->toPlainText().split("\n");
    QStringList extList = ui->textEdit_extentions->toPlainText().split("\n");

    for(auto dir = dirList.cbegin(); dir != dirList.cend(); dir++)
    {
        if(!dir->isEmpty())
        {
            request += *dir + ',';
        }
    }
    if(request.back() == ',')
    {
        request.back() = '\n';
    }
    else
    {
        request += '\n';
    }

    for(auto ext = extList.cbegin(); ext != extList.cend(); ext++)
    {
        if(!ext->isEmpty())
        {
            request += *ext + ',';
        }
    }
    if(request.back() == ',')
    {
        request.back() = '\n';
    }
    else
    {
        request += '\n';
    }

    //there we send request
    //penis

    //parsing and presenting the received data

   // QString str = ui->textEdit_directories->toPlainText();//str is received string
    QString str ="500\nfilek0,12.23.2003";
    QStringList list = str.split("\n");
    QString generalSize = list[0];
    ui->statusbar->showMessage("  General size: " + generalSize, 0);

    if(list.size() < 2)
    {
        throw MyException("Files in this directories are not found");
    }

    ui->tableWidget->clearContents();
    for(int i = 1; i < list.size(); i++)
    {
        QStringList SubList = list[i].split(',');
        QString fileName = SubList[0];
        QString fileBirth = SubList[1];

        ui->tableWidget->insertRow(i-1);
        ui->tableWidget->setItem(i-1, 0, new QTableWidgetItem(QString::number(i)));
        ui->tableWidget->item(i-1, 0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i-1, 1, new QTableWidgetItem(fileName));
        ui->tableWidget->setItem(i-1, 2, new QTableWidgetItem(fileBirth));
    }


   //__________________________________________________________________

    ui->textEdit_directories->setText(request);

}



