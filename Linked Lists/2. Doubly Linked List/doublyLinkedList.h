#ifndef _DOUBLYLINKEDLIST_
#define _DOUBLYLINKEDLIST_

typedef struct _DNode{
    int val;
    struct _DNode* next;
    struct _DNode* prev;
} DNode;

typedef struct _DList{
    DNode* firstNode;
    DNode* lastNode;
} DList;

DList* dlist_create();
void dlist_destroy(DList* list);
DList* dlist_add_head(DList* list, int val);
DList* dlist_add_end(DList* list, int val);
void dlist_forward_iteration(DList* list);
void dlist_backward_iteration(DList* list);
int dlist_size(DList* list);
DList* dlist_eliminate_value(DList* list, int val);

#endif