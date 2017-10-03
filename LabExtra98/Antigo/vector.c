#include <stdlib.h>
#include <stdio.h>
#include "vector.h"


/**
* Attempts to access the vector on its limits (-1 or vector->size position) or
* on its inside.
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

    /* Initialize its attributes */
    (*vector)->length = initial_length;
    (*vector)->size = 0;
    (*vector)->starting_index = 0;
    return 1;
}


int get(Vector *vector, int position, int *retrieved_value) {
    /* Check vector limits */
    if(position < 0 || position >= vector->size) {
        return 0;
    }

    /* Replaces the value */
    *retrieved_value = *get_(vector, position);
    return 1;
}


int insert_on_start(Vector *vector, int inserted_item) {
    int *position = get_(vector, -1);
    /* Attempts to get the desired position */
    if(position == NULL) {
        return 0;
    }

    /* Insert item on vector */
    *position = inserted_item;
    /* Ajust vector size and starting index */
    vector->starting_index--;
    if(vector->starting_index < 0) {
        vector->starting_index += vector->length;
    }
    vector->size++;
    return 1;
}


int insert_on_end(Vector *vector, int inserted_item) {
    int *position = get_(vector, vector->size);
    /* Attempts to get the desired position */
    if(position == NULL) {
        return 0;
    }

    /* Insert item on vector */
    *position = inserted_item;
    /* Ajust vector size */
    vector->size++;
    return 1;
}


int remove_from_start(Vector *vector, int *removed_item) {
    int *position = get_(vector, 0);
    /* Checks if element is valid */
    if(position == NULL) {
        return 0;
    }

    /* Updates the pointer */
    *removed_item = *position;

    /* Removes item */
    vector->size--;
    vector->starting_index++;
    /* Ajust its starting index */
    if(vector->starting_index >= vector->length) {
        vector->starting_index -= vector->length;
    }

    /* Check for resize */
    if(vector->length > 8 && (vector->length / 4) > vector->size) {
        /* Attempts to resize the vector */
        resize_vector(vector, min(8, vector->length / 2));
    }
    return 1;
}


int remove_from_end(Vector *vector, int *removed_item) {
    int *position = get_(vector, vector->size - 1);
    /* Checks if element is valid */
    if(position == NULL) {
        return 0;
    }

    /* Updates the pointer */
    *removed_item = *position;

    /* Removes item */
    vector->size--;

    /* Check for resize */
    if(vector->length > 8 && (vector->length / 4) > vector->size) {
        /* Attempts to resize the vector */
        resize_vector(vector, min(8, vector->length / 2));
    }
    return 1;
}


int clear_vector(Vector *vector) {
    /* Check if the vector is valid */
    if(vector == NULL) {
        return 0;
    }

    /* Reset the vector */
    vector->starting_index = 0;
    vector->size = 0;

    /* Check for resize */
    if(vector->length > 8 && (vector->length / 4) > vector->size) {
        /* Attempts to resize the vector */
        resize_vector(vector, min(8, vector->length / 2));
    }
    return 1;
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
    vector->starting_index = 0;
    vector->length = new_length;
    return 1;
}


int *get_(Vector *vector, int position) {
    if(vector == NULL || position < -1 || position > vector->size) {
        return NULL;
    }

    /* Check if we're accessing a full vector trying to insert a new item and
    * failed to resize it */
    if(
        vector->size >= vector->length &&
        (position >= vector->length || position == -1) &&
        !resize_vector(vector, vector->length * 2)
    ) {
        return NULL;
    }

    /* Move the access position to fit the start of the vector */
    position += vector->starting_index;
    /* Cut the access position to fit the vector */
    while(position >= (vector->length - 1)) {
        position -= vector->length;
    }
    /* Shift the access position to fit the vector */
    while(position <= -1) {
        position += vector->length;
    }

    /* Finally, return the address */
    return vector->array + position;
}


int min(int a, int b) {
    return a <= b ? a : b;
}
