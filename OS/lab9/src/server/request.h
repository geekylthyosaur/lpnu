#ifndef REQUEST_H
#define REQUEST_H

#include "QVector"

class Request {
public:
    int receiver_id;
    QVector<QString>* paths;
    QVector<QString>* extensions;
    Request(int receiver_id, QVector<QString>* paths, QVector<QString>* extensions);
};

#endif // REQUEST_H
