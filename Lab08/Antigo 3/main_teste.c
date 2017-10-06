#include <stdio.h>
#include "heap.h"

/*
* ~MEMORY_FRIENDLY
*    500000 -> 0.422s
*   1000000 -> 0.951s
*   5000000 -> 4.970s
* This is close to n * lg(n).
*
* MEMORY_FRIENDLY
* A lot of time.. Gave up, the problem is indeed time.
*/
#define TEST_SIZE 500000


int main() {
    Heap *heap = NULL;

    if(!initialize_heap(&heap, TEST_SIZE)) {
        fprintf(
            stderr,
            "Failed to initialize heap.\n"
        );
    }

    int key = 0;
    while(key < TEST_SIZE) {
        int cost = -8 + (key * 3 * (key % 2 == 0 ? -1 : 1));
        if(!insert(heap, key, cost)) {
            fprintf(
                stderr,
                "Failed to insert pair { key = %d, cost = %d }.\n",
                key, cost
            );
        }
        key++;
    }

    decrease_cost(heap, 4, -999);

    key = 0;
    while(key < TEST_SIZE) {
        int rem_key, rem_cost;
        if(!remove_minimum(heap, &rem_key, &rem_cost)) {
            fprintf(
                stderr,
                "Failed to remove pair.\n"
            );
        }
        key++;
    }

    free_heap(&heap);
    return 0;
}
