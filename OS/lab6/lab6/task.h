#ifndef TASK_H
#define TASK_H

#include "pthread.h"
#include "threadargs.h"

#include "pthread.h"

enum Status {
    Running,
    Detached,
    Canceled,
    Done,
    Waiting,
};

class Task
{
private:
    pthread_t thread;
    int core;
    int threadIndex;
    Status status;
public:
    Task() = default;
    Task(int threadCount, int threadIndex, int arrLen, int* sum, int* arr, sem_t* sem, pthread_spinlock_t* spin);
    void setAffinity(int core);
    void setCore(int core);

    int getAffinity();
    pthread_t* getHandle() { return &this->thread; }
    int getThreadIndex() { return this->threadIndex; }
    Status getStatus() { return this->status; }
    void setStatus(Status newStatus) { this->status = newStatus; }
};

#endif // TASK_H
