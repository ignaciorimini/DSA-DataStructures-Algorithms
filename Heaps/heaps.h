#ifndef _HEAPS_
#define _HEAPS_
#include "functionPrototypes.h"

typedef struct _BHeap{
    void** array;
    int lastIndex;
    int size;
    CompareFunction comp;
    DestroyFunction destroy;
    CopyFunction copy;
} *BHeap;

BHeap bheap_create(int size, CompareFunction comp, DestroyFunction destroy, CopyFunction copy);
void bheap_destroy(BHeap heap);
int bheap_is_empty(BHeap heap);
void bheap_iteration(BHeap heap, VisitFunction visit);
int bheap_search(BHeap heap, void* val);
void swap(void** val1, void** val2);
BHeap bheap_insert(BHeap heap, void* val);
BHeap bheap_delete(BHeap heap, void* val);
BHeap bheap_create_from_array(void** array, int arraySize, CompareFunction comp, DestroyFunction destroy, CopyFunction copy);

#endif