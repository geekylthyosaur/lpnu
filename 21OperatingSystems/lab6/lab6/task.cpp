#include "task.h"
#include <unistd.h>
#include "QDebug"

using namespace std;

int numCpus = sysconf(_SC_NPROCESSORS_ONLN);

void* thread_task(void* args) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, 0);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, 0);

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
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    this->attr = attr;
    pthread_attr_setschedpolicy(&this->attr, SCHED_FIFO);
    ThreadArgs* args = new ThreadArgs(threadCount, threadIndex, arrLen, sum, arr, sem, spin, this);
    if (pthread_create(&this->thread, &attr, &thread_task, args)) {
        qDebug() << "pthread_create error!";
        return;
    }
    this->threadIndex = threadIndex;
    this->setAffinity(this->threadIndex % numCpus);
}

void Task::detach() {
    pthread_detach(this->thread);
    if (this->status != Done) this->status = Detached;
}

void Task::cancel() {
    pthread_cancel(this->thread);
    if (this->status != Done) this->status = Canceled;
}

void Task::setPriority(int n) {
    int policy;
    struct sched_param param;

    pthread_getschedparam(this->thread, &policy, &param);
    param.sched_priority = n;
    pthread_setschedparam(this->thread, policy, &param);
}

int Task::getPriority() {
    int policy;
    struct sched_param param;
    pthread_getschedparam(this->thread, &policy, &param);
    return param.sched_priority;
}

void Task::setAffinity(int cpu) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu, &cpuset);
    if (pthread_setaffinity_np(this->thread, sizeof(cpuset), &cpuset)) {
        qDebug() << "pthread_setaffinity_np() error";
    }
}

int Task::getAffinity() {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    if (pthread_getaffinity_np(this->thread, sizeof(cpuset), &cpuset)) {
        qDebug() << "pthread_attr_getaffinity_np() error";
    }
    for (int i = 0; i < numCpus; i++) {
        if (CPU_ISSET(i, &cpuset)) return i;
    }
    return -1;
}
