#include "pch.h"
#include "dllSum.h"

int dllSumUp(int* arr, int len) {
	int sum = 0;
	for (int i = 0; i < len; i++) sum += arr[i];
	return sum;
}
