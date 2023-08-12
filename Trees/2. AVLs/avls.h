#ifndef _AVLS_
#define _AVLS_
#include "functionPrototypes.h"

typedef struct _AVLNode{
    void* val;
    int height;
    struct _AVLNode* left;
    struct _AVLNode* right;
} AVLNode;

typedef struct _AVL{
    AVLNode* root;
    CompareFunction comp;
    CopyFunction copy;
    DestroyFunction destroy;
} *AVL;

typedef enum{
    PRE,
    IN,
    POST
} Order;

AVL avl_create(CompareFunction comp, CopyFunction copy, DestroyFunction destroy);
void avl_destroy_aux(AVLNode* root, DestroyFunction destroy);
void avl_destroy(AVL avl);
int avl_search_aux(AVLNode* root, void* val, CompareFunction comp);
int avl_search(AVL avl, void* val);
void avl_dfs_recursive(AVLNode* root, Order order, VisitFunction visit);
void avl_iteration(AVL avl, Order order, VisitFunction visit);
int avl_height_node(AVLNode* root);
int avl_max_height_children(AVLNode* root);
int balance_factor(AVLNode* root);
AVLNode* avl_rotation_toleft(AVLNode* root);
AVLNode* avl_node_insert(AVLNode* root, void* val, CopyFunction copy, CompareFunction comp);
void avl_insert(AVL avl, void* val);
AVLNode* avl_min_node(AVLNode* root);
AVLNode* avl_delete_node(AVLNode* root, void* val, CompareFunction comp, CopyFunction copy, DestroyFunction destroy);
void avl_delete(AVL avl, void* val);

#endif