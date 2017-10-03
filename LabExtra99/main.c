#include <string.h>
#include <stdio.h>
#include "bits.h"


int main() {
    Bits *bits = NULL;
    int n_bits;

    /* Iterate through commands */
    while(1) {
        char input[64];
        fgets(input, 64, stdin);

        char command[16];
        sscanf(input, "%s", command);

        // printf("command = \"%s\"\n", command);

        if(strcmp(command, "create") == 0) {
            sscanf(input + strlen(command) + 1, "%d", &n_bits);

            free_bits(&bits);
            if(!initialize_bits(&bits, n_bits)) {
                fprintf(
                    stderr,
                    "Failed to initialize vector of %d bits.",
                    n_bits
                );
                return -1;
            }
            // printf("created with %d bits (%d bytes)\n", n_bits, bits->n_bytes);
        } else if(strcmp(command, "add") == 0) {
            int key;
            sscanf(input + strlen(command) + 1, "%d", &key);

            if(!set_bit_true(bits, key - 1)) {
                fprintf(
                    stderr,
                    "Failed to insert %d\n",
                    key
                );
            }

            // printf("added %d\n", key);
        } else if(strcmp(command, "remove") == 0) {
            int key;
            sscanf(input + strlen(command) + 1, "%d", &key);

            if(!set_bit_false(bits, key - 1)) {
                fprintf(
                    stderr,
                    "Failed to remove %d\n",
                    key
                );
            }

            // printf("removed %d\n", key);
        } else if(strcmp(command, "in") == 0) {
            int key;
            sscanf(input + strlen(command) + 1, "%d", &key);

            printf("belongs(%d) = ", key);
            if(get_bit(bits, key - 1)) {
                printf("true\n");
            } else {
                printf("false\n");
            }
        } else if(strcmp(command, "rank") == 0) {
            int key;
            sscanf(input + strlen(command) + 1, "%d", &key);

            int rank = 0, i;
            for(i = 1; i <= key; i++) {
                /* Check how many items are behind key */
                if(get_bit(bits, i - 1)) {
                    rank++;
                }
            }

            printf("rank(%d) = %d\n", key, rank);
        } else if(strcmp(command, "select") == 0) {
            int i_th;
            sscanf(input + strlen(command) + 1, "%d", &i_th);

            int i = 0, j = 1;
            while(1) {
                /* Check if we exceeded the vector */
                if(j > n_bits) {
                    printf("select(%d) = 0\n", i_th);
                    break;
                }

                /* Check how many items are on the key until reach i_th */
                if(get_bit(bits, j - 1)) {
                    i++;
                }

                /* Check if we reached i_th */
                if(i == i_th) {
                    printf("select(%d) = %d\n", i_th, j);
                    break;
                }

                /* Increment the current key */
                j++;
            }
        } else if(strcmp(command, "rangecount") == 0) {
            int start, end;
            sscanf(input + strlen(command) + 1, "%d %d", &start, &end);

            int items = 0, key;
            for(key = start; key <= end; key++) {
                /* Count how many items between start and end */
                if(get_bit(bits, key - 1)) {
                    items++;
                }
            }

            printf("rangecount(%d,%d) = %d\n", start, end, items);
        } else if(strcmp(command, "print") == 0) {
            printf("S = {");

            int key, first = 1;
            for(key = 1; key <= n_bits; key++) {
                if(get_bit(bits, key - 1)) {
                    if(!first) {
                        printf(",");
                    }
                    printf("%d", key);
                    first = 0;
                }
            }

            printf("}\n");
        } else if(strcmp(command, "exit") == 0) {
            break;
        }
    }

    /* Free vector of bits' memory */
    free_bits(&bits);
}
