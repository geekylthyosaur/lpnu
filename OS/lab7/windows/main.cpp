#include <iostream>
#include "libSum.h"
#include "dllSum.h"

int main() {
	int len;
	std::cout << "Enter array len: ";
	std::cin >> len;
	int* arr = new int[len];
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	for (int i = 0; i < len; i++) arr[i] = rand() % 10;
	
	int sum = sum::sumUp(arr, len);
	std::cout << "Sum from static lib: " << sum << std::endl;

	int dllSum = dllSumUp(arr, len);
	std::cout << "Sum from dynamic lib: " << dllSum << std::endl;
}
