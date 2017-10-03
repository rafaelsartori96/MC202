#include <stdlib.h>
#include <stdio.h>
#include "list.h"


int main() {
    while(1) {
        int commands;
        /* Read the number of commands to be executed */
        scanf("%d", &commands);

        /* Check if we need to stop */
        if(commands == 0) {
            return 0;
        }

        /* Empty lists */
        Node *stack = NULL, *queue = NULL;
        int stack_viable = 1, queue_viable = 1;

        int command;
        /* Iterate through commands */
        for(command = 0; command < commands; command++) {
            int operation, key;
            /* Read the operation and key to be executed */
            scanf("%d %d\n", &operation, &key);

            if(operation == 1) {
                /* Insert operation */
                if(!insert_on_end(&stack, key) || !insert_on_end(&queue, key)) {
                    fprintf(
                        stderr,
                        "Failed to insert %d on the lists.\n",
                        key
                    );
                    free_list(&stack);
                    free_list(&queue);
                    return -1;
                }
            } else if(operation == 2) {
                /* Remove operation */

                /* Check if stack is a valid data structure */
                Node *stack_end = get_end(stack);
                /* If the end isn't what we excepted, stack is not viable */
                if(stack_end == NULL || stack_end->key != key) {
                    stack_viable = 0;
                } else {
                    remove_from_list(&stack, key);
                }

                Node *queue_head = queue;
                /* Check if the start isn't what we expected */
                if(queue_head == NULL || queue_head->key != key) {
                    queue_viable = 0;
                } else {
                    remove_from_list(&queue, key);
                }
            } else {
                fprintf(
                    stderr,
                    "Failed to recognize operation '%d'!\n",
                    operation
                );
            }
        }

        /* Prints the result */
        if(queue_viable && stack_viable) {
            printf("duvida\n");
        } else if(queue_viable) {
            printf("fila\n");
        } else if(stack_viable) {
            printf("pilha\n");
        } else {
            printf("impossivel\n");
        }

        /* Empty lists */
        free_list(&stack);
        free_list(&queue);
    }
}


int insert_on_end(Node **list, int key) {
    /* Attempt to allocate memory for the node */
    Node *new = malloc(sizeof(Node));
    if(new == NULL) {
        return -1;
    }
    /* Initialize new's attribute */
    new->key = key;

    /* Retrieve the end of the list */
    Node *end = get_end(*list);

    if(end != NULL) {
        /* Insert new node at the end */
        end->next = new;
        new->previous = end;
        new->next = NULL;
    } else {
        *list = new;
        new->previous = NULL;
        new->next = NULL;
    }
    return 1;
}


Node *get_end(Node *list) {
    Node *end = list;
    /* Iterate until find the end wich next points to NULL */
    while(end != NULL && end->next != NULL) {
        end = end->next;
    }
    return end;
}


void remove_from_list(Node **list, int key) {
    /* Check if the list is empty */
    if(*list == NULL) {
        return;
    }

    Node *auxiliary = *list;

    /* Check if the head has the desired key */
    if((*list)->key == key) {
        /* Note that auxiliary points to the old head */

        /* Change the lists' head */
        *list = (*list)->next;
        /* Update the new head's pointers */
        if((*list) != NULL) {
            (*list)->previous = NULL;
        }

        /* Finally, free old head's memory */
        free(auxiliary);
        return;
    }

    /* Find the key */
    while(auxiliary != NULL) {
        /* Break the chain if we reached desired key */
        if(auxiliary->key == key) {
            break;
        }

        auxiliary = auxiliary->next;
    }

    /* Returns if the key isn't on the list */
    if(auxiliary == NULL) {
        return;
    }

    /* Update the pointers */
    /* Since the removed key isn't at the start, there is a previous node */
    auxiliary->previous->next = auxiliary->next;
    if(auxiliary->next != NULL) {
        /* Attempts to update next's pointer */
        auxiliary->next->previous = auxiliary->previous;
    }
    free(auxiliary);
}


void free_list(Node **list) {
    Node *auxiliary;
    while(*list != NULL) {
        auxiliary = *list;
        /* Update to new head */
        *list = (*list)->next;
        /* Free old head */
        free(auxiliary);
    }
}
