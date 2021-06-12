#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
    case OBJ_STRING:
      printf("%s", AS_CSTRING(value));
      break;
  }
}

#define ALLOCATE_OBJ(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType)

static Obj* allocateObject(size_t size, ObjType type) {
    Obj* object = (Obj*)reallocate(NULL, 0, size);
    object->type = type;
    object->next = vm.objects;
    vm.objects = object;
    return object;
}

/*static ObjString* allocateString(char* chars, int length) {*/
    /*ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);*/
    /*string->length = length;*/
    /*[>string->chars = chars;<]*/
    /*memcpy(string->chars, chars, length);*/
    /*return string;*/
/*}*/

ObjString* allocateString(char* chars, int length) {
    size_t stringSize = sizeof(ObjString) + sizeof(char) * length + 1;
    ObjString* string = (ObjString*)allocateObject(stringSize, OBJ_STRING);
    string->length = length;
    memcpy(string->chars, chars, length);
    string->chars[length] = '\0';
    return string;
}

ObjString* takeString(char* chars, int length) {
    return allocateString(chars, length);
}

ObjString* copyString(const char* chars, int length) {
    return allocateString(chars, length);
}

