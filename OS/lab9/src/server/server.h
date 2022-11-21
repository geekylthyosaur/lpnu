#ifndef SERVER_H
#define SERVER_H

#include "worker.h"

class Server {
private:
    Worker * worker;
public:
    Server();
    void request(QString request_str);
    Response* response();
};

#endif // SERVER_H
