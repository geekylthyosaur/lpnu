#include "threadargs.h"

ThreadArgs::ThreadArgs(int threadCount, int threadIndex, int arrLen, int* sum, int* arr, sem_t* sem, pthread_spinlock_t* spin, void* task) {
    this->start = (arrLen / threadCount) * threadIndex;
    this->end = (arrLen / threadCount) * (threadIndex + 1);
    this->sum = sum;
    this->arr = arr;
    this->sem = sem;
    this->spin = spin;
    this->task = task;
}
