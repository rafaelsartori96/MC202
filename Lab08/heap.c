#include <stdlib.h>
#include "heap.h"


/** Code used for empty slots on the heap's position vector */
#define EMPTY -1


/**
* Translates the given node index to a vector position that corresponds to the
* node's parent.
*
* Returns floor((node_index - 1) / 2).
*/
#define parent_node(node_index) ((node_index - 1) >> 1)

/**
* Translates the given node index to a vector position that corresponds to the
* node's left son.
*
* Returns ((2 * node) + 1).
*/
#define left_node(node_index) ((node_index << 1) + 1)

/**
* Translates the given node index to a vector position that corresponds to the
* node's right son.
*
* Returns (2 * (node + 1)).
*/
#define right_node(node_index) ((node_index + 1) << 1)


/**
* Attempts to move the node upwards if possible, maintaining the minimum heap
* property. This should be used on nodes that are goint to the root (all parent
* nodes must already follow the minimum heap property).
*/
void maintain_heap_upwards(Heap *heap, int node_index);

/**
* Attempts to move the node downwards if possible, maintaining the minimum heap
* property. This should be used on nodes that are goint to the leaves (all son
* nodes must already follow the minimum heap property).
*/
void maintain_heap_downwards(Heap *heap, int node_index);


int initialize_heap(Heap **heap, int maximum_length) {
    /* Check if the heap exists */
    if((*heap) != NULL) {
        return -1;
    }

    /* Attempt to allocate memory for the heap */
    *heap = malloc(sizeof(Heap));
    if((*heap) == NULL) {
        return 0;
    }

    /* Attempts to allocate memory for the nodes */
    (*heap)->nodes = malloc(maximum_length * sizeof(Node));
    if((*heap)->nodes == NULL) {
        free(*heap);
        *heap = NULL;
        return 0;
    }

    /* Attempts to allocate memory for the vector of positions */
    (*heap)->positions = malloc(maximum_length * sizeof(int));
    if((*heap)->positions == NULL) {
        free((*heap)->nodes);
        free(*heap);
        *heap = NULL;
        return 0;
    }

    /* Initialize its attributes */
    (*heap)->size = 0;
    int i;
    for(i = 0; i < maximum_length; i++) {
        *((*heap)->positions + i) = EMPTY;
    }

    return 1;
}


int insert(Heap *heap, int key, int cost) {
    /* Check if the heap exists */
    if(heap == NULL) {
        return -1;
    }

    /* Check if the node exists */
    if(*(heap->positions + key) != EMPTY) {
        return 0;
    }

    int node_index = heap->size;

    /* Initialize the node on the heap */
    Node *node = (heap->nodes + node_index);
    node->key = key;
    node->cost = cost;

    /* Insert the key on the position vector */
    *(heap->positions + key) = node_index;

    /* Increase the heap size */
    (heap->size)++;

    /* Maintain the heap property. This operation may only move the node
    * upwards, since it is a leave of the binary tree. */
    maintain_heap_upwards(heap, node_index);

    return 1;
}


int remove_minimum(Heap *heap, int *removed_key, int *removed_cost) {
    /* Check if the heap exists */
    if(heap == NULL) {
        return -1;
    }

    /* Check if the heap is not empty */
    if(heap->size == 0) {
        return 0;
    }

    /* Get the minimum node */
    Node *minimum_node = (heap->nodes);

    /* Update given pointers */
    *removed_key = minimum_node->key;
    *removed_cost = minimum_node->cost;

    /* Clear the position for the key */
    *(heap->positions + minimum_node->key) = EMPTY;

    /* Decrease heap's size */
    (heap->size)--;

    /* Check if there is a son */
    if(heap->size > 0) {
        Node *last_node = (heap->nodes + heap->size);

        /* Replace the current node with the last node */
        minimum_node->cost = last_node->cost;
        minimum_node->key = last_node->key;

        /* Move the last node on the positions vector */
        *(heap->positions + last_node->key) = 0;
    }

    /* Maintain the heap property. Since we moved an item from the bottom to the
    * root of the tree, it may only go downwards. */
    maintain_heap_downwards(heap, 0);

    return 1;
}


