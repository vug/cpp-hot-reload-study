#pragma once

#define EXPORT_API __declspec(dllexport)

extern "C" {
    EXPORT_API int calculate(int x, int y);
}

// using CalculateFunc = int(*)(int, int);
using CalculateFunc = decltype(&calculate);
