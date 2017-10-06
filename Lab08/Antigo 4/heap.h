#ifndef HEAP_H
#define HEAP_H


struct Node {
    /** Node's identifier */
    int key;
    /** Node's cost to the heap */
    int cost;
};

struct Heap {
    /** Heap vector, a vector of pointers to Node */
    struct Node *nodes;
    /** Auxiliary vector, helping us to find the index of the node given key */
    int *positions;
    /** Heap size */
    int size;
};

typedef struct Node Node;
typedef struct Heap Heap;


/**
* Attempts to initialize the heap struct
*
* Returns   1   if successfully allocated memory for the heap.
*/
int initialize_heap(Heap **heap, int maximum_length);

/**
* Attempts to insert the pair (key, cost) on the heap.
*
* Returns   0   if the node already exists,
*           1   if successfully inserted node.
*/
int insert(Heap *heap, int key, int cost);

/**
* Attempts to remove the lowest cost pair of the heap, while maintaing its
* minimum heap property.
*
* Returns   0   if the heap is empty,
*           1   if the minimum node was successfully removed.
*/
int remove_minimum(Heap *heap, int *removed_key, int *removed_cost);

/**
* Attempts to change the cost of a node.
*
* Returns   0   if old cost is less or equal than current cost,
*           1   if successfully changed node's cost.
*/
int decrease_cost(Heap *heap, int key, int new_cost);

/**
* Free up the memory allocated to the heap.
*/
void free_heap(Heap **heap);


#endif /* HEAP_H */
