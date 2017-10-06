#include <stdio.h>
#include "heap.h"

/*
* Old version (does check memory allocations, NULL pointers etc):
*    500000 -> 0.422s
*   1000000 -> 0.951s
*   5000000 -> 4.970s
* This is close to n * lg(n).
*
* New version (does not, just trust):
*    500000 -> 0.411s
*   1000000 -> 0.879s
*   5000000 -> 4.889s
*/
#define TEST_SIZE 1000000

// void print(Heap *heap) {
//     int i;
//     printf("{");
//     for(i = 0; i < heap->size; i++) {
//         if(i > 0) {
//             printf(", ");
//         }
//         printf("%d", (*(heap->nodes + i))->cost);
//     }
//     printf("}\n");
// }

// int main() {
//     Heap *heap = NULL;
//
//     initialize_heap(&heap, 100);
//
//     int key = 1;
//     insert(heap, key++, -8);
//     insert(heap, key++, -3);
//     insert(heap, key++, 5);
//     insert(heap, key++, -96);
//     insert(heap, key++, 2);
//     insert(heap, key++, -2);
//     insert(heap, key++, -3);
//     print(heap);
//     // insert(heap, key++, -3);
//     // print(heap);
//     // insert(heap, key++, -3);
//     // insert(heap, key++, -3);
//     // print(heap);
//
//     decrease_cost(heap, key - 3, -3);
//     decrease_cost(heap, key - 5, -3);
//     print(heap);
//
//     int rem_key, rem_cost;
//     remove_minimum(heap, &rem_key, &rem_cost);
//     printf("min: key = %d, cost = %d\n", rem_key, rem_cost);
//     remove_minimum(heap, &rem_key, &rem_cost);
//     printf("min: key = %d, cost = %d\n", rem_key, rem_cost);
//     remove_minimum(heap, &rem_key, &rem_cost);
//     printf("min: key = %d, cost = %d\n", rem_key, rem_cost);
//     print(heap);
//     remove_minimum(heap, &rem_key, &rem_cost);
//     printf("min: key = %d, cost = %d\n", rem_key, rem_cost);
//     print(heap);
//     remove_minimum(heap, &rem_key, &rem_cost);
//     printf("min: key = %d, cost = %d\n", rem_key, rem_cost);
//     print(heap);
//     remove_minimum(heap, &rem_key, &rem_cost);
//     printf("min: key = %d, cost = %d\n", rem_key, rem_cost);
//     print(heap);
//     // remove_minimum(heap, &rem_key, &rem_cost);
//     // printf("min: key = %d, cost = %d\n", rem_key, rem_cost);
//     // print(heap);
//     // remove_minimum(heap, &rem_key, &rem_cost);
//     // printf("min: key = %d, cost = %d\n", rem_key, rem_cost);
//     // print(heap);
//     // remove_minimum(heap, &rem_key, &rem_cost);
//     // printf("min: key = %d, cost = %d\n", rem_key, rem_cost);
//     // print(heap);
//     // remove_minimum(heap, &rem_key, &rem_cost);
//     // printf("min: key = %d, cost = %d\n", rem_key, rem_cost);
//     // print(heap);
//     // remove_minimum(heap, &rem_key, &rem_cost);
//     // printf("min: key = %d, cost = %d\n", rem_key, rem_cost);
//     // print(heap);
//
//     free_heap(&heap);
//     return 0;
// }

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
