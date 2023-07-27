#include <stdio.h>
#include <stdlib.h>
#include "doublyLinkedList.h"

DList* dlist_create(){
    DList* list= malloc(sizeof(DList));
    list->firstNode= NULL;
    list->lastNode= NULL;
    return list;
}

void dlist_destroy(DList* list){
    if(list->firstNode != NULL){
        DNode* temp= list->firstNode;
        while(temp != NULL){
            DNode* next= temp->next;
            free(temp);
            temp= next;
        }
    }

    free(list);
}

DList* dlist_add_head(DList* list, int val){
    DNode* newNode= malloc(sizeof(DNode));
    newNode->val= val;
    newNode->prev= NULL;
    newNode->next= list->firstNode;

    if(list->firstNode == NULL){
        list->lastNode= newNode;
    }else{
        list->firstNode->prev= newNode;
    }

    list->firstNode= newNode;
    return list;
}

DList* dlist_add_end(DList* list, int val){
    DNode* newNode= malloc(sizeof(DNode));
    newNode->val= val;
    newNode->next= NULL;
    newNode->prev= list->lastNode;

    if(list->lastNode == NULL){
        list->firstNode= newNode;    
    }else{
        list->lastNode->next= newNode;
    }

    list->lastNode= newNode;
    return list;
}

void dlist_forward_iteration(DList* list){
    DNode* temp= list->firstNode;
    while(temp != NULL){
        printf("%d ", temp->val);
        temp= temp->next;
    }
}

void dlist_backward_iteration(DList* list){
    DNode* temp= list->lastNode;
    while(temp != NULL){
        printf("%d ", temp->val);
        temp= temp->prev;
    }
}

int dlist_size(DList* list){
    int size= 0;
    DNode* temp= list->firstNode;
    while(temp!=NULL){
        size++;
        temp= temp->next;
    }
    return size;
}

DList* dlist_eliminate_value(DList* list, int val){
    if(list->firstNode == NULL){
        return list;
    }

    DNode* tempNode= list->firstNode;
    DNode* nextNode= tempNode->next;
    DNode* prevNode= NULL;
    while(tempNode != NULL && tempNode->val != val){
        prevNode= tempNode;
        tempNode= nextNode;
        if (tempNode != NULL) {
            nextNode = tempNode->next;
        }
    }

    if(tempNode != NULL && tempNode->val == val){
        if(prevNode == NULL){
            free(tempNode);
            if(nextNode != NULL){
                nextNode->prev= NULL;
            }else{
                list->lastNode= prevNode;
            }
            list->firstNode= nextNode;
        }else{
            prevNode->next= nextNode;
            if(nextNode != NULL){
                nextNode->prev= prevNode;
            }else{
                list->lastNode= prevNode;
            }
            free(tempNode);
        }
    }

    return list;
}