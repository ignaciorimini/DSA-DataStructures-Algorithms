#include <stdio.h>
#include <stdlib.h>
#include "genericLinkedList.h"
#include "functionPrototypes.h"
#include "queuesUsingLists.h"

Queue queue_create(CompareFunction comp, CopyFunction copy, DestroyFunction destroy, VisitFunction visit){
    Queue queue= glist_create(comp, copy, destroy, visit);
    return queue;
}

void queue_destroy(Queue queue){
    glist_destroy(queue);
}

int queue_empty(Queue queue){
    if(queue->firstNode == NULL){
        return 1;
    }else{
        return 0;
    }
}

void* queue_first_value(Queue queue){
    return (queue->firstNode == NULL) ? NULL : queue->firstNode->val;
}

void queue_iteration(Queue queue){
    glist_iteration(queue);
}

Queue queue_enqueue(Queue queue, void* val){
    queue= glist_add_end(queue, val);
    return queue;
}

Queue queue_dequeue(Queue queue){
    if(queue_first_value(queue) != NULL){
        queue= glist_eliminate_value(queue, queue_first_value(queue));
    }
    
    return queue;
}