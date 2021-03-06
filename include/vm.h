#ifndef clox_vm_h
#define clox_vm_h

#include <string.h>

#include "object.h"
#include "value.h"
#include "table.h"
#include "chunk.h"

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct {
    ObjClosure* closure;
    uint8_t* ip;
    Value* slots;
} CallFrame;


typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

typedef struct {
    CallFrame frames[FRAMES_MAX];
    int frameCount;
    Value stack[STACK_MAX];
    Value* stackTop;
    ObjString* initString;
    ObjUpvalue* openUpvalues;
    Table globals;
    Table strings;
    Obj* objects;
    int grayCount;
    int grayCapacity;
    Obj** grayStack;
    size_t bytesAllocated;
    size_t nextGC;
} VM;

void initVM();
void freeVM();
InterpretResult interpret(const char* source);
extern VM vm; 

void push(Value value);
Value pop();

#endif
