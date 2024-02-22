#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

void bubble_sort(int* array, int N);
vector<string> split(string s, string delimiter);

int main(int argc, char** argv)
{
    if (argc < 4) return -1;

    int Ncol = atoi(argv[1]);
    int startRow = atoi(argv[2]);
    int endRow = atoi(argv[3]);
    int Nrow = endRow - startRow;

    cout << "Reading array from file " << Ncol << "x" << Nrow << " ... ";

    string line;
    ifstream file("C:\\Users\\Dmytro\\source\\repos\\lab3\\lab3\\array.txt");
    int** array = new int* [Nrow];
    for (int i = 0; i < startRow; i++)
    {
        getline(file, line);
    }
    for (int i = 0; i < Nrow; i++)
    {
        getline(file, line);
        array[i] = new int[Ncol];

        auto vec = split(line, ",");
        for (int j = 0; j < Ncol; j++)
        {
            array[i][j] = atoi(vec[j].c_str());
            cout << vec[j] << " ";
        }
        cout << endl;
    }
    file.close();

    cout << "Done!" << endl;

    cout << "Sorting array ... " << endl;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < Nrow; i++)
    {
        cout << "Sorting row " << i << endl;
        bubble_sort(array[i], Ncol);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Sorting took: " << duration.count() << "ms" << endl;

    cout << "Print sorted array? [y/N] ";
    // char op = getchar();
    char op = 'y';

    if (op == 'y')
    {
        cout << "Sorted array: " << endl;

        for (int i = 0; i < Nrow; i++)
        {
            for (int j = 0; j < Ncol; j++)
            {
                cout << array[i][j] << ", ";
            }
            cout << endl;
        }
        cin.ignore();
        cout << "Press any key to continue..." << endl;
        getchar();
    }

    return 0;
}

void bubble_sort(int* array, int N) 
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
