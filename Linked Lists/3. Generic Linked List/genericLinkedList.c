#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functionPrototypes.h"
#include "genericLinkedList.h"

GList* glist_create(CompareFunction comp, CopyFunction copy, DestroyFunction destroy, VisitFunction visit){
    GList* list= malloc(sizeof(GList));
    list->firstNode= NULL;
    list->lastNode= NULL;
    list->comp= comp;
    list->copy= copy;
    list->destroy= destroy;
    list->visit= visit;
    return list;
}

void glist_destroy(GList* list){
    GNode* temp= list->firstNode;
    while(temp!=NULL){
        GNode* nextNode= temp->next;
        list->destroy(temp->val);
        free(temp);
        temp= nextNode;
    }
    free(list);
}

GList* glist_add_head(GList* list, void* val){
    GNode* newNode= malloc(sizeof(GNode));
    newNode->val= list->copy(val);
    newNode->next= list->firstNode;

    if(list->lastNode == NULL){
        list->lastNode= newNode;
    }

    list->firstNode= newNode;
    return list;
}

GList* glist_add_end(GList* list, void* val){
    GNode* newNode= malloc(sizeof(GNode));
    newNode->val= list->copy(val);
    newNode->next= NULL;

    if(list->lastNode == NULL){
        list->firstNode= newNode;
    }else{
        list->lastNode->next= newNode;
    }

    list->lastNode= newNode;
    return list;
}

void glist_iteration(GList* list){
    GNode* temp= list->firstNode;
    while(temp!=NULL){
        list->visit(temp->val);
        temp= temp->next;
    }
}

int glist_value_in_list(GList* list, void* val){
    GNode* temp= list->firstNode;

    while(temp!=NULL && list->comp(temp->val, val) != 0){
        temp= temp->next;
    }

    if(temp!=NULL && list->comp(temp->val, val) == 0){
        return 1;
    }else{
        return 0;
    }
}

GList* glist_eliminate_value(GList* list, void* val){
    if(list->firstNode == NULL){
        return list;
    }

    GNode* tempNode= list->firstNode;
    GNode* nextNode= tempNode->next;
    GNode* prevNode= NULL;
    while(tempNode!=NULL && list->comp(tempNode->val, val) != 0){
        prevNode= tempNode;
        tempNode= nextNode;
        if(tempNode != NULL){
            nextNode= tempNode->next;
        }
    }

    if(tempNode != NULL && list->comp(tempNode->val, val) == 0){
        if(prevNode == NULL){
            list->firstNode= nextNode;
            if(nextNode == NULL){
                list->lastNode= prevNode;
            }
        }else{
            prevNode->next= nextNode;
            if(nextNode == NULL){
                list->lastNode= prevNode;
            }
        }
        list->destroy(tempNode->val);
        free(tempNode);
    }

    return list;
}