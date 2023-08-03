#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functionPrototypes.h"
#include "queuesUsingArrays.h"

Queue* queue_create(int capacity, CompareFunction comp, CopyFunction copy, DestroyFunction destroy, VisitFunction visit){
    Queue* newQueue= malloc(sizeof(Queue));
    newQueue->array= malloc(sizeof(void*)*capacity);
    newQueue->capacity= capacity;
    newQueue->firstIndex= -1;
    newQueue->lastIndex= -1;
    newQueue->comp= comp;
    newQueue->copy= copy;
    newQueue->destroy= destroy;
    newQueue->visit= visit;
    for(int i=0; i<capacity; i++){
        newQueue->array[i]= NULL;
    }
    return newQueue;
}

void queue_destroy(Queue* queue){
    for(int i=0; i<queue->capacity; i++){
        if(queue->array[i] != NULL){
            queue->destroy(queue->array[i]);
        }
    }
    free(queue->array);
    free(queue);
}

int queue_empty(Queue* queue){
    return (queue->firstIndex == -1) ? 1 : 0;
}

void* queue_first_value(Queue* queue){
    return (queue->firstIndex == -1) ? NULL : queue->array[queue->firstIndex];
}

void queue_iteration(Queue* queue){
    for(int i=0; i<queue->capacity; i++){
        if(queue->array[i] != NULL){
            queue->visit(queue->array[i]);
        }
    }
}

Queue* queue_enqueue(Queue* queue, void* val){
    if(queue_empty(queue)){
        queue->firstIndex= 0;
        queue->lastIndex= 0;
    }else{
        queue->lastIndex = (queue->lastIndex + 1) % queue->capacity;
        if(queue->lastIndex == queue->firstIndex){
            queue->destroy(queue->array[queue->firstIndex]);
            queue->array[queue->firstIndex]= NULL;
            queue->firstIndex = (queue->firstIndex + 1) % queue->capacity;
        }
    }

    queue->array[queue->lastIndex] = queue->copy(val);
    return queue;
}

Queue* queue_dequeue(Queue* queue){
    if(queue_empty(queue)){
        return queue;
    }

    queue->destroy(queue->array[queue->firstIndex]);
    queue->array[queue->firstIndex]= NULL;

    if (queue->firstIndex == queue->lastIndex) {
        queue->firstIndex = -1;
        queue->lastIndex = -1;
    }else {
        queue->firstIndex = (queue->firstIndex + 1) % queue->capacity;
    }

    return queue;
}