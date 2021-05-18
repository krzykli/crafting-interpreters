#ifndef clox_vm_h
#define clox_vm_h

#define STACK_MAX 256
#include "value.h"

#include "chunk.h"

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

typedef struct {
    Chunk* chunk;
    u8* ip;
    Value stack[STACK_MAX];
    Value* stackTop;
} VM;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();

#endif
