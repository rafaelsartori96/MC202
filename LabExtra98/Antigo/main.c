#include <stdio.h>
#include "vector.h"


int main() {
    while(1) {
        int commands;
        /* Read the number of commands to be executed */
        scanf("%d", &commands);

        /* Check if we need to stop */
        if(commands == 0) {
            return 0;
        }

        Vector *stack = NULL, *queue = NULL;
        /* Attempt to initialize vector */
        if(!initialize_vector(&queue) || !initialize_vector(&stack)) {
            fprintf(
                stderr,
                "Couldn't initialize the vector.\n"
            );
            free_vector(&queue);
            free_vector(&stack);
            return -1;
        }

        /* Attributes to check the data structure */
        int queue_friendly = 1, stack_friendly = 1;

        int command;
        /* Iterate through commands */
        for(command = 0; command < commands; command++) {
            int operation, key;
            /* Read the operation and key to be executed */
            scanf("%d %d\n", &operation, &key);

            if(operation == 1) {
                /* Insertion operation */
                if(!insert_on_end(stack, key) || !insert_on_end(queue, key)) {
                    fprintf(
                        stderr,
                        "Failed to insert item on vector.\n"
                    );
                    free_vector(&queue);
                    free_vector(&stack);
                    return -1;
                }
            } else if(operation == 2) {
                /* Removal operation */
                int removed_item;

                /* Attempts to remove from stack */
                if(!remove_from_end(stack, &removed_item)) {
                    fprintf(
                        stderr,
                        "Failed to remove from stack\n"
                    );
                    free_vector(&queue);
                    free_vector(&stack);
                    return -1;
                } else if(removed_item != key) {
                    stack_friendly = 0;
                }

                /* Attempts to remove from queue */
                if(!remove_from_start(queue, &removed_item)) {
                    fprintf(
                        stderr,
                        "Failed to remove from queue\n"
                    );
                    free_vector(&queue);
                    free_vector(&stack);
                    return -1;
                } else if(removed_item != key) {
                    queue_friendly = 0;
                }
            } else {
                fprintf(
                    stderr,
                    "Command failed to be parsed: %d\n",
                    operation
                );
            }
        }

        /* Prints the result */
        if(queue_friendly && stack_friendly) {
            printf("duvida\n");
        } else if(queue_friendly) {
            printf("fila\n");
        } else if(stack_friendly) {
            printf("pilha\n");
        } else {
            printf("impossivel\n");
        }

        /* Free resources */
        free_vector(&stack);
        free_vector(&queue);
    }
}
