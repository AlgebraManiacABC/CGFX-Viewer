#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <string.h>
#include "debug.h"

typedef struct CGFX_s * CGFX;

CGFX CGFX_ReadFile(char * filename);

Uint32 CGFX_GetFileSize(CGFX);
const char * CGFX_GetMetadata(CGFX);

#endif