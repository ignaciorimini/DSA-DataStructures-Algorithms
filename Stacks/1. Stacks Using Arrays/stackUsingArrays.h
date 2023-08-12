#ifndef _STACKSARRAYS_
#define _STACKSARRAYS_
#include "functionPrototypes.h"

typedef struct _Stack{
    void** array;
    int lastIndex;
    CopyFunction copy;
    DestroyFunction destroy;
    VisitFunction visit;
} *Stack;

Stack stack_create(CopyFunction copy, DestroyFunction destroy, VisitFunction visit);
void stack_destroy(Stack stack);
int stack_is_empty(Stack stack);
void* stack_last_value(Stack stack);
Stack stack_push(Stack stack, void* val);
Stack stack_pop(Stack stack);
Stack stack_iteration(Stack stack);

#endif