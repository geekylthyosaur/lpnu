#ifndef THREADARGS_H
#define THREADARGS_H

#include "semaphore.h"

class ThreadArgs
{
public:
    int start;
    int end;
    int* sum;
    int* arr;
    sem_t* sem;
    pthread_spinlock_t* spin;
    void* task;
    ThreadArgs(int threadCount, int threadIndex, int arrLen, int* sum, int* arr, sem_t* sem, pthread_spinlock_t* spin, void* task);
};

#endif // THREADARGS_H
