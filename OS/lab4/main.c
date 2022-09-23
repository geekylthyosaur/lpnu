#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {
    pid_t pid;
    int status, PC = 0;

    printf("Enter number of processes: ");
    while (PC < 1)
        scanf("%d", &PC);

    int _ = 0;

    for (int i = 0; i < PC; i++) {
        if (pid > 0)
            pid = fork();
        switch(pid) {
            case -1:
                // Error
                break;
            case 0:
                printf("%d: Start\n", getpid());
                return 0;
            default:
                if (waitpid(pid, &status,0)!=0)
                    printf("%d: End\n", pid);
                else
                //Error
                break;
        }
    }

    return 0;
}

