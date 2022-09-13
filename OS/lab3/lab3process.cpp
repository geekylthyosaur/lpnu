#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

void bubble_sort(int* array, int N);

int main(int argc, char** argv)
{
    if (argc < 2) return -1;
    
    int N = atoi(argv[1]);

    cout << "Got N = " << N << endl;
    cout << "Generating random array " << N << "x" << N << " ... ";

    int** array = new int*[N];
    for (int i = 0; i < N; i++) array[i] = new int[N];

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            array[i][j] = rand();
        }
    }
    cout << "Done!" << endl;

    cout << "Sorting array ... " << endl;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        cout << "Sorting row " << i << endl;
        bubble_sort(array[i], N);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Sorting took: " << duration.count() << "ms" << endl;

    cout << "Print sorted array? [y/N] ";
    char op = getchar();

    if (op == 'y')
    {
        cout << "Sorted array: " << endl;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
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


