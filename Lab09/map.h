#ifndef MAP_H
#define MAP_H


struct Node {
    /** Node's value */
    int value;
    /** Node's key */
    char key[250 + 1];
};

struct Map {
    /** Keys to be mapped */
    struct Node *nodes;
    /** Vector length */
    int length;
    /** Map size */
    int size;
};

typedef struct Map Map;
typedef struct Node Node;

typedef unsigned int uint;


/**
* Attempts to initialize map structure.
*
* Returns   -1  if couldn't allocate memory for the map,
*            0  if the map already exists,
*            1  if successfully initialized the map.
*/
int initialize_map(Map **map, int vector_length);

/**
* Inserts key on the map using string.
*
* Returns   -2  if map doesn't exists,
*           -1  if couldn't find a valid position,
*            0  if the key already exists,
*            1  if successfully inserted key.
*/
int insert(Map *map, char *key, uint value);

/**
* Retrieves value on the map and returns it on a pointer.
*
* Returns   -1  if map doesn't exists,
*            0  if couldn't find the given key,
*            1  if successfully found the key.
*/
int retrieve(Map *map, char *key, uint *retrieved_value);

/**
* Remove the node from the heap given its key.
*
* Returns   -1  if the map doesn't exists,
*            0  if couldn't find the given key,
*            1  if successfully removed the key.
*/
int remove_node(Map *map, char *key);

/**
* Free the memory allocated for the map.
*/
void free_map(Map **map);


#endif /* MAP_H */
