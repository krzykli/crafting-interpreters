#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "value.h"
#include "types.h"

#define OBJ_TYPE(value)        (AS_OBJ(value)->type)

#define IS_STRING(value)       isObjType(value, OBJ_STRING)

#define AS_STRING(value)       ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)      (((ObjString*)AS_OBJ(value))->chars)

void printObject(Value value);

typedef enum {
    OBJ_STRING,
    OBJ_INT,
    OBJ_BOOL
} ObjType;

struct Obj {
    ObjType type;
    u32 hash;
    struct Obj* next;
};

struct ObjString {
    Obj obj;
    int length;
    char* chars;
};

typedef struct ObjInt {
    Obj obj;
    int value;
} ObjInt;

typedef struct ObjBool {
    Obj obj;
    bool value;
} ObjBool;

ObjString* copyString(const char* chars, int length);

ObjString* takeString(char* chars, int length);

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif
