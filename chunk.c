#include <stdlib.h>

#include "memory.h"
#include "value.h"
#include "types.h"
#include "chunk.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;

    chunk->line_count = 0;
    chunk->line_capacity = 0;
    chunk->lines = NULL;

    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(u8, chunk->code, chunk->capacity);
    FREE_ARRAY(u8, chunk->lines, chunk->line_capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, u8 byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(u8, chunk->code,
                oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;

    if (chunk->line_count > 0 &&
            chunk->lines[chunk->line_count - 1].line == line) {
        return;
    }

    if (chunk->line_capacity < chunk->line_count + 1) {
        int old_capacity = chunk->line_count;
        chunk->line_capacity = GROW_CAPACITY(old_capacity);
        chunk->lines = GROW_ARRAY(LineStart, chunk->lines,
                old_capacity, chunk->line_capacity);
    }

    LineStart* lineStart = &chunk->lines[chunk->line_count++];
    lineStart->offset = chunk->count - 1;
    lineStart->line = line;
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}


int getLine(Chunk* chunk, int instruction) {
    int start = 0;
    int end = chunk->line_count - 1;

    for (;;) {
        int mid = (start + end) / 2;
        LineStart* line = &chunk->lines[mid];
        if (instruction < line->offset) {
            end = mid - 1;
        } else if (mid == chunk->line_count - 1 ||
                instruction < chunk->lines[mid + 1].offset) {
            return line->line;
        } else {
            start = mid + 1;
        }
    }
}
