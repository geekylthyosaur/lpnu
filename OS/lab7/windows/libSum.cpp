#include "pch.h"
#include "framework.h"
#include "libSum.h"

namespace sum {
	int sumUp(int* arr, int len) {
		int sum = 0;
		for (int i = 0; i < len; i++) sum += arr[i];
		return sum;
	}
}
