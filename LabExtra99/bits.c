#include <stdlib.h>
#include <limits.h>
#include "bits.h"


int initialize_bits(Bits **bits, int n_bits) {
    /* Checks if the structure exists */
    if((*bits) != NULL) {
        return 0;
    }

    /* Allocate memory for the holding structure */
    *bits = malloc(sizeof(Bits));
    if((*bits) == NULL) {
        return -1;
    }

    /* The number of bytes will be the division of the number of bits by the
    * number of bits on the basic structure that you're using.
    * I'll round up the integer division so we don't waste memory and can
    * keep all the bits */
    (*bits)->n_bytes = (n_bits % CHAR_BIT) > 0 ?
        (n_bits / CHAR_BIT) + 1 : (n_bits / CHAR_BIT);

    /* Allocate memory for the vector.
    *
    * Note that we NEED to use calloc since we check bits not initialized
    * assuming they're zero. */
    (*bits)->vector = calloc((*bits)->n_bytes, sizeof(char));
    if((*bits)->vector == NULL) {
        free(*bits);
        *bits = NULL;
        return -1;
    }

    return 1;
}


int set_bit_true(Bits *bits, int bit_index) {
    /* Calculate the byte index and the bit index inside that byte */
    int byte_index = bit_index / CHAR_BIT;
    int bit_index_on_byte = bit_index % CHAR_BIT;

    /* Check for out of range bit_index */
    if(byte_index > bits->n_bytes) {
        return 0;
    }

    /* Since we're going to set the bit to true, we want to shift the active bit
    * to the corresponding position on the bit's vector byte.
    * After that, we need to a bit-wise OR operation so we can merge the mask
    * and the vector's byte. */
    char mask = 1 << bit_index_on_byte;
    /* On the bit_index_on_byte bit, we will have a OR of 1 and anything (0 or 1)
    * that we don't know. Since the operation is an OR, it'll necessarily be 1
    * after applying the mask.
    *
    * Note that
    *       bits->vector[byte_index] |= mask
    * is the same as
    *       bits->vector[byte_index] = bits->vector[byte_index] | mask
    */
    bits->vector[byte_index] |= mask;
    return 1;
}

int set_bit_false(Bits *bits, int bit_index) {
    /* Calculate the byte index and the bit index inside that byte */
    int byte_index = bit_index / CHAR_BIT;
    int bit_index_on_byte = bit_index % CHAR_BIT;

    /* Check for out of range bit_index */
    if(byte_index > bits->n_bytes) {
        return 0;
    }

    /* Since we're going to set the bit to false, we want to shift the active bit
    * to the corresponding position on the bit's vector byte and negate the mask,
    * so we don't change other values.
    * After that, we need to a bit-wise AND operation so we can merge the mask
    * and the vector's byte. */
    char mask = ~(1 << bit_index_on_byte);
    /* On the bit_index_on_byte bit, we will have a AND of 0 and anything (0 or
    * 1) that we don't know. Since the operation is an AND, it'll necessarily be
    * 0 after applying the mask. We ignore all the other bits since we did an
    * bit-wise negation operation while creating the mask. */
    bits->vector[byte_index] &= mask;
    return 1;
}


int get_bit(Bits *bits, int bit_index) {
    /* Calculate the byte index and the bit index inside that byte */
    int byte_index = bit_index / CHAR_BIT;
    int bit_index_on_byte = bit_index % CHAR_BIT;

    /* Check for out of range bit_index */
    if(byte_index > bits->n_bytes) {
        return 0;
    }

    /* Now, we will build the same mask as set_bit_true, that is, the mask, when
    * merged with the byte we're analyzing, will give us a value that equals
    * zero or equals something greather than zero (on the range 2^0 or 2^3)
    * since it'll be merged through a bit-wise AND operation, like set_bit_false.
    * If the bit is zero, (mask & byte) will be zero.
    * If the bit is one, (mask & byte) will be 1 at the position of the bit on
    * the byte, that will give us something between 2^0 and 2^3.
    * So the result will be greater than zero if the bit is 1 and 0 if the bit
    * is zero.
    *
    * Note that this operation WILL NOT change the vector, since the result is
    * not stored but just compared just like an integer. */
    return (bits->vector[byte_index] & (1 << bit_index_on_byte)) > 0;
}


void free_bits(Bits **bits) {
    /* Check if the vector is already NULL */
    if((*bits) == NULL) {
        return;
    }

    /* Free everything */
    free((*bits)->vector);
    free(*bits);
    *bits = NULL;
}
