#include <stdio.h>
#include <stdarg.h>

#define ERROR(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__);