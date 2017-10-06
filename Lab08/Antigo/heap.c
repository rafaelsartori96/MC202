#include <stdlib.h>
#include <limits.h>
#include "heap.h"


/**
* This function will maintain the minimum heap property by bringing the lowest
* node from index's sons upward.
*/
void maintain_heap(Heap *heap, int key, int index);

/**
* Check for the key given its index on the vector.
*
* Returns   INT_MIN     if couldn't find anything.
*/
int get_key(Heap *heap, int index);

/**
* Calculate the position of the parent of the given node's position.
*
* Returns   ((index - 1) >> 1)  or  floor((index - 1) / 2).
*/
int parent(int index);

/**
* Calculate the position of the left son of the given node's position.
*
* Returns   ((index << 1) + 1)  or  (2 * index + 1)
*/
int left(int index);

/**
* Calculate the position of the right son of the given node's position.
*
* Returns   ((index + 1) << 1)  or  (2 * index + 2)
*/
int right(int index);


int initialize_heap(Heap **heap) {
    /* Check if there is a structure on the pointer */
    if((*heap) != NULL) {
        return 0;
    }

    /* Attempts to create the heap structure */
    *heap = malloc(sizeof(Heap));
    if((*heap) == NULL) {
        return -1;
    }

    /* Attempt to initialize heap vector */
    if(!initialize_vector(&(*heap)->heap)) {
        free(*heap);
        return -1;
    }

    /* Attempt to initialize indicies vector */
    if(!initialize_vector(&(*heap)->indicies)) {
        free_vector(&(*heap)->heap);
        free(*heap);
        return -1;
    }

    /* Initialize heap's attributes */
    (*heap)->last_index = 0;
    return 1;
}


int insert_pair(Heap *heap, int key, int cost) {
    /* Attempt to insert the pair on heap and indicies */
    set(heap->heap, ++(heap->last_index), cost);
    set(heap->indicies, key, heap->last_index);

    maintain_heap(heap, key, heap->last_index);
    return 1;
}


int remove_pair(Heap *heap, int key) {
    int index = get(heap->indicies, key);

    /* Replace it with the */
}


int decrease_cost(Heap *heap, int key, int new_cost) {

}


void free_heap(Heap **heap) {
    /* Check if the heap has already been freed */
    if((*heap) == NULL) {
        return;
    }

    free_vector(&(*heap)->heap);
    free_vector(&(*heap)->indicies);
    free(*heap);
    *heap = NULL;
}


void maintain_heap(Heap *heap, int key, int index) {
    /* Check if current index has a parent */
    if(index > 0) {
        return;
    }

    /* Check if the parent cost is lower than the current index */
    int parent_cost = get(heap->heap, parent(index)),
        current_cost = get(heap->heap, index);
    if(parent_cost > current_cost) {
        int parent_key = get_key(heap, parent(index));

        /* Parent will receive son's attributes */
        set(heap->heap, index, parent_cost);
        set(heap->indicies, parent_key, index);

        /* Son will receive parent's attributes */
        set(heap->heap, parent(index), current_cost);
        set(heap->indicies, key, parent(index));

        /* Continue moving current index if necessary */
        maintain_heap(heap, key, parent(index));
    }
}


int get_key(Heap *heap, int index) {
    int i;
    for(i = 0; i < heap->indicies->length; i++) {
        /* Search for the index */
        if(get(heap->indicies, i) == index) {
            return i;
        }
    }

    return INT_MIN;
}


int parent(int index) {
    return ((index - 1) >> 1);
}


int left(int index) {
    return ((index << 1) + 1);
}


int right(int index) {
    return ((index + 1) << 1);
}
