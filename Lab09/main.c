#include <stdio.h>
#include "map.h"


int main() {
    Map *map = NULL;
    /* Initialize the map. We'll be storing up to 5000 strings */
    if(initialize_map(&map, 12000) != 1) {
        fprintf(
            stderr,
            "Failed to initialize the map.\n"
        );
        return -1;
    }

    uint last_value = 0;

    /* Iterate through commands */
    while(1) {
        char command[256];
        fgets(command, 256, stdin);

        char operation;
        sscanf(command, "%c", &operation);

        /* Run the operation */
        if(operation == 'i') {
            char key[251];
            sscanf(command + 2, "%s", key);

            int insert_status = insert(map, key, last_value);
            if(insert_status == 1) {
                last_value++;
            } else if(insert_status < 0) {
                fprintf(
                    stderr,
                    "Failed to insert key.\n"
                );
            }
        } else if(operation == 'b') {
            char key[251];
            sscanf(command + 2, "%s", key);

            uint value;
            if(retrieve(map, key, &value) == 1) {
                printf("encontrado %u\n", value);
            } else {
                printf("nao encontrado\n");
            }
        } else if(operation == 'r') {
            char key[251];
            sscanf(command + 2, "%s", key);

            remove_node(map, key);
        } else {
            break;
        }
    }

    free_map(&map);
    return 0;
}
