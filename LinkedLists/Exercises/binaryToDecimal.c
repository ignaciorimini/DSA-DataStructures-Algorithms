#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "singlyLinkedList.h"

// Solution to the following problem: https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/
// Difficulty: Easy

int binaryArrayToDecimal(int* array, int size){
    int sumaTotal= 0;
    for(int i=0; i<size; i++){
        if(array[i] == 1){
            sumaTotal+= pow(2, size-i-1);
        }
    }

    return sumaTotal;
}

int getDecimalValue(SList head){
    int* arrayValores= malloc(sizeof(int)*31);

    int i=0;
    while(head != NULL){
        arrayValores[i]= head->val;
        head= head->next;
        i++;
    }

    int sumaTotal= getSumaArray(arrayValores, i);
    free(arrayValores);
    return sumaTotal;
}

int main(){
    SList list= slist_create();
    list= slist_add_end(list, 1);
    list= slist_add_end(list, 0);
    list= slist_add_end(list, 1);
    list= slist_add_end(list, 1);

    printf("Binary number: %d\n", getDecimalValue(list));

    slist_iterate(list);
    slist_destroy(list);
    return 0;
}