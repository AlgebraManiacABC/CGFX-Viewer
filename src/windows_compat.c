/**
 * @file windows_compat.c
 * @author Luke
 * @brief
 *  Adds functionality for `asprintf` and `vasprintf`
 *  under Windows, or at least under MinGW. Obviously,
 *  this is highly dependant on OS and compiler.
 *  Tweaks or recommendations welcome.
 * @date 2025-01-04
 */

#ifdef _WIN32
#include "windows_compat.h"

int asprintf(char ** str, const char * fmt, ...)
{
    va_list args;
    va_start(args,fmt);
    int retval = vasprintf(str,fmt,args);
    va_end(args);
    return retval;
}

int vasprintf(char ** str, const char * fmt, va_list args)
{
    return __mingw_vasprintf(str,fmt,args);
}

#endif