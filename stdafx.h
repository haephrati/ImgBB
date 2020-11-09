#pragma once
#include <Windows.h>
#if defined(WIN32) && !defined(__GNUC__)
#define wcsncasecmp _wcsnicmp
static inline bool isnan(double x) { return x != x; }
static inline bool isinf(double x) { return !isnan(x) && isnan(x - x); }
#endif