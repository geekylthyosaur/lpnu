#include "request.h"

Request::Request(QString request) {
    QVector<QString>* paths = new QVector<QString>();
    QVector<QString>* extensions = new QVector<QString>();

    auto rows = request.split(separator);
    int receiver_id = rows[0].toInt();

    auto paths_tokens = rows[1].split(",");
    auto extensions_tokens = rows[2].split(",");

    for (QString path : paths_tokens)
        paths->append(path);

    for (QString extension : extensions_tokens)
        extensions->append(extension);

    this->receiver_id = receiver_id;
    this->paths = paths;
    this->extensions = extensions;
}

Request::Request(int receiver_id, QVector<QString> *paths, QVector<QString>* extensions) {
    this->receiver_id = receiver_id;
    this->paths = paths;
    this->extensions = extensions;
}
