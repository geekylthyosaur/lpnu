#pragma once

#ifndef DLLSUM_EXPORTS
#define DLLSUM_API __declspec(dllexport)
#else
#define DLLSUM_API __declspec(dllimport)
#endif

extern "C" DLLSUM_API int dllSumUp(int* arr, int len);
