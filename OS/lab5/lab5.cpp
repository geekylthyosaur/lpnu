#include <windows.h>
#include <stdio.h>
#include <iostream>

#define MAX_SEM_COUNT 10

struct PARAMETERS {
    int i;
};

HANDLE ghSemaphore;
DWORD WINAPI ThreadProc(LPVOID);

int* array;
int N;
int threadCount = 0;
LONG sum = 0;

int main(void) {
    HANDLE* aThread;
    DWORD ThreadID;

    while (N < 1) {
        std::cout << "Enter value of N (> 10000): ";
        std::cin >> N;
    }

    while (threadCount < 1) {
        std::cout << "Enter number of threads: ";
        std::cin >> threadCount;
    }

    aThread = new HANDLE[threadCount];

    // Generate random array
    array = new int[N];
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < N; i++)
        array[i] = rand();

    // Create a semaphore with initial and max counts of MAX_SEM_COUNT

    ghSemaphore = CreateSemaphore(
        NULL,           // default security attributes
        MAX_SEM_COUNT,  // initial count
        MAX_SEM_COUNT,  // maximum count
        NULL);          // unnamed semaphore

    if (ghSemaphore == NULL) {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    // Create worker threads

    for (int i = 0; i < threadCount; i++) {
        PARAMETERS* p = new PARAMETERS{ i };
        aThread[i] = CreateThread(
            NULL,       // default security attributes
            0,          // default stack size
            (LPTHREAD_START_ROUTINE)ThreadProc,
            p,         // no thread function arguments
            0,          // default creation flags
            &ThreadID); // receive thread identifier

        if (aThread[i] == NULL) {
            printf("CreateThread error: %d\n", GetLastError());
            return 1;
        }
    }

    // Wait for all threads to terminate

    WaitForMultipleObjects(threadCount, aThread, TRUE, INFINITE);

    // Close thread and semaphore handles

    for (int i = 0; i < threadCount; i++)
        CloseHandle(aThread[i]);

    CloseHandle(ghSemaphore);

    std::cout << sum << std::endl;

    int a = 0;
    for (int i = 0; i < N; i++)
        a += array[i];
    std::cout << a << std::endl;

    return 0;
}

DWORD WINAPI ThreadProc(LPVOID lpParam) {
    PARAMETERS* p = (PARAMETERS*)lpParam;
    int i = p->i;
    int start, end;

    // lpParam not used in this example
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;
    BOOL bContinue = TRUE;

    while (bContinue) {
        // Try to enter the semaphore gate.

        dwWaitResult = WaitForSingleObject(
            ghSemaphore,   // handle to semaphore
            0L);           // zero-second time-out interval

        switch (dwWaitResult) {
            // The semaphore object was signaled.
        case WAIT_OBJECT_0:
            // TODO: Perform task
            printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
            bContinue = FALSE;

            // Simulate thread spending time on task
            start = (N / threadCount) * i;
            end = (N / threadCount) * (i + 1);
            for (int j = start; j < end; j++)
                InterlockedAdd(&sum, (LONG)array[j]);

            // Release the semaphore when task is finished

            if (!ReleaseSemaphore(
                ghSemaphore,  // handle to semaphore
                1,            // increase count by one
                NULL))       // not interested in previous count
            {
                printf("ReleaseSemaphore error: %d\n", GetLastError());
            }
            break;

            // The semaphore was nonsignaled, so a time-out occurred.
        case WAIT_TIMEOUT:
            printf("Thread %d: wait timed out\n", GetCurrentThreadId());
            break;
        }
    }
    return TRUE;
}
