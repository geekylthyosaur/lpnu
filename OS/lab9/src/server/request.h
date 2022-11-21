#ifndef REQUEST_H
#define REQUEST_H

#include "QVector"
#include "QStringList"

class Request {
public:
    Request(QString request);
    Request(int receiver_id, QVector<QString>* paths, QVector<QString>* extensions);

    int receiver_id;
    QVector<QString>* paths;
    QVector<QString>* extensions;
};

#endif // REQUEST_H
