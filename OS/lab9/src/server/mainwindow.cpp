#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    Server * server = new Server();

    /*
     * TODO
     *
     * server.request(QString request) - add request to queue
     * Response* response = server.response() = get latest response from queue
     */
}
