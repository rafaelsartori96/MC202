#ifndef HEAP_H
#define HEAP_H
#include "vector.h"


struct Heap {
    /** Sequential representation of the heap. Will store costs. */
    Vector *heap;
    /** Vector of indexes for each heap node. indicies[key] = index on heap */
    Vector *indicies;
    /** Last used heap index */
    int last_index;
};

typedef struct Heap Heap;


/**
* Attempts to initialize the Heap structure.
*
* Returns   -1  if couldn't allocate memory for the structure,
*            0  if the structure already exists,
*            1  if successfully created heap.
*/
int initialize_heap(Heap **heap);

/**
* Attempts to insert (key, cost) pair at the heap.
*
* Returns   -1  if couldn't insert on the heap,
*            1  if successfully inserted on the item.
*/
int insert_pair(Heap *heap, int key, int cost);

int remove_pair(Heap *heap, int key);

int decrease_cost(Heap *heap, int key, int new_cost);

void free_heap(Heap **heap);


#endif /* HEAP_H */
