#include <stdio.h>
#include <stdlib.h>
#include "functionPrototypes.h"
#include "stackUsingArrays.h"
#define SIZE_STACK 3

// Stacks using arrays with generic data values (void*).

Stack stack_create(CopyFunction copy, DestroyFunction destroy, VisitFunction visit){
    Stack newStack= malloc(sizeof(struct _Stack));
    newStack->array= malloc(sizeof(void*)*SIZE_STACK);
    newStack->lastIndex= -1;
    newStack->copy= copy;
    newStack->destroy= destroy;
    newStack->visit= visit;
    return newStack;
}

void stack_destroy(Stack stack){
    for(int i=0; i<=stack->lastIndex; i++){
        free(stack->array[i]);
    }
    free(stack->array);
    free(stack);
}

int stack_is_empty(Stack stack){
    return stack->lastIndex == -1;
}

void* stack_last_value(Stack stack){
    if(stack->lastIndex != -1){
        return stack->array[stack->lastIndex];
    }else{
        return NULL;
    }
}

Stack stack_push(Stack stack, void* val){
    stack->lastIndex++;

    if(SIZE_STACK == stack->lastIndex+1){
        stack->array= realloc(stack->array, sizeof(void*)*((stack->lastIndex+1)*2));
    }

    stack->array[stack->lastIndex]= stack->copy(val);
    return stack;
}

Stack stack_pop(Stack stack){
    if(stack->lastIndex == -1){
        return stack;
    }

    free(stack->array[stack->lastIndex]);
    stack->lastIndex--;
    return stack;
}

Stack stack_iteration(Stack stack){
    for(int i=0; i<=stack->lastIndex; i++){
        stack->visit(stack->array[i]);
    }
}