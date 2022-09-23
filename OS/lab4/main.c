#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
int main(void) {
    pid_t pid;
    int status;
    pid = fork();
    switch(pid) {
        case -1:
            // якщо fork() повернув -1, то процес не створився
            perror("fork");
            break;
        case 0:
            // якщо fork() повернув 0, то тут пишемо інструкції для
            //дочірнього процесу
            // тут можна виконати заміну на іншу програму через exec
            printf("my pid=%i, returned pid=%i, my parent’s pid= %i\n", getpid(), pid, getppid());
            break;
        default:
            // якщо fork() повернув число> 0, то тут пишемо інструкції для
            //батьківського процесу
            printf("my pid = %i, returned pid = %i\n", getpid(), pid);
            // якщо дочірній завершився а батьківський не чекає коду його
            //завершення, то це створює процес-зомбі
            if (waitpid(pid, &status,0)!=0)
                printf("childprocess ended with status %i\n", status);
            else
                perror("waitpid");
            kill(pid, SIGKILL);
            break;
    }
    return 0;
}
