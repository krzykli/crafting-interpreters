#ifndef clox_chunk_h
#define clox_chunk_h

#include "types.h"
#include "common.h"
#include "value.h"


typedef struct {
    int offset;
    int line;
} LineStart;

typedef enum {
    OP_CONSTANT,
    OP_NIL,
    OP_TRUE,
    OP_FALSE,
    OP_EQUAL,
    OP_GREATER,
    OP_LESS,
    OP_NEGATE,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NOT,
    OP_RETURN,
} OpCode;

typedef struct {
    int count;
    int capacity;
    u8* code;

    int line_count;
    int line_capacity;
    LineStart* lines;

    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, u8 byte, int line);
void writeConstant(Chunk* chunk, Value value, int line);
int addConstant(Chunk* chunk, Value value);
int getLine(Chunk* chunk, int instructionIndex);


#endif
