#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lab11.h"


int main() {
    Grafo *grafo = NULL;

    /* Inicializamos o grafo */
    if(inicializar_grafo(&grafo) != 1) {
        fprintf(stderr, "Falha ao inicializar o grafo!\n");
        return -1;
    }

    /* Enquanto recebemos entradas, adicionamos ao grafo */
    char input[24];
    while(fgets(input, 24, stdin) != NULL) {
        /* Removemos \n */
        input[strlen(input) - 1] = '\0';

        /* Adicionamos a palvra ao grafo */
        adiciona_vertice(grafo, input);
    }

    /* Calculamos a maior distância */
    printf("%d\n", maior_distancia(grafo));

    /* Liberamos o grafo */
    liberar_grafo(&grafo);
    return 0;
}
