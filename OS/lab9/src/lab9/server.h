#ifndef SERVER_H
#define SERVER_H

#include "worker.h"

class Server {
private:
    Worker * worker;
public:
    Server();
};

#endif // SERVER_H
