#ifndef _QUEUESLISTS_
#define _QUEUESLISTS_
#include "genericLinkedList.h"
#include "functionPrototypes.h"

typedef GList* Queue;

Queue queue_create(CompareFunction comp, CopyFunction copy, DestroyFunction destroy, VisitFunction visit);
void queue_destroy(Queue queue);
int queue_empty(Queue queue);
void* queue_first_value(Queue queue);
void queue_iteration(Queue queue);
Queue queue_enqueue(Queue queue, void* val);
Queue queue_dequeue(Queue queue);

#endif