#ifndef HEAP_H
#define HEAP_H


struct Node {
    /** Node's cost */
    int cost;
    /** Node's key */
    int key;
};

struct Heap {
    /** Sequential format of a heap as pointers to pointers to node */
    struct Node **heap_array;
    /** Array of nodes' position where the index is the node's key */
    int *key_node_pos_array;
    /** Length of the heap's key_node array and maximum size of the heap */
    int length;
    /** Last used position on the heap_array */
    int last_position;
};

typedef struct Node Node;
typedef struct Heap Heap;


/**
* Attempts to initialize the Heap structure that must not exceed maximum_length.
*
* Returns   -1  if couldn't allocate memory for the structure,
*            0  if the structure already exists,
*            1  if successfully created heap.
*/
int initialize_heap(Heap **heap, int maximum_length);

/**
* Attempts to insert (key, cost) pair at the heap.
*
* Returns   -1  if couldn't insert on the heap,
*            0  if the element already exists,
*            1  if successfully inserted on the item.
*/
int insert_pair(Heap *heap, int key, int cost);

/**
* Attempts to remove the minimum heap and returns its values.
*
* Returns   -1  if the heap doesn't exists,
*            0  if the heap is empty,
*            1  if successfully removed the key.
*/
int remove_minimum(Heap *heap, int *removed_key, int *removed_cost);

/**
* Decreases key's node cost on the heap and move it if necessary.
*/
void decrease_cost(Heap *heap, int key, int new_cost);

/**
* Clear the heap and its allocated memory.
*/
void free_heap(Heap **heap);

#endif /* HEAP_H */
