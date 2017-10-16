#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "map_auxiliary.h"


// #include <stdio.h>
// uint colisoes = 0;

typedef unsigned long ulong;


#define EMPTY -1
#define REMOVED -2


int initialize_map(Map **map, int vector_length) {
    /* Check if the map exists */
    if((*map) != NULL) {
        return 0;
    }

    /* Attempt to allocate memory for the map */
    *map = malloc(sizeof(Map));
    if((*map) == NULL) {
        return -1;
    }

    /* Initialize the map vector */
    (*map)->nodes = malloc(vector_length * sizeof(Node));
    if((*map)->nodes == NULL) {
        free(*map);
        *map = NULL;
        return -1;
    }

    /* Initialize map's attributes */
    (*map)->length = vector_length;
    (*map)->size = 0;
    int i;
    for(i = 0; i < vector_length; i++) {
        ((*map)->nodes + i)->value = EMPTY;
    }

    return 1;
}


int insert(Map *map, char *key, uint value) {
    /* Check if the map exists */
    if(map == NULL) {
        return -2;
    }

    /* Initialize search variables, making it more efficient */
    int attempt = 0;
    ulong hash_1 = _first_hash(key);
    ulong hash_2 = _second_hash(key);

    int first_removed_position = -1;
    int hash_posision;

    /* Calculate hash position until reach an ampty space or find current key */
    while(1) {
        hash_posision = _hash_position(map, hash_1, hash_2, attempt);
        Node *node = (map->nodes + hash_posision);

        if(node->value == EMPTY) {
            /* Since we found an empty position, break the loop */
            break;
        } else if(node->value == REMOVED && first_removed_position < 0) {
            /* Store the first removed position */
            first_removed_position = hash_posision;
        } else if(
            node->value != REMOVED && node->value != EMPTY &&
            strcmp(key, node->key) == 0
        ) {
            /* Returns if we found the key we're inserting */
            return 0;
        } else if(attempt > map->length) {
            /* Check if we found an empty position */
            if(first_removed_position < 0) {
                /* Returns if we made too much attempts */
                return -1;
            } else {
                /* Continues inserting the item if we have an empty position */
                break;
            }
        }

        // colisoes++;
        attempt++;
    }

    /* Now that we're here, we must insert the node. Let's define the position
    * to do it. */
    int inserting_position;
    if(first_removed_position > 0) {
        /* Check if we must replace a removed node */
        inserting_position = first_removed_position;
    } else {
        /* Insert at empty node */
        inserting_position = hash_posision;
    }

    /* Insert the node */
    Node *node = (map->nodes + inserting_position);
    strcpy(node->key, key);
    node->value = value;
    (map->size)++;

    return 1;
}


int retrieve(Map *map, char *key, uint *retrieved_value) {
    /* Check if the map exists */
    if(map == NULL) {
        return -1;
    }

    /* Initialize search variables, making it more efficient */
    int attempt = 0;
    ulong hash_1 = _first_hash(key);
    ulong hash_2 = _second_hash(key);

    int hash_posision;

    /* Calculate hash position until reach the current key */
    while(1) {
        hash_posision = _hash_position(map, hash_1, hash_2, attempt);
        Node *node = (map->nodes + hash_posision);

        if(node->value == EMPTY || attempt > map->length) {
            /* Since we found an empty position, returns not found */
            break;
        } else if(
            node->value != EMPTY && node->value != REMOVED &&
            strcmp(key, node->key) == 0
        ) {
            /* Returns if we found the key we're looking for */
            *retrieved_value = node->value;
            return 1;
        }

        // colisoes++;
        attempt++;
    }

    return 0;
}


int remove_node(Map *map, char *key) {
    /* Check if the map exists */
    if(map == NULL) {
        return -1;
    }

    /* Initialize search variables, making it more efficient */
    int attempt = 0;
    ulong hash_1 = _first_hash(key);
    ulong hash_2 = _second_hash(key);

    int hash_posision;

    /* Calculate hash position until reach the current key */
    while(1) {
        hash_posision = _hash_position(map, hash_1, hash_2, attempt);
        Node *node = (map->nodes + hash_posision);

        if(node->value == EMPTY || attempt > map->length) {
            /* Since we found an empty position, returns not found */
            break;
        } else if(
            node->value != REMOVED && node->value != EMPTY &&
            strcmp(key, node->key) == 0
        ) {
            /* Remove the key if we found it */
            node->value = REMOVED;
            (map->size)--;

            return 1;
        }

        // colisoes++;
        attempt++;
    }

    return 0;
}


void free_map(Map **map) {
    /* Check if the map has already been freed or not initialized */
    if((*map) == NULL) {
        return;
    }

    /* Free its resources */
    free((*map)->nodes);
    free(*map);
    *map = NULL;
    // printf("colisoes = %u\n", colisoes);
}


ulong _first_hash(char *string) {
    ulong hash = 31;
    unsigned char c;
    int i = 0;

    /* For every char on the string... */
    while((c = (unsigned char) *(string + i++)) != '\0') {
        /* Calculate a hash. Let's do it this way:
        * Get the 8-bit unsigned char (0 -> 255) and shift it in a way that even
        * if we add 250 of the worst case shift, we wouldn't overflow the 64-bit
        * hash.
        *
        * char << (i % x) so that 250 * (255 << (i % x)) < 2^64
        * 2^8 * 2^x < 2^64 / 250
        * 2^x < (2^(64 - 8)) / 250
        * x < lg ((2^56) / 250), that is, x < 48.034
        */
        hash = hash + (c << (i % 48));
    }

    return hash;
}


ulong _second_hash(char *string) {
    /* My second hash function failed on the last test even when the vector was
    * too big (then it exceeded time). */
    // ulong hash = 751;
    // unsigned char c;
    // int i = 0;
    //
    // /* For every char on the string... */
    // while((c = (unsigned char) *(string + i++)) != '\0') {
    //     /* Calculate a hash. Let's do it this way:
    //     * Get the 8-bit unsigned char (0 -> 255) and shift it in a way that
    //     * even if we add 250 of the worst case shift, we wouldn't overflow
    //     * the 64-bit hash. */
    //     hash = hash + (c << ((i * 2 + 9) % 41));
    // }
    //
    // return hash;
    ulong hash = 5381;
    unsigned char c;

    while ((c = (unsigned char) *string++))
      hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}


int _hash_position(Map *map, ulong hash_1, ulong hash_2, int attempt) {
    return (hash_1 + attempt * hash_2) % map->length;
}
