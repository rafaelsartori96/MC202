/*
* Rafael Sartori Martins dos Santos (RA: 186154)
*
* Por questões de consistência, documentarei em inglês (ou o mais próximo disso).
*/
#include <stdio.h>
#include <string.h>
#include "tree.h"


int main() {
    int nodes_amount, commands_amount;
    scanf("%d %d\n", &nodes_amount, &commands_amount);

    Node *node_pool = NULL;
    /* Initialize node_pool */
    if(!initialize_node_pool(&node_pool, nodes_amount)) {
        fprintf(
            stderr,
            "Failed to create node pool!\n"
        );
        return -1;
    }

    int i;
    for(i = 0; i < commands_amount; i++) {
        char command[8];
        /* Read the command */
        scanf("%s", command);

        if(strcmp(command, "lca") == 0) {
            int key_a, key_b;
            scanf("%d %d\n", &key_a, &key_b);

            Node *a = NULL, *b = NULL;
            /* Search for the node */
            if(
                !search_node(node_pool, key_a, &a) ||
                !search_node(node_pool, key_b, &b)
            ) {
                fprintf(
                    stderr,
                    "Failed at finding key.\n"
                );
            } else {
                Node *lca_ = NULL;
                if(lca(a, b, &lca_)) {
                    printf("%d\n", lca_->key);
                } else {
                    fprintf(
                        stderr,
                        "Failed to find the lowest common ancestor.\n"
                    );
                }
            }
        } else if(strcmp(command, "link") == 0) {
            int key_a, key_b;
            scanf("%d %d\n", &key_a, &key_b);

            Node *old_root = NULL, *father = NULL;
            /* Search for the node */
            if(
                !remove_from_pool(&node_pool, key_a, &old_root) ||
                !search_node(node_pool, key_b, &father)
            ) {
                fprintf(
                    stderr,
                    "Failed at removing A from node pool finding key B.\n"
                );
            } else {
                link(old_root, father);
            }
        } else if(strcmp(command, "cut") == 0) {
            int key_a;
            scanf("%d\n", &key_a);

            Node *a = NULL;
            /* Search for the node */
            if(!search_node(node_pool, key_a, &a)) {
                fprintf(
                    stderr,
                    "Failed at finding key.\n"
                );
            } else {
                cut(&node_pool, a);
            }
        } else {
            fprintf(
                stderr,
                "Command not recognized!\n"
            );
        }
    }

    free_node_pool(&node_pool);
    return 0;
}
