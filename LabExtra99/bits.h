#ifndef BITS_H
#define BITS_H


struct Bits {
    /** Vector of bits */
    char *vector;
    /** Number of bytes on the vector */
    int n_bytes;
};

typedef struct Bits Bits;


/**
* Attempts to create a vector of n bits.
*
* Returns   -1  if couldn't create bit vector,
*            0  if bit vector already exists,
*            1  if could create bit vector.
*/
int initialize_bits(Bits **bits, int n_bits);

/**
* Attempts to set the bit_index bit of the vector true.
*
* Returns   0   if bit is invalid,
*           1   if set the bit to true.
*/
int set_bit_true(Bits *bits, int bit_index);

/**
* Attempts to set the bit_index bit of the vector false.
*
* Returns   0   if bit is invalid,
*           1   if set the bit to false.
*/
int set_bit_false(Bits *bits, int bit_index);

/**
* Avaliates the bit_index bit on the vector.
*
* Returns   0   if the bit is invalid or false,
*           1   if the bit is true.
*/
int get_bit(Bits *bits, int bit_index);

/**
* Free the memory stored for the bits.
*/
void free_bits(Bits **bits);


#endif /* BITS_H */
