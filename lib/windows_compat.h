/**
 * @file windows_compat.h
 * @author Luke
 * @brief
 *  Adds functionality for `asprintf` and `vasprintf`
 *  under Windows, or at least under MinGW. Obviously,
 *  this is highly dependant on OS and compiler.
 *  Tweaks or recommendations welcome.
 * @date 2025-01-04
 */

#ifndef WIN_COMPAT_H
#define WIN_COMPAT_H
#ifdef _WIN32

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int asprintf(char ** str, const char * fmt, ...);
int vasprintf(char ** str, const char * fmt, va_list args);

#else
    #define _GNU_SOURCE
#endif
#endif