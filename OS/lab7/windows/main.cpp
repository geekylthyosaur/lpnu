#include <iostream>
#include <Windows.h>
#include "libSum.h"
#ifndef RUNTIME
#include "dllSum.h"
#else
typedef int(__cdecl* DLLSUMUP)(int*, int);
#endif

int main() {
  int len;
  std::cout << "Enter array len: ";
  std::cin >> len;
  int* arr = new int[len];
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  for (int i = 0; i < len; i++) arr[i] = rand() % 10;
  
  int sum = libSumUp(arr, len);
  std::cout << "Sum from static lib: " << sum << std::endl;

#ifndef RUNTIME
  int dllSum = dllSumUp(arr, len);
  std::cout << "Sum from dynamic lib (using load-time linking): " << dllSum << std::endl;
#else
    HINSTANCE hinstLib;
    DLLSUMUP dllSumUp;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    hinstLib = LoadLibrary(TEXT("dllSum.dll"));

    if (hinstLib != NULL) {
        dllSumUp = (DLLSUMUP)GetProcAddress(hinstLib, "dllSumUp");

        if (NULL != dllSumUp) {
            fRunTimeLinkSuccess = TRUE;
            int dllSum = (dllSumUp)(arr, len);
            std::cout << "Sum from dynamic lib (using run-time linking): " << dllSum << std::endl;
        }

        fFreeResult = FreeLibrary(hinstLib);
    }

    if (!fRunTimeLinkSuccess)
        std::cout << "Failed to link on runtime" << std::endl;
#endif
}
