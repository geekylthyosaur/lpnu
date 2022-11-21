#include "server.h"

Server::Server() {
    this->worker = new Worker();
}

void Server::request(QString request_str) {
    Request* request = new Request(request_str);

    this->worker->requests->enqueue(request);
}

Response* Server::response() {
    return this->worker->responses->dequeue();
}
