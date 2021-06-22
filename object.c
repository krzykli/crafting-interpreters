#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <math.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"
#include "vm.h"

void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
    case OBJ_STRING:
      printf("%s", AS_CSTRING(value));
      break;
  }
}

#define INT32_MAX_DIGITS 10

#define ALLOCATE_OBJ(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType)

static u32 hashString(const char* key, int length) {
  uint32_t hash = 2166136261u;
  for (int i = 0; i < length; i++) {
    hash ^= (uint8_t)key[i];
    hash *= 16777619;
  }
  return hash;
}

static u32 hash(Obj* object) {
    char* key;
    int length;

    switch (object->type) {
        case OBJ_STRING: {
            ObjString* objStr = (ObjString*)object;
            key = objStr->chars;
            length = objStr->length;
            break;
        }
        case OBJ_INT: {
            ObjInt* objInt = (ObjInt*)object;
            int value = objInt->value;
            int digits = floor(log10(abs(value))) + 1;
            char buffer[INT32_MAX_DIGITS];
            sprintf(buffer, "%d", value);
            key = buffer;
            length = digits;
            break;
        }
        case OBJ_BOOL: {
            ObjBool* objBool = (ObjBool*)object;
            key = objBool->value ? "true" : "false";  // read from defines?
            u8 length = objBool->value ? 4 : 5;  // read from defines?
            break;
        }
        default:
           return NULL;
    }
    return hashString(key, length);
}

static Obj* allocateObject(size_t size, ObjType type) {
    Obj* object = (Obj*)reallocate(NULL, 0, size);
    object->type = type;
    object->next = vm.objects;
    vm.objects = object;
    return object;
}

static ObjString* allocateString(char* chars, int length) {
    ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
    string->length = length;
    string->chars = chars;
    object.obj.hash = hash(object);
    tableSet(&vm.strings, string, NIL_VAL);
    return string;
}


ObjString* takeString(char* chars, int length) {
    u32 hash = hashString(chars, length);
    ObjString* interned = tableFindString(&vm.strings, chars, length, hash);
    if (interned != NULL) {
        FREE_ARRAY(char, chars, length + 1);
        return interned;
    }

    return allocateString(chars, length, hash);
}

ObjString* copyString(const char* chars, int length) {
    u32 hash = hashString(chars, length);
    ObjString* interned = tableFindString(&vm.strings, chars, length,
            hash);
    if (interned != NULL)
        return interned;
    char* heapChars = ALLOCATE(char, length + 1);
    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';
    return allocateString(heapChars, length);
}
