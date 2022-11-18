#include "response.h"

Response::Response(int receiver_id, QString response) {
    this->receiver_id = receiver_id;
    this->response = response;
}
