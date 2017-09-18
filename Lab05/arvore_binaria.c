#include <stdio.h>
#include <stdlib.h>
#include "arvore_binaria.h"


/** Função recursiva auxiliar de encontrar_no. A função assume que raiz não é
* NULL */
// int encontrar_no_r(
//     ArvoreBinaria *arvore, char chave, No **encontrado, No *raiz
// );

/** Função recursiva auxiliar de encontrar_pai. A função assume que raiz não é
* NULL */
// int encontrar_pai_r(
//     ArvoreBinaria *arvore, char chave_filho, No **encontrado, No *raiz
// );

/** Função recursiva auxiliar de filho_da_esquerda. A função assume que raiz não
* é NULL */
// int filho_da_esquerda_r(
//     ArvoreBinaria *arvore, char chave_filho, No *raiz
// );

/**
* Função auxiliar para criar_filho_esquerda, criar_filho_direita e criar_raiz.
*
* Retorna   -1  quando não for possível alocar memória para o nó,
*            0  caso exista filho na variável dada e
*            1  caso for possível.
*/
int criar_no(No **no);

/** Função auxiliar recursiva a limpar_arvore. Utiliza pós-ordem. */
void limpar_arvore_r(No *raiz);

/** Função auxiliar recursiva a imprimir_pos_ordem. */
void imprimir_pos_ordem_r(No *raiz);


int inicializar_arvore(ArvoreBinaria **arvore) {
    /* Conferimos se existe árvore na variável */
    if(*arvore != NULL) {
        return 0;
    }

    *arvore = malloc(sizeof(ArvoreBinaria));
    /* Conferimos se conseguimos alocar memória dinâmica para a árvore */
    if(*arvore == NULL) {
        return -1;
    }

    /* Inicializamos seus atributos */
    (*arvore)->raiz = NULL;
    return 1;
}


// int encontrar_pai(ArvoreBinaria *arvore, char chave_filho, No **encontrado) {
//     if(arvore->raiz != NULL && arvore->raiz->chave != chave_filho) {
//         /* Fazemos a busca utilizando pré-ordem */
//         return encontrar_pai_r(arvore, chave_filho, encontrado, arvore->raiz);
//     } else {
//         /* Como a árvore está vazia ou como o filho não possui pai, não
//         * procuramos */
//         return 0;
//     }
// }


// int encontrar_pai_r(
//     ArvoreBinaria *arvore, char chave_filho, No **encontrado, No *raiz
// ) {
//     /* Procuramos na raiz */
//     /* Se algum dos filhos tem a chave desejada, retornamos nó atual */
//     if((raiz->esquerda != NULL && raiz->esquerda->chave == chave_filho) ||
//         (raiz->direita != NULL && raiz->direita->chave == chave_filho)) {
//         *encontrado = raiz;
//         return 1;
//     }
//
//     /* Procuramos no filho da esquerda */
//     if(raiz->esquerda != NULL &&
//                 encontrar_pai_r(arvore, chave_filho, encontrado, raiz->esquerda)) {
//         return 1;
//     }
//
//     /* Procuramos no filho da direita */
//     if(raiz->direita != NULL &&
//                 encontrar_pai_r(arvore, chave_filho, encontrado, raiz->direita)) {
//         return 1;
//     }
//
//     /* Retornamos 0 se não encontramos */
//     return 0;
// }


// int encontrar_no(ArvoreBinaria *arvore, char chave, No **encontrado) {
//     if(arvore->raiz != NULL) {
//         /* Fazemos a busca utilizando pré-ordem */
//         return encontrar_no_r(arvore, chave, encontrado, arvore->raiz);
//     } else {
//         /* Como a árvore está vazia, não procuramos */
//         return 0;
//     }
// }


