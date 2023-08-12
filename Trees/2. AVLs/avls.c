#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functionPrototypes.h"
#include "avls.h"

AVL avl_create(CompareFunction comp, CopyFunction copy, DestroyFunction destroy){
    AVL avl= malloc(sizeof(struct _AVL));
    avl->comp= comp;
    avl->copy= copy;
    avl->destroy= destroy;
    avl->root= NULL;
    return avl;
}

void avl_destroy(AVL avl){
    avl_destroy_aux(avl->root, avl->destroy);
    free(avl);
}

void avl_destroy_aux(AVLNode* root, DestroyFunction destroy){
    if(root != NULL){
        avl_destroy_aux(root->left, destroy);
        avl_destroy_aux(root->right, destroy);
        destroy(root->val);
        free(root);
    }
}

int avl_search(AVL avl, void* val){
    return avl_search_aux(avl->root, val, avl->comp);
}

int avl_search_aux(AVLNode* root, void* val, CompareFunction comp){
    if(root == NULL){
        return 0;
    }else if(comp(val, root->val) < 0){
        return avl_search_aux(root->left, val, comp);
    }else if(comp(val, root->val) > 0){
        return avl_search_aux(root->right, val, comp);
    }else{
        return 1;
    }
}

void avl_iteration(AVL avl, Order order, VisitFunction visit){
    avl_dfs_recursive(avl->root, order, visit);
}

void avl_dfs_recursive(AVLNode* root, Order order, VisitFunction visit){
    if(root != NULL){
        if(order == PRE){
            visit(root->val);
        }

        avl_dfs_recursive(root->left, order, visit);

        if(order == IN){
            visit(root->val);
        }

        avl_dfs_recursive(root->right, order, visit);

        if(order == POST){
            visit(root->val);
        }
    }
}

AVLNode* avl_rotation_toleft(AVLNode* root){
    AVLNode* rightChild= root->right;

    root->right= rightChild->left;
    rightChild->left= root;

    root->height= 1 + avl_max_height_children(root);
    rightChild->height= 1 + avl_max_height_children(rightChild);
    return rightChild;
}

AVLNode* avl_rotation_toright(AVLNode* root){
    AVLNode* leftChild= root->left;

    root->left= leftChild->right;
    leftChild->right= root;

    root->height= 1 + avl_max_height_children(root);
    leftChild->height= 1 + avl_max_height_children(leftChild); 
}

void avl_insert(AVL avl, void* val){
    avl->root= avl_node_insert(avl->root, val, avl->copy, avl->comp);
}

AVLNode* avl_node_insert(AVLNode* root, void* val, CopyFunction copy, CompareFunction comp){
    if(root == NULL){
        AVLNode* node= malloc(sizeof(AVLNode));
        node->val= copy(val);
        node->height= 0;
        node->left= NULL;
        node->right= NULL;
        return node;
    }else if(comp(val, root->val) < 0){
        root->left= avl_node_insert(root->left, val, copy, comp);

        if(balance_factor(root) == 2){
            if(balance_factor(root->left) == -1){
                root->left= avl_rotation_toleft(root->left);
            }
            root= avl_rotation_toright(root);
        }

        root->height= 1 + avl_max_height_children(root);
        return root;
    }else if(comp(val, root->val) > 0){
        root->right= avl_node_insert(root->right, val, copy, comp);

        if(balance_factor(root) == -2){
            if(balance_factor(root->right) == 1){
                root->right= avl_rotation_toright(root->right);
            }
            root= avl_rotation_toleft(root);
        }

        root->height= 1 + avl_max_height_children(root);
        return root;
    }else{
        return root;
    }
}

int avl_height_node(AVLNode* root){
    return (root == NULL) ? -1 : root->height;
}

int avl_max_height_children(AVLNode* root){
    int leftHeight= avl_height_node(root->left);
    int rightHeight= avl_height_node(root->right);
    return (leftHeight >= rightHeight) ? leftHeight : rightHeight;
}

int balance_factor(AVLNode* root){
    return avl_height_node(root->left) - avl_height_node(root->right);
}

AVLNode* avl_min_node(AVLNode* root){
    if(root == NULL){
        return root;
    }

    while(root->left != NULL){
        root= root->left;
    }

    return root;
}

void avl_delete(AVL avl, void* val){
    if(avl == NULL || avl->root == NULL){
        return;
    }

    avl->root= avl_delete_node(avl->root, val, avl->comp, avl->copy, avl->destroy);
}

AVLNode* avl_delete_node(AVLNode* root, void* val, CompareFunction comp, CopyFunction copy, DestroyFunction destroy){
    if(root == NULL){
        return root;
    }
    else if(comp(val, root->val) < 0){
        root->left= avl_delete_node(root->left, val, comp, copy, destroy);
    }
    else if(comp(val, root->val) > 0){
        root->right= avl_delete_node(root->right, val, comp, copy, destroy);
    }
    else{
        if(root->left == NULL && root->right == NULL){
            destroy(root->val);
            free(root);
            return NULL;
        }
        else if(root->right == NULL){
            AVLNode* temp= root->left;
            destroy(root->val);
            free(root);
            return temp;
        }
        else if(root->left == NULL){
            AVLNode* temp= root->right;
            destroy(root->val);
            free(root);
            return temp;
        }
        else if(root->left != NULL && root->right != NULL){
            AVLNode* newRoot= avl_min_node(root->right);
            root->val= copy(newRoot->val);
            root->right= avl_delete_node(root->right, newRoot->val, comp, copy, destroy);
        }
    }

    if(balance_factor(root) == 2){
        if(balance_factor(root->left) == -1){
            root->left= avl_rotation_toleft(root->left);
        }
        root= avl_rotation_toright(root);
    }

    if(balance_factor(root) == -2){
        if(balance_factor(root->right) == 1){
            root->right= avl_rotation_toright(root->right);
        }
        root= avl_rotation_toleft(root);
    }

    return root;
}