#ifndef _BINARYSEARCHTREES_
#define _BINARYSEARCHTREES_
#include "functionPrototypes.h"

typedef struct _BSTNode{
    void* val;
    struct _BSTNode* left;
    struct _BSTNode* right;
} BSTNode;

typedef BSTNode* BSTree;

typedef enum{
    PRE,
    IN,
    POST
} Order;

BSTree bstree_create();
void bstree_destroy(BSTree root, DestroyFunction destroy);
int bstree_search(BSTree root, void* val, CompareFunction comp);
void bstree_dfs_recursive(BSTree root, Order order, VisitFunction visit);
void visit_level(BSTree root, int level, VisitFunction visit);
int bstree_height(BSTree root);
void bstree_bfs_recursive(BSTree root, VisitFunction visit);
BSTree bstree_insert(BSTree root, void* val, CompareFunction comp, CopyFunction copy);
BSTree bstree_min(BSTree root);
BSTree bstree_delete(BSTree root, void* val, CompareFunction comp, DestroyFunction destroy, CopyFunction copy);

#endif