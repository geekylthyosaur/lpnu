#include <stdio.h>
#include "stdlib.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(void) {
    pid_t pid;
    int status, PC = 0, N = 0;

    while (N < 1) {
        cout << "Enter value of N (> 1000): ";
        cin >> N;
    }

    while (PC < 1) {
        cout << "Enter number of processes: ";
        cin >> PC;
    }

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
                execl("/bin/footclient", "-e", "./process", s1, s2, s3, NULL);
                return 0;
            default:
                //Error
                break;
        }
    }

    return 0;
}

