#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "chunk.h"
#include "value.h"
#include "types.h"

#define OBJ_TYPE(value)        (AS_OBJ(value)->type)

#define IS_FUNCTION(value)     isObjType(value, OBJ_FUNCTION)
#define IS_NATIVE(value)       isObjType(value, OBJ_NATIVE)
#define IS_STRING(value)       isObjType(value, OBJ_STRING)

#define AS_FUNCTION(value)     ((ObjFunction*)AS_OBJ(value))
#define AS_NATIVE(value) \
    (((ObjNative*)AS_OBJ(value))->function)
#define AS_STRING(value)       ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)      (((ObjString*)AS_OBJ(value))->chars)

void printObject(Value value);

typedef enum {
    OBJ_STRING,
    OBJ_NATIVE,
    OBJ_FUNCTION
} ObjType;

struct Obj {
    ObjType type;
    struct Obj* next;
};

typedef struct {
  Obj obj;
  int arity;
  Chunk chunk;
  ObjString* name;
} ObjFunction;

typedef Value (*NativeFn)(int argCount, Value* args, ValueType* argTypes);

typedef struct {
    Obj obj;
    int arity;
    NativeFn function;
    ValueType* argTypes;
} ObjNative;

struct ObjString {
    Obj obj;
    int length;
    char* chars;
    u32 hash;
};

ObjString* copyString(const char* chars, int length);
ObjFunction* newFunction();
ObjNative* newNative(NativeFn function, int argCount, ValueType* argTypes);
ObjString* takeString(char* chars, int length);

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif
