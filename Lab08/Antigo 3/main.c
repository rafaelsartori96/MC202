#include <stdio.h>
#include "heap.h"


int main() {
    int maximum_length;
    scanf("%d", &maximum_length);

    Heap *heap = NULL;
    if(!initialize_heap(&heap, maximum_length)) {
        fprintf(
            stderr,
            "Failed to initialize heap.\n"
        );
    }

    char command_line[128], command;
    int key, cost;
    while(1) {
        fgets(command_line, 128, stdin);

        sscanf(command_line, "%c", &command);

        if(command == 't') {
            break;
        } else if(command == 'i') {
            sscanf(command_line + 2, "%d %d", &key, &cost);

            /* Attempt to insert the key */
            if(insert(heap, key, cost) < 0) {
                fprintf(
                    stderr,
                    "Failed to insert key = %d, cost = %d\n",
                    key, cost
                );
                free_heap(&heap);
                return -1;
            }
        } else if(command == 'm') {
            switch (remove_minimum(heap, &key, &cost)) {
                case -1:
                    fprintf(
                        stderr,
                        "Failed to remove minimum key.\n"
                    );
                    free_heap(&heap);
                    return -1;
                case 0:
                    printf("vazio\n");
                    break;
                case 1:
                    printf("minimo {%d,%d}\n", key, cost);
                    break;
            }
        } else if(command == 'd') {
            sscanf(command_line + 2, "%d %d", &key, &cost);

            if(decrease_cost(heap, key, cost) < 0) {
                fprintf(
                    stderr,
                    "Failed to decrease cost to %d from key %d.\n",
                    cost, key
                );
                free_heap(&heap);
                return -1;
            }
        }
    }

    free_heap(&heap);
    return 0;
}
