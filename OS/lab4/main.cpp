#include <stdio.h>
#include "stdlib.h"
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sys/times.h>

using namespace std;

void gettimes(int pid);
void suspend(int pid);
void resume(int pid);
void kill(int pid);
void renice(int pid);

time_t time_begin;
int main(void) {
    int* pids;
    int pid;
    int status, PC = 0, N = 0;
    char op;

    while (N < 1) {
        cout << "Enter value of N (> 1000): ";
        cin >> N;
    }

    while (PC < 1) {
        cout << "Enter number of processes: ";
        cin >> PC;
    }

    pids = new int[PC];
    cout << "Generating random array " << N << "x" << N << " ... ";

    int** array = new int* [N];
    for (int i = 0; i < N; i++) array[i] = new int[N];

    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            array[i][j] = rand();
        }
    }
    cout << "Done!" << endl;

    cout << "Writing array to file ... ";

    ofstream file;
    file.open("array.txt");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == N-1)
                file << array[i][j];
            else 
                file << array[i][j] << ",";
        }
        file << "\n";
    }
    file.close();

    cout << "Done!" << endl;

    time_begin = clock();

    for (int i = 0; i < PC; i++) {
        pid = fork();
        switch(pid) {
            case -1:
                // Error
                break;
            case 0:
                printf("Started child process (pid: %d)\n", getpid());
                char s1[10];
                char s2[10];
                char s3[10];
                sprintf(s1, "%d", N);
                sprintf(s2, "%d",(N/PC)*i);
                sprintf(s3, "%d", (N/PC)*(i+1));
                execl("/bin/footclient", "--", "./process", s1, s2, s3, NULL);
                return 0;
            default: 
                usleep(100000);
                string line;
                ifstream file("pid");
                getline(file, line);
                file.close();

                pids[i] = atoi(line.c_str());
                break;
        }
    }

    int i;
    while (true) {
        cout << "Suspend [s], Resume [r], Exit [e], Kill [k], Times [t], Priority [p]: ";
        cin >> op;
        if (op == 'e') break;
        cout << "Process index: ";
        cin >> i;
        if (op == 's') suspend(pids[i]);
        if (op == 'r') resume(pids[i]);
        if (op == 'k') kill(pids[i]);
        if (op == 't') gettimes(pids[i]);
        if (op == 'p') renice(pids[i]);
    }

    for (int i = 0; i < PC; i++) {
        kill(pids[i]);
    }

    return 0;
}

void gettimes(int pid) {
    char s[100];
    sprintf(s, "ps -o time %d | grep 0", pid);
    system(s);
}

void kill(int pid) {
    kill(pid, SIGKILL);
}

void resume(int pid) {
    kill(pid, SIGCONT);
}

void suspend(int pid) {
    cout << pid << endl;
    kill(pid, SIGSTOP);
}

void renice(int pid) {
    int nice;
    char cmd[100];
    cout << "New priority: ";
    cin >> nice;
    sprintf(cmd, "/bin/doas /bin/renice -n %d -p %d", nice, pid);
    system(cmd);
}

