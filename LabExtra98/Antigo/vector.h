#ifndef VECTOR_H
#define VECTOR_H


struct Vector {
    /** Array of integers, used for storing data */
    int *array;
    /** Starting index for the array */
    int starting_index;
    /** Amount of items on the array */
    int size;
    /** Array length */
    int length;
};

typedef struct Vector Vector;


/**
* Attempts to create a vector on given pointer with starting length of 8
* integers.
*
* Returns   -1  if couldn't allocate memory for vector,
*            0  if vector already exists on pointer,
*            1  if successfully created vector.
*/
int     initialize_vector   (Vector **vector);

/**
* Attempts to create a vector on given pointer with capacity of initial_length
* integers.
*
* Returns   -1  if couldn't allocate memory for vector,
*            0  if vector already exists on pointer,
*            1  if successfully created vector.
*/
int     initialize_vector_  (Vector **vector, int initial_length);

/**
* Attempts to access the vector on its inside.
*
* Returns   0   if couldn't access the vector on given position,
*           1   if successfully replaced the pointer with vector's value.
*/
int     get                 (Vector *vector, int position, int *retrieved_value);

/**
* Attempts to add inserted_item on the vector at its first position.
*
* Returns   0   if couldn't access the vector to insert the item,
*           1   if successfully added the item on start of the vector.
*/
int     insert_on_start     (Vector *vector, int inserted_item);

/**
* Attempts to add inserted_item on the vector at its last position.
*
* Returns   0   if couldn't access the vector to insert the item,
*           1   if successfully added the item on the end of the vector.
*/
int     insert_on_end       (Vector *vector, int inserted_item);

/**
* Attempts to remove the first item and pass its value to removed_item.
*
* Returns   0   if couldn't access the item to be removed,
*           1   if successfully removed the item.
*/
int     remove_from_start   (Vector *vector, int *removed_item);

/**
* Attempts to remove the last item and pass its value to removed_item.
*
* Returns   0   if couldn't access the item to be removed,
*           1   if successfully removed the item.
*/
int     remove_from_end     (Vector *vector, int *removed_item);

/**
* Attempts to clear the vector
*
* Returns   0   if vector is NULL,
*           1   if could empty its items.
*/
int     clear_vector        (Vector *vector);

/**
* Clears the memory of the vector.
*/
void    free_vector         (Vector **vector);


#endif /* VECTOR_H */
