#include "server.h"

Server::Server() {
    QVector<QString> paths = QVector<QString>();
    QVector<QString> extensions = QVector<QString>();
    paths.append(QString::fromStdString("/home/dmytro/pix"));
    paths.append(QString::fromStdString("/home/dmytro/loads"));
    extensions.append(QString::fromStdString(".pdf"));
    extensions.append(QString::fromStdString(".pdf"));
    Request r = {
        paths,
        extensions
    };
    this->worker = new Worker();
    this->worker->requests->enqueue(r);
}
