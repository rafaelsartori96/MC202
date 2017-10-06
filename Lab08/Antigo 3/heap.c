#include <stdlib.h>
#include "heap.h"


#define EMPTY -1


/**
* Attempts to move the node upwards if possible, maintaining the minimum heap
* property. This should be used on nodes that are near the leafs (all parent
* nodes must already follow the minimum heap property).
*/
void maintain_heap_upwards(Heap *heap, int node_index);

/**
* Attempts to move the node downwards if possible, maintaining the minimum heap
* property. This should be used on nodes that are near the root (all son nodes
* must already follow the minimum heap property).
*/
void maintain_heap_downwards(Heap *heap, int node_index);

/**
* Attempts to find node's key from node's index, so we don't need extra memory.
*
* Returns { k / heap[index] has the key k }
*/
#ifdef MEMORY_FRIENDLY
int key_from_index(Heap *heap, int index);
#endif

/**
* Translates the given key to a vector position to be used on the heap.
*
* Returns key.
*/
// int key_index(int key) { return key; }

/**
* Translates the given node index to a vector position that corresponds to the
* node's parent.
*
* Returns floor((node_index - 1) / 2).
*/
// int parent_node(int node_index) { return ((node_index - 1) >> 1); }

/**
* Translates the given node index to a vector position that corresponds to the
* node's left son.
*
* Returns ((2 * node) + 1).
*/
// int left_node(int node_index) { return ((node_index << 1) + 1); }

/**
* Translates the given node index to a vector position that corresponds to the
* node's right son.
*
* Returns (2 * (node + 1)).
*/
// int right_node(int node_index) { return ((node_index + 1) << 1); }

#define key_index(key) (key)
#define parent_node(node_index) ((node_index - 1) >> 1)
#define left_node(node_index) ((node_index << 1) + 1)
#define right_node(node_index) ((node_index + 1) << 1)


int initialize_heap(Heap **heap, int maximum_length) {
    /* Check if the heap already exists */
    if((*heap) != NULL) {
        return 0;
    }

    /* Attempt to allocate memory for the heap */
    *heap = malloc(sizeof(Heap));
    if((*heap) == NULL) {
        return -1;
    }

    /* Initialize the vectors */
    (*heap)->nodes = calloc(maximum_length, sizeof(Node *));
    if((*heap)->nodes == NULL) {
        free(*heap);
        *heap = NULL;
        return -1;
    }

    (*heap)->positions = malloc(maximum_length * sizeof(int));
    if((*heap)->positions == NULL) {
        free((*heap)->nodes);
        free(*heap);
        *heap = NULL;
        return -1;
    }

    /* Initialize its attributes */
#ifdef MEMORY_FRIENDLY
    (*heap)->length = maximum_length;
#endif
    (*heap)->size = 0;
    int key;
    for(key = 0; key < maximum_length; key++) {
        *((*heap)->positions + key_index(key)) = EMPTY;
    }

    return 1;
}


int insert(Heap *heap, int key, int cost) {
    /* Check if the structure exists */
    // if(heap == NULL) {
    //     return -2;
    // }

    /* Check if the node already exists */
    if(*(heap->positions + key_index(key)) != EMPTY) {
        return 0;
    }

    /* Allocate memory for the node */
    Node *new_node = malloc(sizeof(Node));
    if(new_node == NULL) {
        return -1;
    }

    /* Initialize its attributes */
#ifndef MEMORY_FRIENDLY
    new_node->key = key;
#endif
    new_node->cost = cost;

    /* Insert the node */
    int node_position = heap->size;
    (heap->size)++;
    *(heap->nodes + node_position) = new_node;
    *(heap->positions + key_index(key)) = node_position;

    /* Maintain minimum heap property */
    maintain_heap_upwards(heap, node_position);

    return 1;
}


int remove_minimum(Heap *heap, int *removed_key, int *removed_cost) {
    /* Check if the heap exists */
    // if(heap == NULL) {
    //     return -1;
    // }

    /* Check if the heap is not empty */
    if(heap->size == 0) {
        return 0;
    }

    Node *minimum_node = *(heap->nodes + 0);

    /* Remove minimum node from the positions vector */
#ifdef MEMORY_FRIENDLY
    int minimum_node_key = key_from_index(heap, 0);
    *(heap->positions + minimum_node_key) = EMPTY;
#else
    *(heap->positions + key_index(minimum_node->key)) = EMPTY;
#endif

    /* Decrease heap's size */
    (heap->size)--;

    /* Check if there is another node on the heap */
    if(heap->size > 0) {
        int last_node_index = heap->size;
        Node *last_node = *(heap->nodes + last_node_index);

        /* Replace the node with the last node on the heap vector */
        *(heap->nodes + 0) = last_node;
        *(heap->nodes + last_node_index) = NULL;

        /* Move the last node on the positions vector */
#ifdef MEMORY_FRIENDLY
        int last_node_key = key_from_index(heap, last_node_index);
        *(heap->positions + last_node_key) = 0;
#else
        *(heap->positions + key_index(last_node->key)) = 0;
#endif
    }

    /* Replace given pointers */
#ifdef MEMORY_FRIENDLY
    *removed_key = minimum_node_key;
#else
    *removed_key = minimum_node->key;
#endif
    *removed_cost = minimum_node->cost;

    /* Finally, free the allocated memory for the node */
    free(minimum_node);

    /* Maintain the minimum heap property downwards (since the last node
    * can be brought to the leaf again) */
    maintain_heap_downwards(heap, 0);

    return 1;
}


