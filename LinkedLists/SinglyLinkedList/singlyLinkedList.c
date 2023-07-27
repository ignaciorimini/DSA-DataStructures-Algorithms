#include <stdio.h>
#include <stdlib.h>
#include "singlylinkedlist.h"

SList slist_create(){
    return NULL;
}

void slist_destroy(SList head){
    if(head != NULL){
        SNode* temp= head;
        while(temp != NULL){
            SNode* next= temp->next;
            free(temp);
            temp= next;
        }
    }
}

SList slist_add_head(SList head, int val){
    SNode* newNode= malloc(sizeof(SNode));
    newNode->val= val;
    newNode->next= head;
    return newNode;
}

SList slist_add_end(SList head, int val){
    SNode* newNode= malloc(sizeof(SNode));
    newNode->val= val;
    newNode->next= NULL;

    if(head==NULL){
        return newNode;
    }else{
        SNode* temp= head;
        for(; temp->next != NULL; temp= temp->next);
        temp->next= newNode;
        return head;
    }
}

void slist_iterate(SList head){
    SNode* temp= head;
    while(temp != NULL){
        printf("%d ", temp->val);
        temp= temp->next;
    }
}

int slist_size(SList head){
    int size= 0;
    SNode* temp= head;
    while(temp!=NULL){
        size++;
        temp= temp->next;
    }
    return size;
}

int slist_value_in_list(SList head, int val){
    SNode* temp= head;
    for(; temp != NULL && temp->val != val; temp= temp->next);

    if(temp == NULL){
        return 0;
    }else{
        return 1;
    }
}

SList slist_eliminate_value(SList head, int val){
    if(head == NULL){
        return head;
    }

    SNode* temp= head;
    SNode* prev= NULL;

    while(temp != NULL){
        SNode* next= temp->next;

        if(temp->val == val){
            if(prev==NULL){
                free(temp);
                return next;
            }else{
                free(temp);
                prev->next= next;
                return head;
            }
        }

        prev= temp;
        temp= next;
    }

    return head;
}