// int encontrar_no_r(ArvoreBinaria *arvore, char chave, No **encontrado, No *raiz) {
//     /* Procuramos na raiz */
//     if(chave == raiz->chave) {
//         *encontrado = raiz;
//         return 1;
//     }
//
//     /* Procuramos no filho da esquerda */
//     if(raiz->esquerda != NULL &&
//                     encontrar_no_r(arvore, chave, encontrado, raiz->esquerda)) {
//         return 1;
//     }
//
//     /* Procuramos no filho da direita */
//     if(raiz->direita != NULL &&
//                     encontrar_no_r(arvore, chave, encontrado, raiz->direita)) {
//         return 1;
//     }
//
//     /* Retornamos 0 se não encontramos */
//     return 0;
// }


// int filho_da_esquerda(ArvoreBinaria *arvore, char chave_filho) {
//     if(arvore->raiz != NULL && arvore->raiz->chave != chave_filho) {
//         /* Fazemos a busca utilizando pré-ordem */
//         return filho_da_esquerda_r(arvore, chave_filho, arvore->raiz);
//     } else {
//         /* Como a árvore está vazia ou como o filho não possui pai, não
//         * procuramos */
//         return 0;
//     }
// }


// int filho_da_esquerda_r(
//     ArvoreBinaria *arvore, char chave_filho, No *raiz
// ) {
//     /* Procuramos no filho da esquerda atual ou nos seus filhos */
//     if(raiz->esquerda != NULL && (raiz->esquerda->chave == chave_filho ||
//             filho_da_esquerda_r(arvore, chave_filho, raiz->esquerda))) {
//         return 1;
//     }
//
//     /* Procuramos nos filho do filho da direita */
//     if(raiz->direita != NULL) {
//         return filho_da_esquerda_r(arvore, chave_filho, raiz->direita);
//     }
//
//     return 0;
// }


int criar_no(No **no) {
    /* Caso exista um nó no ponteiro, não fazemos nada. */
    if((*no) != NULL) {
        return 0;
    }

    *no = malloc(sizeof(No));
    /* Verificamos se foi possível alocar memória para o nó */
    if((*no) == NULL) {
        return -1;
    }

    /* Inicializamos o nó */
    (*no)->direita = NULL;
    (*no)->esquerda = NULL;
    return 1;
}


int criar_raiz(ArvoreBinaria *arvore) {
    return criar_no(&(arvore->raiz));
}


int criar_filho_esquerda(No *pai) {
    return criar_no(&(pai->esquerda));
}


int criar_filho_direita(No *pai) {
    return criar_no(&(pai->direita));
}


void limpar_arvore(ArvoreBinaria *arvore) {
    /* Liberamos a árvore recursivamente */
    if(arvore->raiz != NULL) {
        limpar_arvore_r(arvore->raiz);
        free(arvore->raiz);
        arvore->raiz = NULL;
    }
}


void limpar_arvore_r(No *raiz) {
    /* Liberamos a raiz da esquerda */
    if(raiz->esquerda != NULL) {
        limpar_arvore_r(raiz->esquerda);
        free(raiz->esquerda);
    }

    /* Liberamos a raiz da direita */
    if(raiz->direita != NULL) {
        limpar_arvore_r(raiz->direita);
        free(raiz->direita);
    }
}


void destruir_arvore(ArvoreBinaria **arvore) {
    if(*arvore == NULL) {
        return;
    }

    /* Liberamos a árvore após limpar seus nós */
    limpar_arvore(*arvore);
    free(*arvore);
    *arvore = NULL;
}


void imprimir_pos_ordem(ArvoreBinaria *arvore) {
    imprimir_pos_ordem_r(arvore->raiz);
}


void imprimir_pos_ordem_r(No *raiz) {
    /* Imprimimos, se existir, raiz da esquerda */
    if(raiz->esquerda != NULL) {
        imprimir_pos_ordem_r(raiz->esquerda);
    }

    /* Imprimimos, se existir, raiz da direita */
    if(raiz->direita != NULL) {
        imprimir_pos_ordem_r(raiz->direita);
    }

    /* Imprimimos a chave da raiz atual */
    printf("%c", raiz->chave);
}
