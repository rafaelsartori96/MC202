#include <stdlib.h>
#include "conjuntos.h"

static int min(int a, int b) {
    return a < b ? a : b;
}


static int max(int a, int b) {
    return a > b ? a : b;
}


int inicializar_conjuntos(Conjuntos **conjuntos, int num_conjuntos) {
    /* Conferimos se já existe */
    if((*conjuntos) != NULL) {
        return 0;
    }

    /* Alocamos memória para a estrutura */
    (*conjuntos) = malloc(sizeof(Conjuntos));
    if((*conjuntos) == NULL) {
        return -1;
    }

    /* Tentamos alocar memória para os conjuntos unitários */
    (*conjuntos)->representantes = malloc(num_conjuntos * sizeof(int));
    if((*conjuntos)->representantes == NULL) {
        return -1;
    }

    /* Inicializamos as variáveis da estrutura */
    (*conjuntos)->num_conjuntos = num_conjuntos;
    limpar_conjuntos(*conjuntos);

    return 1;
}


void uniao(Conjuntos *conjuntos, int conjunto_a, int conjunto_b) {
    int representante_a = representante(conjuntos, conjunto_a),
        representante_b = representante(conjuntos, conjunto_b);

    /* Verificamos se os representantes já são iguais */
    if(representante_a == representante_b) {
        return;
    }

    int min_representante = min(representante_a, representante_b),
        max_representante = max(representante_a, representante_b);

    /* Verificamos os elementos cujo representante é o máximo e transformamos
    * no mínimo */
    for(int i = 0; i < conjuntos->num_conjuntos; i++) {
        int *representante = (conjuntos->representantes + i);

        /* Verificamos se precisamos substituir */
        if(*representante == max_representante) {
            /* Substituímos através do apontador */
            *representante = min_representante;
        }
    }
}


int representante(Conjuntos *conjuntos, int conjunto) {
    /* Como mantemos a altura 1, é possível apenas: */
    return *(conjuntos->representantes + conjunto);
}


void limpar_conjuntos(Conjuntos *conjuntos) {
    /* Inicializamos os conjuntos como unitários */
    for(int i = 0; i < conjuntos->num_conjuntos; i++) {
        *(conjuntos->representantes + i) = i;
    }
}


void liberar_conjuntos(Conjuntos **conjuntos) {
    free((*conjuntos)->representantes);
    free(*conjuntos);
    *conjuntos = NULL;
}
