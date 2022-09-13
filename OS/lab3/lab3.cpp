#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

string getPriorityClass(PROCESS_INFORMATION* pi, int i);
void setPriorityClass(PROCESS_INFORMATION* pi, int p, int i);
void getProcessTimes(PROCESS_INFORMATION* pi, FILETIME* lpc, FILETIME* lpe, FILETIME* lpk, FILETIME* lpu, int i);
void createProcess(STARTUPINFO* si, PROCESS_INFORMATION* pi, HANDLE* handles, wstring cmd, int i);
void createProcesses(STARTUPINFO* si, PROCESS_INFORMATION* pi, HANDLE* handles, wstring cmd, int PC);
void resumeThread(PROCESS_INFORMATION* pi, int i);
void suspendThread(PROCESS_INFORMATION* pi, int i);
void closeProcessHandles(PROCESS_INFORMATION* pi, int i);
void closeProcessesHandles(PROCESS_INFORMATION* pi, int PC);
void terminateProcess(PROCESS_INFORMATION* pi, int i);
void terminateProcesses(PROCESS_INFORMATION* pi, int PC);

int main()
{
    int N = 0, PC = 0;
    
    while (N < 1)
    {
        cout << "Enter value of N (> 1000): ";
        cin >> N;
    }

    while (PC < 1)
    {
        cout << "Enter process count: ";
        cin >> PC;
    }

    cout << "Start!" << endl;

    wstring cmd = L"C:\\Users\\Dmytro\\source\\repos\\lab3process\\x64\\Debug\\lab3process.exe " + to_wstring(N);

    STARTUPINFO* si = new STARTUPINFO[PC];
    PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[PC];
    HANDLE* handles = new HANDLE[PC];
    FILETIME ft[4];
    SYSTEMTIME tm[4];

    createProcesses(si, pi, handles, cmd, PC);

    char op;
    int i;
    while (true)
    {
        cout << "Suspend [s], Resume [r], Exit [e], Kill [k], Times [t], Priority [p]: ";
        cin >> op;
        if (op == 'e') break;
        cout << "Process index: ";
        cin >> i;
        if (op == 's') suspendThread(pi, i);
        if (op == 'r') resumeThread(pi, i);
        if (op == 'k') terminateProcess(pi, i);
        if (op == 't')
        {
            getProcessTimes(pi, &ft[0], &ft[1], &ft[2], &ft[3], i);
            for (int i = 0; i < 4; i++) {
                FileTimeToSystemTime(&ft[i], &tm[i]);
            }
            cout << "create: " << tm[0].wMilliseconds << "ms" << endl;
            cout << "exit: " << tm[1].wMilliseconds << "ms" << endl;
            cout << "kernel: " << tm[2].wMilliseconds << "ms" << endl;
            cout << "user: " << tm[3].wMilliseconds << "ms" << endl;
        }
        if (op == 'p')
        {
            int p;
            cout << "Old priority: " << getPriorityClass(pi, i) << endl;
            cout << "[0] IDLE" << endl;
            cout << "[1] BELOW_NORMAL" << endl;
            cout << "[2] NORMAL" << endl;
            cout << "[3] ABOVE_NORMAL" << endl;
            cout << "[4] HIGH" << endl;
            cout << "[5] REALTIME" << endl;
            cout << "New priority: ";
            cin >> p;
            setPriorityClass(pi, p, i);
        }
    }

    terminateProcesses(pi, PC);
    
    cout << "End!" << endl;
}

string getPriorityClass(PROCESS_INFORMATION* pi, int i)
{
    return to_string(GetPriorityClass(pi[i].hProcess));
}

void setPriorityClass(PROCESS_INFORMATION* pi, int p, int i)
{
    if (p == 0) SetPriorityClass(pi[i].hProcess, IDLE_PRIORITY_CLASS);
    if (p == 1) SetPriorityClass(pi[i].hProcess, BELOW_NORMAL_PRIORITY_CLASS);
    if (p == 2) SetPriorityClass(pi[i].hProcess, NORMAL_PRIORITY_CLASS);
    if (p == 3) SetPriorityClass(pi[i].hProcess, ABOVE_NORMAL_PRIORITY_CLASS);
    if (p == 4) SetPriorityClass(pi[i].hProcess, HIGH_PRIORITY_CLASS);
    if (p == 5) SetPriorityClass(pi[i].hProcess, REALTIME_PRIORITY_CLASS);
}

void getProcessTimes(PROCESS_INFORMATION* pi, FILETIME* lpc, FILETIME* lpe, FILETIME* lpk, FILETIME* lpu, int i)
{
    GetProcessTimes(pi[i].hProcess, lpc, lpe, lpk, lpu);
}

void createProcess(STARTUPINFO* si, PROCESS_INFORMATION* pi, HANDLE* handles, wstring cmd, int i)
{
    ZeroMemory(&si[i], sizeof(si[i]));
    si[i].cb = sizeof(si[i]);
    ZeroMemory(&pi[i], sizeof(pi[i]));

    if (CreateProcess(
        NULL,
        (LPWSTR)cmd.c_str(),
        NULL,
        NULL,
        false,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si[i],
        &pi[i])
        )
    {
        handles[i] = pi[i].hProcess;

        cout << "Done!" << endl;
    }
    else
    {
        cout << "Failed!" << endl;
        return;
    }
}

void createProcesses(STARTUPINFO* si, PROCESS_INFORMATION* pi, HANDLE* handles, wstring cmd, int PC)
{
    for (int i = 0; i < PC; i++)
    {
        cout << "Creating process " << i + 1 << " ... ";
        createProcess(si, pi, handles, cmd, i);
    }
}

void resumeThread(PROCESS_INFORMATION* pi, int i)
{
    ResumeThread(pi[i].hThread);
}

void suspendThread(PROCESS_INFORMATION* pi, int i)
{
    SuspendThread(pi[i].hThread);
}

void closeProcessHandles(PROCESS_INFORMATION* pi, int i)
{
    CloseHandle(pi[i].hProcess);
    CloseHandle(pi[i].hThread);
}

void closeProcessesHandles(PROCESS_INFORMATION* pi, int PC)
{
    for (int pc = 0; pc < PC; pc++)
    {
        closeProcessHandles(pi, pc);
    }
}

void terminateProcess(PROCESS_INFORMATION* pi, int i)
{
    cout << "Terminating process " << i + 1 << " ... ";

    TerminateProcess(pi[i].hProcess, WM_CLOSE);
    closeProcessHandles(pi, i);

    cout << "Done!" << endl;
}

void terminateProcesses(PROCESS_INFORMATION* pi, int PC)
{
    for (int pc = 0; pc < PC; pc++)
    {
        terminateProcess(pi, pc);
    }
}
