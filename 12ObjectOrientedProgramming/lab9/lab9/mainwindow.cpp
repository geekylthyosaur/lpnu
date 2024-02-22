#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "wholesaleclient.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

// 3
RegularWholeSaleClient regular = RegularWholeSaleClient();
VIPWholeSaleClient vip = VIPWholeSaleClient();
QVector<WholeSaleClient> l;
// 3

WholeSaleClient * client = new VIPWholeSaleClient(100);
