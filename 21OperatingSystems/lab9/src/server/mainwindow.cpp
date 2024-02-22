#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include "qdebug.h"
#include <unistd.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

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

    QList<int> proccessedRequests = QList<int>();

    while(1) {
        //Reading the requests
        struct flock ilock;
        ilock.l_type = F_RDLCK;
        ilock.l_whence = SEEK_SET;
        ilock.l_start = 0;
        ilock.l_len = 0;

        int ifd;
        while ((ifd = open(requestFilePath.c_str(), O_RDWR | O_APPEND, 0666)) < 0);

        while (fcntl(ifd, F_SETLK, &ilock) < 0);

        int bufferSize = 4096;
        char buffer[bufferSize];

        while(read(ifd, &buffer, bufferSize) > 0);

        std::string input = std::string(buffer, 0, bufferSize);

        qDebug() << "Readings: " << buffer;

        ilock.l_type = F_UNLCK;
        while (fcntl(ifd, F_SETLK, &ilock) < 0);

        //1804289383@/home/piktur/OSLab9Server@.cpp
        QList<QString> requests = QString::fromStdString(input).split('\n');
        requests = filterIfNotContains(requests, proccessedRequests);

        if (requests.size() > 0) requests.pop_back();

        qDebug() << "Requests: " << requests;
        if (requests.size() > 0) {
            //Outputting the responses
            struct flock olock;
            olock.l_type = F_WRLCK;
            olock.l_whence = SEEK_SET;
            olock.l_start = 0;
            olock.l_len = 0;

            int ofd;
            while ((ofd = open(responseFilePath.c_str(), O_RDWR | O_APPEND, 0666)) < 0) {
                creat(responseFilePath.c_str(), 0666);
            };

            while (fcntl(ofd, F_SETLK, &olock) < 0);

            for (QString request : requests) {
                server->request(request);

                Response* response;
                while (!(response = server->response()));

                std::string responseString = response->toString().toStdString();
                responseString.pop_back();
                responseString += "\n";

                qDebug() << "Response: " << response->toString();

                write(ofd, responseString.c_str(), strlen(responseString.c_str()));

                qDebug() << "Something is written to resp file";

                proccessedRequests.append(request.split(separator)[0].toInt());
            }

            olock.l_type = F_UNLCK;
            while (fcntl(ofd, F_SETLK, &olock) < 0);
        }

        sleep(3);
    }
}

QList<QString> MainWindow::filterIfContains(QList<QString> origin, QList<int> ids) {
    if (ids.isEmpty()) return origin;

    QList<QString> results = QList<QString>();

    for (QString element : origin) {
        bool condition = true;
        for (int id : ids) {
            if (!element.contains(QString::number(id))) {
                condition = false;
            }
        }
        if (condition) results.append(element);
    }

    return results;
}

QList<QString> MainWindow::filterIfNotContains(QList<QString> origin, QList<int> ids) {
    if (ids.isEmpty()) return origin;

    QList<QString> results = QList<QString>();

    for (QString element : origin) {
        bool condition = true;
        for (int id : ids) {
            if (element.contains(QString::number(id))) {
                condition = false;
            }
        }
        if (condition) results.append(element);
    }

    return results;
}
