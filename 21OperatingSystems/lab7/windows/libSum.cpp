#include "pch.h"
#include "framework.h"
#include "libSum.h"

int libSumUp(int* arr, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) sum += arr[i];
    return sum;
}
