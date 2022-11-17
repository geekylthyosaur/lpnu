#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

#define N 100

using namespace std;

void task(HANDLE handle);
vector<string> split(string s, string delimiter);
void bubble_sort(int* array);

int main() {
    string filename;
    HANDLE handle;
    cout << "Enter file name: ";
    cin >> filename;
    filename = "C:\\Users\\Dmytro\\source\\repos\\os8\\" + filename;
    handle = CreateFileA((LPCSTR)filename.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (handle == INVALID_HANDLE_VALUE)
        return -1;

    task(handle);

    CloseHandle(handle);

    bool exit = true;
    while (exit) {
        int desired_attrs;
        DWORD attrs = GetFileAttributesA((LPCSTR)filename.c_str());
        if (attrs == NULL) {
            cout << "null" << endl;
        }
        cout << "Enter file attributes to set: \n[1]-reset,\n[2]-readonly,\n[3]-hidden\n";
        cin >> desired_attrs;
        switch (desired_attrs) {
        case 1:
            attrs = attrs & ~FILE_ATTRIBUTE_READONLY & ~FILE_ATTRIBUTE_HIDDEN;
            break;
        case 2:
            attrs = attrs | FILE_ATTRIBUTE_READONLY;
            break;
        case 3:
            attrs = attrs | FILE_ATTRIBUTE_HIDDEN;
            break;
        }
        SetFileAttributesA((LPCSTR)filename.c_str(), attrs);
    }
}

void task(HANDLE handle) 
{
    int** array = new int* [N];
    for (int i = 0; i < N; i++) array[i] = new int[N];

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            array[i][j] = rand();
        }
    }

    for (int i = 0; i < N; i++)
    {
        bubble_sort(array[i]);
    }

    string text;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == N - 1)
                text += to_string(array[i][j]);
            else
                text += to_string(array[i][j]);
                text += ",";
        }
        text += "\n";
    }
    WriteFile(handle, text.c_str(), text.size(), NULL, NULL);
}

void bubble_sort(int* array)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

