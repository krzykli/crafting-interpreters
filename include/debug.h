#ifndef clox_debug_h
#define clox_debug_h

#include <stdarg.h>
#include "chunk.h"

#define print(format, ...) \
    printf("%s\t| %s:%d\t| " format "\n", __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);


#endif
