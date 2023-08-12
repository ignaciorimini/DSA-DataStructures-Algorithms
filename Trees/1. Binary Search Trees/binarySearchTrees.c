#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functionPrototypes.h"
#include "binarySearchTrees.h"

BSTree bstree_create(){
    return NULL;
}

void bstree_destroy(BSTree root, DestroyFunction destroy){
    if(root!=NULL){
        bstree_destroy(root->left, destroy);
        bstree_destroy(root->right, destroy);
        destroy(root->val);
        free(root);
    }
}

int bstree_search(BSTree root, void* val, CompareFunction comp){
    if(root==NULL){
        return 0;
    }else if(comp(val, root->val) < 0){
        return bstree_search(root->left, val, comp);
    }else if(comp(val, root->val) > 0){
        return bstree_search(root->right, val, comp);
    }else{
        return 1;
    }
}

void bstree_dfs_recursive(BSTree root, Order order, VisitFunction visit){
    if(root!=NULL){
        if(order == PRE){
            visit(root->val);
        }

        bstree_dfs_recursive(root->left, order, visit);

        if(order == IN){
            visit(root->val);
        }

        bstree_dfs_recursive(root->right, order, visit);

        if(order == POST){
            visit(root->val);
        }
    }
}

void visit_level(BSTree root, int level, VisitFunction visit){
    if(root == NULL){
        return;
    }

    if(level == 0){
        visit(root->val);
    }else if(level > 0){
        visit_level(root->left, level-1, visit);
        visit_level(root->right, level-1, visit);
    }
}

int bstree_height(BSTree root){
    if(root == NULL){
        return -1;
    }

    int leftHeight= bstree_height(root->left);
    int rightHeight= bstree_height(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void bstree_bfs_recursive(BSTree root, VisitFunction visit){
    int height= bstree_height(root);

    for(int level=0; level<=height; level++){
        visit_level(root, level, visit);
    }
}

BSTree bstree_insert(BSTree root, void* val, CompareFunction comp, CopyFunction copy){
    if(root == NULL){
        BSTNode* node= malloc(sizeof(BSTNode));
        node->val= copy(val);
        node->left= NULL;
        node->right= NULL;
        return node;
    }else if(comp(val, root->val) < 0){
        root->left= bstree_insert(root->left, val, comp, copy);
    }else if(comp(val, root->val) > 0){
        root->right= bstree_insert(root->right, val, comp, copy);
    }

    return root;
}

BSTree bstree_min(BSTree root){
    if(root == NULL){
        return root;
    }

    while(root->left != NULL){
        root= root->left;
    }

    return root;
}

BSTree bstree_delete(BSTree root, void* val, CompareFunction comp, DestroyFunction destroy, CopyFunction copy){
    if(root == NULL){
        return NULL;
    }

    if(comp(val, root->val) < 0){
        root->left= bstree_delete(root->left, val, comp, destroy, copy);
    }else if(comp(val, root->val) > 0){
        root->right= bstree_delete(root->right, val, comp, destroy, copy);
    }else{
        if(root->left == NULL && root->right == NULL){
            destroy(root->val);
            free(root);
            return NULL;
        }else if(root->left == NULL){
            BSTNode* temp= root->right;
            destroy(root->val);
            free(root);
            return temp;
        }else if(root->right == NULL){
            BSTNode* temp= root->left;
            destroy(root->val);
            free(root);
            return temp;
        }else if(root->left != NULL && root->right != NULL){
            BSTNode* newRoot= bstree_min(root->right);
            root->val= copy(newRoot->val);
            root->right= bstree_delete(root->right, newRoot->val, comp, destroy, copy);
        }
    }
}