#include "request.h"

Request::Request(int receiver_id, QVector<QString> *paths, QVector<QString>* extensions) {
    this->receiver_id = receiver_id;
    this->paths = paths;
    this->extensions = extensions;
}
