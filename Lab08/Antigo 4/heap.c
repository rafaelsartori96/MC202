/*
* Fiz algumas versões para este lab. O que me incomodou foi o fato do programa
* executar com n * log(n) e não passar no quarto teste nas versões em que eu
* verificava por erros importantes de execução (como se o ponteiro recebido da
* alocação era NULL ou não).
*/
#include <stdio.h>
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

#define node_p(heap, index) (&(heap->nodes[index]))


int initialize_heap(Heap **heap, int maximum_length) {
    /* Attempt to allocate memory for the heap */
    *heap = malloc(sizeof(Heap));

    /* Initialize the vectors */
    (*heap)->nodes = malloc(maximum_length * sizeof(Node));
    (*heap)->positions = malloc(maximum_length * sizeof(int));

    /* Initialize its attributes */
    (*heap)->size = 0;
    int key;
    for(key = 0; key < maximum_length; key++) {
        *((*heap)->positions + key) = EMPTY;
    }

    return 1;
}


int insert(Heap *heap, int key, int cost) {
    /* Check if the node already exists */
    if(*(heap->positions + key) != EMPTY) {
        return 0;
    }

    /* Allocate memory for the node */
    Node *new_node = node_p(heap, heap->size);
    // Node *new_node = malloc(sizeof(Node));

    /* Initialize its attributes */
    new_node->key = key;
    new_node->cost = cost;

    /* Insert the node */
    int node_position = (heap->size)++;
    // *(heap->nodes + node_position) = new_node;
    *(heap->positions + key) = node_position;

    /* Maintain minimum heap property */
    maintain_heap_upwards(heap, node_position);

    return 1;
}


int remove_minimum(Heap *heap, int *removed_key, int *removed_cost) {
    /* Check if the heap is not empty */
    if(heap->size == 0) {
        return 0;
    }

    Node *minimum_node = node_p(heap, 0);
    // Node *minimum_node = *(heap->nodes);

    /* Remove minimum node from the positions vector */
    *(heap->positions + minimum_node->key) = EMPTY;

    /* Decrease heap's size and check if there is another node on the heap */
    if(--(heap->size) > 0) {
        Node *last_node = node_p(heap, heap->size);
        // int last_node_index = heap->size;
        // Node *last_node = *(heap->nodes + last_node_index);

        /* Replace the node with the last node on the heap vector */
        *(heap->nodes) = *last_node;
        // *(heap->nodes + last_node_index) = NULL;

        /* Move the last node on the positions vector */
        *(heap->positions + last_node->key) = 0;
    }

    /* Replace given pointers */
    *removed_key = minimum_node->key;
    *removed_cost = minimum_node->cost;

    /* Finally, free the allocated memory for the node */
    // free(minimum_node);

    /* Maintain the minimum heap property downwards (since the last node
    * can be brought to the leaf again) */
    maintain_heap_downwards(heap, 0);

    return 1;
}


int decrease_cost(Heap *heap, int key, int new_cost) {
    /* Search for the node */
    int node_index = *(heap->positions + key);
    Node *node = node_p(heap, node_index);
    // Node *node = *(heap->nodes + node_index);

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
    // int i;
    // for(i = 0; i < (*heap)->size; i++) {
    //     free(*((*heap)->nodes + i));
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

    Node    *parent =   node_p(heap, parent_index);
    Node    *node =     node_p(heap, node_index);
    // Node    *parent =   *(heap->nodes + parent_index);
    // Node    *node =     *(heap->nodes + node_index);

    /* Check if the parent has a lower cost than current key */
    if(node->cost >= parent->cost) {
        return;
    }

    /* Change place with the parent on the positions vector */
    *(heap->positions + node->key) =    parent_index;
    *(heap->positions + parent->key) =  node_index;

    /* Change place with the parent on the heap vector */
    *(heap->nodes + parent_index) = *node;
    *(heap->nodes + node_index) =   *parent;

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
        minimum_son = node_p(heap, left_son_index);
        // minimum_son = *(heap->nodes + left_son_index);

        int right_son_index = right_node(node_index);

        /* Check if the right son exists */
        if(right_son_index < heap->size) {
            Node *right_son = node_p(heap, right_son_index);
            // Node *right_son = *(heap->nodes + right_son_index);

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
    Node *current_node = node_p(heap, node_index);
    // Node *current_node = *(heap->nodes + node_index);

    /* Check if we don't need to move the current node. */
    if(current_node->cost <= minimum_son->cost) {
        return;
    }

    /* Shift on the positions vector */
    *(heap->positions + minimum_son->key) =  node_index;
    *(heap->positions + current_node->key) = minimum_son_index;

    /* Shift on the heap */
    *(heap->nodes + minimum_son_index) =    *current_node;
    *(heap->nodes + node_index) =           *minimum_son;

    /* Maintain the heap for the changed son */
    maintain_heap_downwards(heap, minimum_son_index);
}
