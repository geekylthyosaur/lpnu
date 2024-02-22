#include "response.h"

using namespace std;

Response::Response(int receiver_id, QString response) {
    this->receiver_id = receiver_id;
    this->response = response;
}

QString Response::toString() {
    return QString::number(this->receiver_id) + separator + this->response;
}
