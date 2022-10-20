#include "task.h"
#include "QDebug"

using namespace std;

void* thread_task(void* args) {
    ThreadArgs* targs = (ThreadArgs*)args;
    int start = targs->start;
    int end = targs->end;
    int* sum = targs->sum;
    int* arr = targs->arr;
    sem_t* sem = targs->sem;
    pthread_spinlock_t* spin = targs->spin;
    Task* task = (Task*)targs->task;

    task->setStatus(Running);
    int value;
    sem_getvalue(sem, &value);
    if (value == 0) {
        task->setStatus(Waiting);
    }
    sem_wait(sem);
    task->setStatus(Running);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = start; i < end; i++) {
        arr[i] = rand() % 5;
    }

    for (int i = start; i < end; i++) {
        pthread_spin_lock(spin);
        *sum += arr[i];
        pthread_spin_unlock(spin);
    }
    sem_post(sem);
    task->setStatus(Done);
    pthread_exit(NULL);
}

Task::Task(int threadCount, int threadIndex, int arrLen, int* sum, int* arr, sem_t* sem, pthread_spinlock_t* spin) {
    ThreadArgs* args = new ThreadArgs(threadCount, threadIndex, arrLen, sum, arr, sem, spin, this);
    if (pthread_create(&this->thread, NULL, &thread_task, args)) {
        qDebug() << "pthread_create error!";
        return;
    }
    this->threadIndex = threadIndex;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, 0);
}

void Task::setAffinity(int core) {

}

int Task::getAffinity() {
}
