#ifndef _QUEUESARRAYS_
#define _QUEUESARRAYS_
#include "functionPrototypes.h"

typedef struct _Queue{
    void** array;
    int capacity;
    int firstIndex;
    int lastIndex;
    CompareFunction comp;
    CopyFunction copy;
    DestroyFunction destroy;
    VisitFunction visit;
} Queue;

Queue* queue_create(int capacity, CompareFunction comp, CopyFunction copy, DestroyFunction destroy, VisitFunction visit);
void queue_destroy(Queue* queue);
int queue_empty(Queue* queue);
void* queue_first_value(Queue* queue);
void queue_iteration(Queue* queue);
Queue* queue_enqueue(Queue* queue, void* val);
Queue* queue_dequeue(Queue* queue);

#endif