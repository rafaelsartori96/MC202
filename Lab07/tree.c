#include <stdlib.h>
#include "tree.h"


/**
* Frees up the memory of the node, removing its brothers and sons.
*/
void free_node(Node *node);


int initialize_node_pool(Node **node_pool, int pool_size) {
    /* Check if the pool is already initialized */
    if((*node_pool) != NULL) {
        return 0;
    }

    Node *last_node = NULL;
    int node;
    /* For i = 1..pool_size, we create the node i */
    for(node = 1; node <= pool_size; node++) {
        Node *current_node = malloc(sizeof(Node));

        /* Check if the node's memory could be allocated */
        if(current_node == NULL) {
            Node *free_ = (*node_pool), *auxiliar = NULL;

            /* We free all the allocated memory */
            while(free_ != NULL) {
                auxiliar = free_;
                free_ = free_->brother;
                free(auxiliar);
            }

            /* Reset the given pointer */
            (*node_pool) = NULL;
            return -1;
        }

        /* Initializing attributes */
        current_node->brother = NULL;
        current_node->father = NULL;
        current_node->left_son = NULL;
        current_node->key = node;

        /* Check if the last node exists */
        if(last_node != NULL) {
            /* If it exists, set its new brother */
            last_node->brother = current_node;
        } else {
            /* If it doesn't, set its first node */
            (*node_pool) = current_node;
        }

        /* Update the last node */
        last_node = current_node;
    }
    return 1;
}


void free_node_pool(Node **node_pool) {
    /* We free its nodes */
    free_node((*node_pool));
    (*node_pool) = NULL;
}


void free_node(Node *node) {
    /* Ignores NULL nodes */
    if(node == NULL) {
        return;
    }

    /* Free its brother */
    free_node(node->brother);

    /* Free its sons */
    free_node(node->left_son);

    /* Finally, free this node */
    free(node);
}

int remove_from_pool(Node **node_pool, int key, Node **node) {
    /* Since there will be AT LEAST one root, we can use (*node_pool) */
    if((*node_pool)->key == key) {
        /* Remove desired node from pool */
        (*node) = (*node_pool);
        (*node_pool) = (*node_pool)->brother;

        /* Clean the node */
        (*node)->brother = NULL;
        return 1;
    }

    Node *auxiliary = (*node_pool);
    /* Search on the rest of the pool trought its ancestor */
    while(auxiliary->brother != NULL) {
        /* Check for the desired node */
        if(auxiliary->brother->key == key) {
            /* Remove the desired node */
            (*node) = auxiliary->brother;
            auxiliary->brother = (*node)->brother;

            /* Clean the node */
            (*node)->brother = NULL;
            return 1;
        }

        auxiliary = auxiliary->brother;
    }

    return 0;
}


int search_node(Node *node_pool, int key, Node **node) {
    if(node_pool == NULL) {
        /* Couldn't find it on this node */
        return 0;
    } else if(node_pool->key == key) {
        /* Replace given pointer */
        (*node) = node_pool;
        return 1;
    } else {
        /* Search on brothers and sons */
        return search_node(node_pool->brother, key, node) ||
                search_node(node_pool->left_son, key, node);
    }
}


void link(Node *old_root, Node *father) {
    /* Set the father */
    old_root->father = father;

    /* Continue the list of brothers */
    old_root->brother = father->left_son;
    /* Add old_root to father as son */
    father->left_son = old_root;
}


void cut(Node **node_pool, Node *son) {
    Node *father = son->father;

    /* Check if the first son is the son we want to remove */
    if(father->left_son == son) {
        /* We remove his occurrance on the father */
        father->left_son = father->left_son->brother;
    } else {
        /* Since he isn't the first son, let's search through the ancestor */
        Node *ancestor = father->left_son;
        while(ancestor->brother != NULL) {
            /* Check for the desired son */
            if(ancestor->brother == son) {
                ancestor->brother = son->brother;
                break;
            }

            /* Search through all brothers */
            ancestor = ancestor->brother;
        }
    }

    /* We remove his father and put him on the node_pool */
    son->father = NULL;
    son->brother = (*node_pool);
    (*node_pool) = son;
}


int lca(Node *a, Node *b, Node **lca_) {
    Node *auxiliary_a = a, *auxiliary_b = b;

    /* Keep changing a's father and b's father until match */
    while(auxiliary_b != auxiliary_a) {
        if(auxiliary_b->father == NULL) {
            auxiliary_a = auxiliary_a->father;
            auxiliary_b = b;

            /* Stop when there's no more a's father */
            if(auxiliary_a == NULL) {
                return 0;
            }
        } else {
            auxiliary_b = auxiliary_b->father;
        }
    }

    (*lca_) = auxiliary_a;
    return 1;
}
