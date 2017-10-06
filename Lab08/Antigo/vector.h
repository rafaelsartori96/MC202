#ifndef VECTOR_H
#define VECTOR_H


struct Vector {
    /** Array of integers, used for storing data */
    int *array;
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
* Returns   vector's value on given position.
*/
int     get                 (Vector *vector, int position);

/**
* Attempts to set the vector integer on given position to set_value.
*
* Returns   0   if couldn't access the vector on given position,
*           1   if successfully replaced the value on the vector.
*/
int     set                 (Vector *vector, int position, int set_value);

/**
* Attempts to remove the element from the vector.
*
* Returns   0   if couldn't access the vector on given position,
*           1   if successfully replaced the value on the vector.
*/
int     reset               (Vector *vector, int position);

/**
* Clears the memory of the vector.
*/
void    free_vector         (Vector **vector);


#endif /* VECTOR_H */
