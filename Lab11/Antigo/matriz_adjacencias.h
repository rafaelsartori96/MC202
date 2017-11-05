#ifndef MATRIZ_ADJACENCIAS_H
#define MATRIZ_ADJACENCIAS_H
#include "vetor_binario.h"


struct MatrizAdjacencias {
    /** Número de linhas e colunas na matriz */
    int linhas_colunas;

    /** Vetor binário que representa a matriz */
    VetorBinario *bits;
};

typedef struct MatrizAdjacencias MatrizAdjacencias;


/**
* Inicializa a matriz de bits.
*
* Retorna   -1  se não foi possível alocar memória para a matriz,
*            0  se ja existe uma matriz no ponteiro dado,
*            1  se inicializamos com sucesso.
*/
int inicializar_matriz_adjacencias(
    MatrizAdjacencias **matriz, int linhas_colunas
);

/**
* Verifica o estado do bit.
*
* Nota: a indexação começa do zero, ou seja, a primeira posição é (0, 0).
*
* Retorna   0   se o bit está no estado 'false' ou está fora da posição válida,
*           1   se o bit está no estado 'true'.
*/
int recebe_bit_(MatrizAdjacencias *matriz, int linha, int coluna);

/**
* Alterna o bit na posição dada para 1.
*
* Nota: a indexação começa do zero, ou seja, a primeira posição é (0, 0).
*
* Retorna   0   se não foi possível acessar a posição dada,
*           1   se o bit foi alterado com sucesso.
*/
int define_bit_verdadeiro_(MatrizAdjacencias *matriz, int linha, int coluna);

/**
* Alterna o bit na posição dada para 0.
*
* Nota: a indexação começa do zero, ou seja, a primeira posição é (0, 0).
*
* Retorna   0   se não foi possível acessar a posição dada,
*           1   se o bit foi alterado com sucesso.
*/
int define_bit_falso_(MatrizAdjacencias *matriz, int linha, int coluna);

/**
* Libera os recursos alocados para a matriz de adjacências.
*/
void liberar_matriz_adjacencias(MatrizAdjacencias **matriz);


#endif /* MATRIZ_ADJACENCIAS_H */
