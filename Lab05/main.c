#include <stdio.h>
#include <string.h>
#include "arvore_binaria.h"

// #define DEBUG
#ifdef DEBUG
    #define dprintf printf
#else
    #define dprintf(...)
#endif


/**
* A função compara a impressão de uma árvore binária "em-ordem" e "pré-ordem"
* para construir uma árvore binária na variável 'arvore'.
*/
void reconstruir_arvore(char *pre_ordem, char *em_ordem, ArvoreBinaria *arvore);

/** Função auxiliar recursiva para reconstruir_arvore. */
void reconstruir_arvore_r(
    char    *pre_ordem,
    char    *em_ordem,
    int     str_len,
    No      *atual
);


/**
* Repartimos o vetor de caracteres 'string' em 'a' e 'b', definindo o início de
* 'a' em 'ini_a' cujo tamanho será 'str_len_a'. 'b' análogo. Não incluindo 'c'
* em 'a' nem em 'b'.
*
* Retorna   1   caso foi possível repartir a string,
*           0   caso não encontramos o caractere 'c'.
*/
int split(
    char    *string,
    int     str_len,
    int     *ini_a,
    int     *str_len_a,
    int     *ini_b,
    int     *str_len_b,
    char    c
);


int main() {
    /** Vetor de caracteres de entrada, representa árvore em pré-ordem.
    * Capacidade máxima: alfabeto minúsculo + maiúsculo + '\0' */
    char pre_ordem[(2 * 26) + 1];
    /** Vetor de caracteres de entrada, representa árvore em em-ordem.
    * Capacidade máxima: alfabeto minúsculo + maiúsculo + '\0' */
    char em_ordem[(2 * 26) + 1];

    /** Árvore binária que será reciclada em cada iteração */
    ArvoreBinaria *arvore = NULL;
    if(!inicializar_arvore(&arvore)) {
        fprintf(stderr, "Erro ao alocar memória dinâmica para árvore.\n");
        return -1;
    }

    /* Lemos todos os casos de teste */
    while(scanf("%s %s\n", pre_ordem, em_ordem) != EOF) {
        dprintf("Lido pre_ordem = \"%s\", em_ordem = \"%s\"\n", pre_ordem,
                em_ordem);

        /* Limpamos a árvore passada */
        limpar_arvore(arvore);

        /* Reconstruímos a árvore a partir de pre_ordem e em_ordem */
        reconstruir_arvore(pre_ordem, em_ordem, arvore);

        /* Imprimimos a árvore em pós-ordem */
        imprimir_pos_ordem(arvore);
        printf("\n");
        dprintf("\n\n\n");
    }

    /* Destruímos a árvore, já que acabamos */
    destruir_arvore(&arvore);
    return 0;
}


void reconstruir_arvore(
    char            *pre_ordem,
    char            *em_ordem,
    ArvoreBinaria   *arvore
) {
    /* Criamos a raiz e deixamos para a função recursiva fazer o resto */
    if(!criar_raiz(arvore)) {
        fprintf(
            stderr,
            "Falha ao criar raiz para árvore.\n"
        );
        return;
    }

    reconstruir_arvore_r(pre_ordem, em_ordem, strlen(pre_ordem), arvore->raiz);
}


void reconstruir_arvore_r(
        char    *pre_ordem,
        char    *em_ordem,
        int     str_len,
        No      *atual
) {
    /* Adicionamos a chave atual ao nó */
    atual->chave = *(pre_ordem);

    /* Definimos as variáveis dos futuros sub-strings */
    int inicio_esquerda, str_len_esquerda;
    int inicio_direita, str_len_direita;

    /* Dividimos a string */
    if(!split(
        em_ordem, str_len,
        &inicio_esquerda, &str_len_esquerda,
        &inicio_direita, &str_len_direita,
        *(pre_ordem)
    )) {
        fprintf(
            stderr,
            "Erro ao dividir a string \"%s\" no caractere '%c'.\n",
            em_ordem,
            *(pre_ordem)
        );
        return;
    }

    dprintf(
        "nó atual = '%c' da string pre = \"%s\", em = \"%s\" (lim: %d)\n"
        "Dividimos para a esquerda: len = %d pre = \"%s\" em = \"%s\"\n"
        "Dividimos para a direita: len = %d pre = \"%s\" em = \"%s\"\n",
        atual->chave,
        pre_ordem,
        em_ordem,
        str_len,
        str_len_esquerda,
        pre_ordem + 1,
        em_ordem + inicio_esquerda,
        str_len_direita,
        pre_ordem + 1 + str_len_esquerda,
        em_ordem + inicio_direita
    );

    /* Conferimos se há sub-árvore a esquerda */
    if(str_len_esquerda > 0) {
        /* Criamos o filho, já que há sub-árvore */
        if(!criar_filho_esquerda(atual)) {
            fprintf(
                stderr,
                "Erro ao criar filho a esquerda de '%c'\n",
                atual->chave
            );
        }

        /* Chamamos a função recursivamente para a sub-string da esquerda */
        reconstruir_arvore_r(
            /* Ignoramos o item atual */
            pre_ordem + 1,
            /* Fazemos o shift para o início da esquerda */
            em_ordem + inicio_esquerda,
            /* Passamos o tamanho tal que limite as funções de manipulação */
            str_len_esquerda,
            atual->esquerda
        );
    }


    /* Conferimos se há sub-árvore a direita */
    if(str_len_direita > 0) {
        /* Criamos o filho, já que há sub-árvore */
        if(!criar_filho_direita(atual)) {
            fprintf(
                stderr,
                "Erro ao criar filho a direita de '%c'\n",
                atual->chave
            );
        }

        /* Chamamos a função recursivamente para a sub-string da direita */
        reconstruir_arvore_r(
            /* Ignoramos o item atual e a string da esquerda */
            pre_ordem + 1 + str_len_esquerda,
            /* Fazemos o shift para o início da direita */
            em_ordem + inicio_direita,
            /* Passamos o tamanho tal que limite as funções de manipulação */
            str_len_direita,
            atual->direita
        );
    }
}


int split(
    char *string, int str_len,
    int *ini_a, int *str_len_a,
    int *ini_b, int *str_len_b,
    char c
) {
    int i;
    for(i = 0; i < str_len && *(string + i) != '\0'; i++) {
        /* Se encontramos o caractere, fazemos a divisão */
        if(*(string + i) == c) {
            /* Definimos a sub-string 'a' */
            *ini_a = 0;
            *str_len_a = i;
            /* Definimos a sub-string 'b' com o "resto" */
            *ini_b = i + 1;
            *str_len_b = str_len - (*str_len_a) - 1;
            return 1;
        }
    }

    /* Caso não encontramos o caractere, retornamos 0 */
    return 0;
}
