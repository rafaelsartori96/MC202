#include <stdio.h>
#include "heap.h"


int main() {
    Heap *heap = NULL;
    if(!initialize_heap(&heap, 12)) {
        fprintf(
            stderr,
            "Failed to initialize heap.\n"
        );
    }

    int key = 1;
    while(key <= 12) {
        int cost = -8 + (key * 3 * (key % 2 == 0 ? -1 : 1));
        printf("inserting {key = %d, cost = %d}\n", key, cost);
        if(!insert_pair(heap, key, cost)) {
            fprintf(
                stderr,
                "Failed to insert pair { key = %d, cost = %d }.\n",
                key, cost
            );
        }
        key++;
    }

    decrease_cost(heap, 4, -999);

    key = 1;
    while(key <= 12) {
        int rem_key, rem_cost;
        if(!remove_minimum(heap, &rem_key, &rem_cost)) {
            fprintf(
                stderr,
                "Failed to remove pair.\n"
            );
        }
        key++;
        printf("removed pair { key = %d, cost = %d }\n", rem_key, rem_cost);
    }

    free_heap(&heap);
    return 0;
}
