#include <iostream>
#include "aSum.h"
#define RUNTIME
#ifndef RUNTIME
#include "soSum.h"
#else
#include <dlfcn.h>
int (*soSumUp)(int*, int);
#endif

int main() {
	int len;
    std::cout << "Enter array len: ";
	std::cin >> len;
	int* arr = new int[len];
	srand(static_cast<unsigned int>(time(nullptr)));
	for (int i = 0; i < len; i++) arr[i] = rand() % 10;
	
	int aSum = sumUp(arr, len);
    std::cout << "Sum from static lib: " << aSum << std::endl;

#ifndef RUNTIME
	int soSum = soSumUp(arr, len);
    std::cout << "Sum from dynamic lib (using load-time linking: " << soSum << std::endl;
#else
    void* lib;
    lib = dlopen("./libSum.so", RTLD_LAZY);
    if (!lib)
        std::cout << "Failed to link on runtime" << std::endl;

    soSumUp = (int (*)(int*, int))dlsym(lib, "soSumUp");

	int soSum = (*soSumUp)(arr, len);
    std::cout << "Sum from dynamic lib (using run-time linking: " << soSum << std::endl;

    dlclose(lib);
#endif
}
