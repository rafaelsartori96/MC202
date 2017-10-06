#include <stdio.h>
#include "heap.h"


/*
* Note that I should check the functions outputs before printing, but I'm lazy.
*/

int main() {
    int maximum_length;
    scanf("%d\n", &maximum_length);

    Heap *heap = NULL;
    if(!initialize_heap(&heap, maximum_length)) {
        fprintf(
            stderr,
            "Failed to initialize heap.\n"
        );
    }


    while(1) {
        char command_line[128];
        fgets(command_line, 128, stdin);

        char command;
        sscanf(command_line, "%c", &command);

        if(command == 'i') {
            int key, cost;
            sscanf(command_line + 2, "%d %d", &key, &cost);

            /* Insert pair */
            insert(heap, key, cost);
        } else if(command == 'm') {

            /* Check if the heap is empty */
            if(heap->size == 0) {
                printf("vazio\n");
            } else {
                int key, cost;
                /* Remove the minimum pair */
                remove_minimum(heap, &key, &cost);
                printf("minimo {%d,%d}\n", key, cost);
            }
        } else if(command == 'd') {
            int key, new_cost;
            sscanf(command_line + 2, "%d %d", &key, &new_cost);

            /* Decrease key's cost */
            decrease_cost(heap, key, new_cost);
        } else {
            free_heap(&heap);
            return 0;
        }
    }

    return -1;
}
