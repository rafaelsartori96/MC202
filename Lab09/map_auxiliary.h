#ifndef MAP_AUXILIARY_H
#define MAP_AUXILIARY_H
#include "map.h"


/**
* Function that calculates the first hash of the string.
*/
ulong _first_hash(char *string);

/**
* Function that calculates the second hash of the string.
*/
ulong _second_hash(char *string);

/**
* Function that calculates the hash position for the current map using the
* division method.
*/
int _hash_position(Map *map, ulong hash_1, ulong hash_2, int attempt);


#endif
