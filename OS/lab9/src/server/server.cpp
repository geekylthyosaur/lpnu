#include "server.h"

Server::Server() {
    QVector<QString>* paths = new QVector<QString>();
    QVector<QString>* extensions = new QVector<QString>();

    /*
     * Maybe it'll be useful in the future
     */
    int receiver_id = 0;

    paths->append(QString::fromStdString("/home/*/*"));
    paths->append(QString::fromStdString("/home/*/*"));

    extensions->append(QString::fromStdString(".pdf"));
    extensions->append(QString::fromStdString(".png"));

    Request* r = new Request(receiver_id, paths, extensions);
    this->worker = new Worker();
    this->worker->requests->enqueue(*r);
}
