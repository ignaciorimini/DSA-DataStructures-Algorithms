#include <stdio.h>
#include <stdlib.h>
#include "singlylinkedlist.h"

// Solution to the following problem: https://leetcode.com/problems/middle-of-the-linked-list/description/
// Difficulty: Easy

SList middleNode(SList head){
    int nodes= 0;
    SNode* temp= head;
    while(temp!=NULL){
        nodes++;
        temp= temp->next;
    }

    temp= head;
    for(int i=0; i<(nodes/2); i++){
        temp= temp->next;
    }

    return temp;
}

int main(){
    SList list= slist_create();
    list= slist_add_end(list, 1);
    list= slist_add_end(list, 2);
    list= slist_add_end(list, 3);
    list= slist_add_end(list, 4);
    list= slist_add_end(list, 5);
    list= slist_add_end(list, 6);
    
    SList listMiddle= middleNode(list);
    slist_iterate(listMiddle);
    printf("\n");

    slist_iterate(list);
    slist_destroy(list);
    return 0;
}