int decrease_cost(Heap *heap, int key, int new_cost) {
    /* Check if the heap exists */
    if(heap == NULL) {
        return -1;
    }

    int node_index = *(heap->positions + key);

    /* Check if the node exists */
    if(node_index == EMPTY) {
        return 0;
    }

    Node *node = (heap->nodes + node_index);

    /* Check if new cost is valid */
    if(new_cost > node->cost) {
        return -2;
    }

    /* Update current node's cost */
    node->cost = new_cost;

    /* Since we decreased the cost of the node, it may only go upwards. */
    maintain_heap_upwards(heap, node_index);
    return 1;
}


void free_heap(Heap **heap) {
    /* Check if the heap exists */
    if((*heap) == NULL) {
        return;
    }

    /* Free allocated memory */
    free((*heap)->nodes);
    free((*heap)->positions);
    free(*heap);
    *heap = NULL;
}


void maintain_heap_upwards(Heap *heap, int node_index) {
    /* Check if we're on the root */
    if(node_index == 0) {
        return;
    }

    int parent_index = parent_node(node_index);

    Node    *parent =   (heap->nodes + parent_index);
    Node    *node =     (heap->nodes + node_index);

    /* Check if the parent has a lower cost than current node */
    if(node->cost >= parent->cost) {
        return;
    }

    /* Since the parent has a higher cost, we need to replace it.
    * Move the positions vectors for the shift */
    *(heap->positions + node->key) =    parent_index;
    *(heap->positions + parent->key) =  node_index;

    /* Make a copy of the current node */
    Node copy;
    copy.cost = node->cost;
    copy.key = node->key;

    /* Replace the current node with parent's information */
    node->cost = parent->cost;
    node->key = parent->key;

    /* Replace the parent node with the current node's information */
    parent->cost = copy.cost;
    parent->key = copy.key;

    /* Call for the parent index now */
    maintain_heap_upwards(heap, parent_index);
}


void maintain_heap_downwards(Heap *heap, int node_index) {
    int minimum_son_index = -1;
    Node *minimum_son = NULL;

    {
        int left_son_index = left_node(node_index);

        /* Check if there is a left son.
        * Note that if there isn't a left son, there must not be a right son
        * since this is a heap. */
        if(left_son_index >= heap->size) {
            return;
        }

        Node *left_son = (heap->nodes + left_son_index);

        /* Set the minimum son to the left son */
        minimum_son_index = left_son_index;
        minimum_son = left_son;

        int right_son_index = right_node(node_index);

        /* Check if there is a right son */
        if(right_son_index < heap->size) {
            Node *right_son = (heap->nodes + right_son_index);

            /* Check if the right son has lower cost than the left son */
            if(left_son->cost > right_son->cost) {
                /* Replace the minimum cost son */
                minimum_son_index = right_son_index;
                minimum_son = right_son;
            }
        }
    }

    Node *current_node = (heap->nodes + node_index);

    /* Check if we need to move the current node downwards */
    if(current_node->cost <= minimum_son->cost) {
        return;
    }

    /* Move on the positions vector */
    *(heap->positions + minimum_son->key) =  node_index;
    *(heap->positions + current_node->key) = minimum_son_index;

    /* Make a copy of the current node */
    Node copy;
    copy.cost = current_node->cost;
    copy.key = current_node->key;

    /* Replace the current node */
    current_node->cost = minimum_son->cost;
    current_node->key = minimum_son->key;

    /* Replace the son node */
    minimum_son->cost = copy.cost;
    minimum_son->key = copy.key;

    /* Call for the son node, since it can go to the leaves */
    maintain_heap_downwards(heap, minimum_son_index);
}
