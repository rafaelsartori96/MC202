#include <stdlib.h>
#include "heap.h"


void maintain_min_heap(Heap *heap, int index);

int parent(int index);

int left(int index);

int right(int index);


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

    /* Attempt to allocate memory for the heap array of pointers */
    (*heap)->heap_array     = calloc(maximum_length, sizeof(Node *));
    /* Check if successfully allocated memory */
    if((*heap)->heap_array == NULL) {
        free(*heap);
        *heap = NULL;
        return -1;
    }

    /* Attempt to allocate memory for the <key, node> array */
    (*heap)->key_node_pos_array = malloc((maximum_length + 1) * sizeof(int));
    /* Check if successfully allocated memory */
    if((*heap)->key_node_pos_array == NULL) {
        free((*heap)->heap_array);
        free(*heap);
        *heap = NULL;
        return -1;
    } else {
        int i;
        for(i = 0; i < (maximum_length + 1); i++) {
            *((*heap)->key_node_pos_array + i) = -1;
        }
    }

    /* Initialize its attributes */
    (*heap)->length = maximum_length;
    (*heap)->last_position = 0;

    return 1;
}


int insert_pair(Heap *heap, int key, int cost) {
    /* Check if the heap exists */
    if(heap == NULL) {
        return -1;
    }

    /* Check if the item already exists */
    if(*(heap->key_node_pos_array + key) >= 0) {
        return 0;
    }

    /* Attempt to allocate memory for the node */
    Node *new_node = malloc(sizeof(Node));
    if(new_node == NULL) {
        return -1;
    }

    /* Initialize its attributes */
    new_node->cost = cost;
    new_node->key = key;

    /* Add it to the end of the heap_array */
    *(heap->heap_array + heap->last_position) = new_node;
    *(heap->key_node_pos_array + key) = heap->last_position;

    /* Maintain minimum-heap property */
    maintain_min_heap(heap, heap->last_position);

    /* Increase last position for the next item */
    (heap->last_position)++;

    return 1;
}


int remove_minimum(Heap *heap, int *removed_key, int *removed_cost) {
    /* Check if the heap exists */
    if(heap == NULL) {
        return -1;
    }

    /* By definition of minimum heap, the minimum is on the root */
    int index = 0;

    /* Check if the heap is empty */
    if(index == heap->last_position) {
        return 0;
    }

    Node *auxiliary = *(heap->heap_array + index);

    /* Move the last index from the heap here */
    *(heap->heap_array + index) = *(heap->heap_array + heap->last_position);
    heap->last_position--;
    /* Update moved node's position */
    *(heap->key_node_pos_array + (*(heap->heap_array + index))->key) = index;
    /* Update given pointers */
    *removed_key = auxiliary->key;
    *removed_cost = auxiliary->cost;
    /* Free auxiliary's memory */
    *(heap->key_node_pos_array + index) = -1;
    free(auxiliary);

    /* Finally, maintain heap property */
    maintain_min_heap(heap, index);

    return 1;
}


void decrease_cost(Heap *heap, int key, int new_cost) {
    int index = *(heap->key_node_pos_array + key);
    /* Update its cost */
    (*(heap->heap_array + index))->cost = new_cost;

    /* Maintain heap property */
    maintain_min_heap(heap, index);
}


void free_heap(Heap **heap) {
    /* Check if the heap exists */
    if((*heap) == NULL) {
        return;
    }

    /* Free its memory */
    free((*heap)->heap_array);
    free((*heap)->key_node_pos_array);
    free(*heap);
    *heap = NULL;
}


void maintain_min_heap(Heap *heap, int index) {
    Node *current_node = *(heap->heap_array + index);

    Node *minimum_son = NULL;
    int minimum_son_index = -1;
    /* Check for the left son */
    if(left(index) <= heap->last_position) {
        minimum_son = *(heap->heap_array + left(index));
        minimum_son_index = left(index);
    }
    /* Check for the right son */
    if(right(index) <= heap->last_position) {
        Node *right_son = *(heap->heap_array + right(index));
        /* Since this IS a heap, if there is a right son, there must exist a
        * left one */
        if(right_son->cost < minimum_son->cost) {
            minimum_son = right_son;
            minimum_son_index = right(index);
        }
    }

    /* Check if we should move current index downward */
    if(minimum_son != NULL && minimum_son->cost < current_node->cost) {
        /* Shift minimum_son <-> current_node */
        *(heap->heap_array + minimum_son_index) = current_node;
        *(heap->heap_array + index) = minimum_son;
        /* Shift on the key_node position array */
        *(heap->key_node_pos_array + current_node->key) = minimum_son_index;
        *(heap->key_node_pos_array + minimum_son->key) = index;

        /* Maintain heap for the downward tree */
        maintain_min_heap(heap, minimum_son_index);
    } else if(index > 0) {
        int parent_index = parent(index);
        Node *parent_ = *(heap->heap_array + parent_index);
        /* Check if we should move the current index upward */
        if(parent_->cost < current_node->cost) {
            /* Shift parent_ <-> current_node */
            *(heap->heap_array + parent_index) = current_node;
            *(heap->heap_array + index) = parent_;
            /* Shift on the key_node position array */
            *(heap->key_node_pos_array + current_node->key) = parent_index;
            *(heap->key_node_pos_array + parent_->key) = index;

            /* Maintain heap for the upward tree */
            maintain_min_heap(heap, parent_index);
        }
    }
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
