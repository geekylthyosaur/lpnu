#ifndef WORKER_H
#define WORKER_H

#include "QDebug"
#include "QQueue"
#include "pthread.h"
#include "unistd.h"
#include "iostream"

#include <request.h>
#include <response.h>

class Worker {
private:
    pthread_t thread;
public:
    Worker();
    QQueue<Request*>* requests;
    QQueue<Response*>* responses;

    static void* task(void*);

private:
    static char iseparator;
    static char separator;
};

#endif // WORKER_H
