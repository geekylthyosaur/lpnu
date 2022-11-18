#ifndef WORKER_H
#define WORKER_H

#include "QDebug"
#include "QQueue"
#include "pthread.h"
#include "unistd.h"
#include "iostream"

struct Request {
    QVector<QString> paths;
    QVector<QString> extensions;
};

class Worker {
private:
    pthread_t thread;
public:
    Worker();
    QQueue<Request>* requests;

    static void* task(void*);
};

#endif // WORKER_H
