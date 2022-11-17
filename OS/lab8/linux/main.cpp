#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define N 100

using namespace std;

void task(int file);
vector<string> split(string s, string delimiter);
void bubble_sort(int* array);

int main() {
    string filename;
    cout << "Enter file name: ";
    cin >> filename;
    int mode = S_IRUSR | S_IRGRP | S_IROTH;
    int file = open(filename.c_str(), O_RDWR | O_CREAT, mode);

    if (file == -1) {
        cout << "open() error" << endl;
    }

    task(file);

    close(file);

    bool exit = true;
    while (exit) {
        int desired_attrs;
        cout << "Enter file attributes to set: ";
        cin >> desired_attrs;
        switch (desired_attrs) {
        case 1:
            mode = mode | S_IXOTH;
            break;
        case 2:
            mode = mode | S_IWOTH;
            break;
        case 4:
            mode = mode | S_IROTH;
            break;
        case 7:
            mode = mode | S_IRWXO;
            break;
        case 10:
            mode = mode | S_IXGRP;
            break;
        case 20:
            mode = mode | S_IWGRP;
            break;
        case 40:
            mode = mode | S_IRGRP;
            break;
        case 70:
            mode = mode | S_IRWXG;
            break;
        case 100:
            mode = mode | S_IXUSR;
            break;
        case 200:
            mode = mode | S_IWUSR;
            break;
        case 400:
            mode = mode | S_IRUSR;
            break;
        case 700:
            mode = mode | S_IRWXU;
            break;
        }
        chmod(filename.c_str(), mode);
    }
}

void task(int file) 
{
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
    write(file, text.c_str(), text.size());
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

