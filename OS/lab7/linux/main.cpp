using namespace std;

#include <iostream>
#include "aSum.h"
#include "soSum.h"

int main() {
	int len;
	cout << "Enter array len: ";
	std::cin >> len;
	int* arr = new int[len];
	srand(static_cast<unsigned int>(time(nullptr)));
	for (int i = 0; i < len; i++) arr[i] = rand() % 10;
	
	int aSum = sumUp(arr, len);
	cout << "Sum from static lib: " << aSum << endl;

	int soSum = soSumUp(arr, len);
	cout << "Sum from dynamic lib: " << soSum << endl;
}
