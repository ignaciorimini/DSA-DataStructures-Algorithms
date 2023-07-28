#ifndef _STACKSLISTS_
#define _STACKSLISTS_
#include "functionPrototypes.h"
#include "genericLinkedList.h"

typedef GList* Stack;

Stack stack_create(CompareFunction comp, CopyFunction copy, DestroyFunction destroy, VisitFunction visit);
void stack_destroy(Stack stack);
void* stack_last_value(Stack stack);
Stack stack_push(Stack stack, void* val);
Stack stack_pop(Stack stack);
void stack_iteration(Stack stack);

#endif
