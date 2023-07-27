#ifndef _GENERICLINKEDLIST_
#define _GENERICLINKEDLIST_
#include "functionPrototypes.h"

typedef struct _GNode{
    void* val;
    struct _GNode* next;
} GNode;

typedef struct _GList{
    GNode* firstNode;
    GNode* lastNode;
    CompareFunction comp;
    CopyFunction copy;
    DestroyFunction destroy;
    VisitFunction visit;
} GList;

GList* glist_create(CompareFunction comp, CopyFunction copy, DestroyFunction destroy, VisitFunction visit);
void glist_destroy(GList* list);
GList* glist_add_head(GList* list, void* val);
GList* glist_add_end(GList* list, void* val);
void glist_iteration(GList* list);
int glist_value_in_list(GList* list, void* val);
GList* glist_eliminate_value(GList* list, void* val);

#endif