#include <stdlib.h>
#include <limits.h>
#include "vector.h"


/**
* Attempts to access the vector on its inside, resizing if needed.
*
* Returns   NULL    if couldn't access position.
*/
int     *get_           (Vector *vector, int position);

/**
* Attempts to resize the vector to a new length, that must be greater than the
* array size.
*
* Returns   -2  if given vector is NULL,
*           -1  if couldn't allocate memory for new vector,
*            0  if new_length is invalid,
*            1  if sucessfully changed vector's length and copied its items.
*/
int     resize_vector   (Vector *vector, int new_length);

/**
* Calculates the minimum of the 2 integers, a and b.
*
* Returns   a   if a <= b,
*           b   if b < a.
*/
int min(int a, int b);

/**
* Calculates the maximum of the 2 integers, a and b.
*
* Returns   a   if a >= b,
*           b   if b > a.
*/
int max(int a, int b);


int initialize_vector(Vector **vector) {
    return initialize_vector_(vector, 8);
}


int initialize_vector_(Vector **vector, int initial_length) {
    /* Returns if vector already exists */
    if((*vector) != NULL) {
        return 0;
    }

    /* Atempts to create vector */
    *vector = malloc(sizeof(Vector));
    /* Checks for allocation */
    if((*vector) == NULL) {
        return -1;
    }

    /* Attempts to create vector's array */
    (*vector)->array = malloc(initial_length * sizeof(int));
    /* Check for allocation */
    if((*vector)->array == NULL) {
        /* Free resources */
        free(*vector);
        (*vector) = NULL;
        return -1;
    }

    int i;
    for(i = 0; i < initial_length; i++) {
        (*vector)->array = INT_MIN;
    }

    /* Initialize its attributes */
    (*vector)->length = initial_length;
    return 1;
}


int get(Vector *vector, int position) {
    return *get_(vector, position);
}


void set(Vector *vector, int position, int set_value) {
    int *position_ = get_(vector, position);
    /* Attempts to access the vector on given position */
    if(position_ == NULL) {
        return 0;
    }

    *position_ = set_value;
    return 1;
}


void reset(Vector *vector, int position, int set_value) {
    return set(vector, position, INT_MIN);
}


void free_vector(Vector **vector) {
    /* Check if the vector exists */
    if((*vector) == NULL) {
        return;
    }

    /* Clear its memory */
    free((*vector)->array);
    free(*vector);
    /* Update its pointer */
    *vector = NULL;
}


int resize_vector(Vector *vector, int new_length) {
    /* Check if there's a vector */
    if(vector == NULL) {
        return -2;
    }

    /* Check if we can decrease the vector */
    if(vector->size > new_length) {
        return 0;
    }

    /* Return success on useless resizes */
    if(new_length == vector->length) {
        return 1;
    }

    /* Attempts to create new array */
    int *new_array = malloc(new_length * sizeof(int));
    /* Check for allocation */
    if(new_array == NULL) {
        return -1;
    }

    int i;
    for(i = 0; i < vector->size; i++) {
        /* Populate new array on the right order */
        *(new_array + i) = *get_(vector, i);
    }

    /* Update vector attributes */
    free(vector->array);
    vector->array = new_array;
    vector->length = new_length;
    return 1;
}


int *get_(Vector *vector, int position) {
    /* Check if given position is accessible on the current vector we have */
    if(
        position >= vector->length &&
        !resize_vector(vector, max(position * 2, vector->length * 2))
    ) {
        return NULL;
    }

    /* Finally, return the address */
    return vector->array + position;
}


int min(int a, int b) {
    return a <= b ? a : b;
}


int max(int a, int b) {
    return a >= b ? a : b;
}
