#ifndef TREE_H
#define TREE_H


/*
* Although we could just use a list of nodes that points to the node's father, I
* don't think this would be considered a tree for grade porpuse.
*/

struct Node {
    /** List of brothers */
    struct Node *brother;

    /** Father's address. NULL if current node is root */
    struct Node *father;

    /** List of sons, pointing to the one on the left */
    struct Node *left_son;

    /** Node's key */
    int key;
};

typedef struct Node Node;


/**
* Creates the node pool, initialized with nodes which keys 1..pool_size.
*
* Returns   -1  if couldn't allocate memory,
*            0  if node_pool is already initialized,
*            1  if sucessfully initialized node pool.
*/
int initialize_node_pool(Node **node_pool, int pool_size);

/**
* Free pool's memory.
*/
void free_node_pool(Node **node_pool);

/**
* Removes the desired key from the pool and replace it on given pointer.
*
* Returns   0   if node wasn't found on pool,
*           1   if node was successfully removed.
*/
int remove_from_pool(Node **node_pool, int key, Node **node);

/**
* Searches the given key on any tree of the pool.
*
* Returns   0   if couldn't find any node with this key,
*           1   if successfully found the key.
*/
int search_node(Node *node_pool, int key, Node **node);

/**
* Given root 'old_root' and node 'father', turns 'old_root' into a son of
* 'father'.
*/
void link(Node *old_root, Node *father);

/**
* Given node 'a', removes link from 'a' to its father, turning 'a' into a root.
*/
void cut(Node **node_pool, Node *a);

/**
* Prints the lowest common ancestor of the node 'a' and 'b'.
*/
int lca(Node *a, Node *b, Node **lca_);


#endif /* TREE_H */