int decrease_cost(Heap *heap, int key, int new_cost) {
    /* Check if the heap exists */
    // if(heap == NULL) {
    //     return -1;
    // }

    /* Search for the node */
    int node_index = *(heap->positions + key_index(key));
    Node *node = *(heap->nodes + node_index);

    /* Check if the new cost is lower than old cost */
    if(node->cost <= new_cost) {
        return 0;
    }

    /* Change its cost */
    node->cost = new_cost;

    /* Maintain minimum heap property upwards (since new_cost must be lower than
    * current cost) */
    maintain_heap_upwards(heap, node_index);

    return 1;
}


void free_heap(Heap **heap) {
    /* Check if the heap exists */
    // if((*heap) == NULL) {
    //     return;
    // }

    /* Free its memory */
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

    Node    *parent =   *(heap->nodes + parent_index);
    Node    *node =     *(heap->nodes + node_index);

    /* Check if the parent has a lower cost than current key */
    if(node->cost >= parent->cost) {
        return;
    }

    /* Change place with the parent on the positions vector */
#ifdef MEMORY_FRIENDLY
    int node_key =      key_from_index(heap, node_index);
    int parent_key =    key_from_index(heap, parent_index);
    *(heap->positions + node_key) =    parent_index;
    *(heap->positions + parent_key) =  node_index;
#else
    *(heap->positions + key_index(node->key)) =    parent_index;
    *(heap->positions + key_index(parent->key)) =  node_index;
#endif

    /* Change place with the parent on the heap vector */
    *(heap->nodes + parent_index) = node;
    *(heap->nodes + node_index) =   parent;

    /* Call for the parent index now */
    maintain_heap_upwards(heap, parent_index);
}


void maintain_heap_downwards(Heap *heap, int node_index) {
    int minimum_son_index = -1;
    Node *minimum_son = NULL;

    {
        int left_son_index = left_node(node_index);

        /* Check if there is no son */
        if(left_son_index >= heap->size) {
            return;
        }

        /* Make the left son the minimum son since we don't know if a right son
        * exists. */
        minimum_son_index = left_son_index;
        minimum_son = *(heap->nodes + left_son_index);

        int right_son_index = right_node(node_index);

        /* Check if the right son exists */
        if(right_son_index < heap->size) {
            Node *right_son = *(heap->nodes + right_son_index);

            /* Check if the right son is the minimum cost one.
            *
            * Note that minimum_son here is the left son. */
            if(minimum_son->cost > right_son->cost) {
                minimum_son_index = right_son_index;
                minimum_son = right_son;
            }
        }
    }

    /* Since we're here, we found a lowest son to attempt to shift current node
    * with. */
    Node *current_node = *(heap->nodes + node_index);

    /* Check if we don't need to move the current node. */
    if(current_node->cost <= minimum_son->cost) {
        return;
    }

    /* Shift on the positions vector */
#ifdef MEMORY_FRIENDLY
    int minimum_son_key = key_from_index(heap, minimum_son_index);
    int current_node_key = key_from_index(heap, node_index);
    *(heap->positions + minimum_son_key) =  node_index;
    *(heap->positions + current_node_key) = minimum_son_index;
#else
    *(heap->positions + key_index(minimum_son->key)) =  node_index;
    *(heap->positions + key_index(current_node->key)) = minimum_son_index;
#endif

    /* Shift on the heap */
    *(heap->nodes + minimum_son_index) =    current_node;
    *(heap->nodes + node_index) =           minimum_son;

    /* Maintain the heap for the changed son */
    maintain_heap_downwards(heap, minimum_son_index);
}


#ifdef MEMORY_FRIENDLY
int key_from_index(Heap *heap, int index) {
    int i;
    for(i = 0; i < heap->length; i++) {
        if(*(heap->positions + i) == index) {
            return i;
        }
    }
    return EMPTY;
}
#endif
