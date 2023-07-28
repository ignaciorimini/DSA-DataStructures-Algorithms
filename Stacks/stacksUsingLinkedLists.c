#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genericLinkedList.h"
#include "stackUsingLinkedLists.h"

Stack stack_create(CompareFunction comp, CopyFunction copy, DestroyFunction destroy, VisitFunction visit){
    Stack stack= glist_create(comp, copy, destroy, visit);
    return stack;
}

void stack_destroy(Stack stack){
    glist_destroy(stack);
}

void* stack_last_value(Stack stack){
    if(stack->lastNode != NULL){
        return stack->lastNode->val;
    }else{
        return NULL;
    }

}

Stack stack_push(Stack stack, void* val){
    stack= glist_add_end(stack, val);
    return stack;
}

Stack stack_pop(Stack stack){
    stack= glist_eliminate_last_node(stack);
    return stack;
}

void stack_iteration(Stack stack){
    glist_iteration(stack);
}