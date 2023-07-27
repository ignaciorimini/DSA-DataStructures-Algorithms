#ifndef _SINGLYLINKEDLIST_
#define _SINGLYLINKEDLIST_

typedef struct _SNode{
    int val;
    struct _SNode* next;
} SNode;

typedef SNode* SList;

SList slist_create();
void slist_destroy(SList head);
SList slist_add_head(SList head, int val);
SList slist_add_end(SList head, int val);
void slist_iterate(SList head);
int slist_size(SList head);
int slist_value_in_list(SList head, int val);
SList slist_eliminate_value(SList head, int val);

#endif