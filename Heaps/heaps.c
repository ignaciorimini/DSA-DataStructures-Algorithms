#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functionPrototypes.h"
#include "heaps.h"

BHeap bheap_create(int size, CompareFunction comp, DestroyFunction destroy, CopyFunction copy){
    BHeap heap= malloc(sizeof(struct _BHeap));
    heap->array= malloc(sizeof(void*)*size);
    heap->lastIndex= -1;
    heap->size= size;
    heap->comp= comp;
    heap->destroy= destroy;
    heap->copy= copy;
    
    for(int i=0; i<size; i++){
        heap->array[i]= NULL;
    }
    return heap;
}

void bheap_destroy(BHeap heap){
    for(int i=0; i <= heap->lastIndex; i++){
        heap->destroy(heap->array[i]);
    }

    free(heap->array);
    free(heap);
}

int bheap_is_empty(BHeap heap){
    return heap->lastIndex == -1;
}

void bheap_iteration(BHeap heap, VisitFunction visit){
    for(int i=0; i <= heap->lastIndex; i++){
        visit(heap->array[i]);
    }
}

int bheap_search(BHeap heap, void* val){
    for(int i=0; i<=heap->lastIndex; i++){
        if(heap->comp(heap->array[i], val) == 0){
            return 1;
        }
    }
    return 0;
}

void swap(void** val1, void** val2){
    void* temp= *val1;
    *val1= *val2;
    *val2= temp;
}

BHeap bheap_insert(BHeap heap, void* val){
    if(bheap_search(heap, val) == 1){
        return heap;
    }

    if(heap->lastIndex == heap->size - 1){
        heap->size*=2;
        heap->array= realloc(heap->array, sizeof(void*)*heap->size);
    }

    heap->lastIndex++;
    heap->array[heap->lastIndex]= heap->copy(val);

    int i= heap->lastIndex;
    while(i > 0 && heap->comp(heap->array[(i-1)/2], heap->array[i]) < 0){
        swap(&(heap->array[(i-1)/2]), &(heap->array[i]));
        i= (i-1)/2;
    }

    return heap;
}

BHeap bheap_delete(BHeap heap, void* val){
    if(bheap_search(heap, val) == 0){
        return heap;
    }

    if(heap->lastIndex == 0 && heap->comp(heap->array[heap->lastIndex], val) == 0){
        heap->destroy(heap->array[0]);
        heap->array[0]= NULL;
        heap->lastIndex--;
        return heap;
    }else{
        for(int i=0; i <= heap->lastIndex; i++){

            if(heap->array[i] != NULL && heap->comp(heap->array[i], val) == 0){
                heap->destroy(heap->array[i]);

                if(i != heap->lastIndex){
                    heap->array[i]= heap->copy(heap->array[heap->lastIndex]);
                    heap->destroy(heap->array[heap->lastIndex]);
                    heap->array[heap->lastIndex]= NULL;
                }

                heap->lastIndex--;

                while(2*i+i <= heap->lastIndex){
                    int leftChild= 2*i+1;
                    int rightChild= 2*i+2;
                    int largestIndex= i;

                    if(heap->comp(heap->array[leftChild], heap->array[largestIndex]) > 0){
                        largestIndex= leftChild;
                    }

                    if(rightChild <= heap->lastIndex && heap->comp(heap->array[rightChild], heap->array[largestIndex]) > 0){
                        largestIndex= rightChild;
                    }

                    if(largestIndex == i){
                        break;
                    }

                    swap(&(heap->array[largestIndex]), &(heap->array[i]));
                    i= largestIndex;
                }

                return heap;
            }
        }
    }

    return heap;
}

BHeap bheap_create_from_array(void** array, int arraySize, CompareFunction comp, DestroyFunction destroy, CopyFunction copy){
    BHeap heap= bheap_create(arraySize, comp, destroy, copy);

    for(int i=0; i<arraySize; i++){
        if(bheap_search(heap, array[i]) == 0){
            heap->lastIndex++;
            heap->array[heap->lastIndex]= heap->copy(array[i]);

            int j= heap->lastIndex;
            while(j>0 && heap->comp(heap->array[(j-1)/2], heap->array[j]) < 0){
                swap(&(heap->array[(j-1)/2]), &(heap->array[j]));
                j= (j-1)/2;
            }
        }
    }

    return heap;
}