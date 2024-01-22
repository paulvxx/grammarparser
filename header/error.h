#include <stdio.h>
#include <stdarg.h>

#ifndef ERROR_H
#define ERROR_H

#define ERROR(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__);

#endif
