#ifndef MATRIZ_BINARIA_H
#define MATRIZ_BINARIA_H
#include "vetor_binario.h"


struct MatrizBinaria {
    /** Número de linhas na matriz */
    int linhas;
    /** Número de colunas na matriz */
    int colunas;

    /** Vetor binário que representa a matriz */
    VetorBinario *bits;
};

typedef struct MatrizBinaria MatrizBinaria;


/**
* Inicializa a matriz de bits.
*
* Retorna   -1  se não foi possível alocar memória para a matriz,
*            0  se ja existe uma matriz no ponteiro dado,
*            1  se inicializamos com sucesso.
*/
int inicializar_matriz_binaria(MatrizBinaria **matriz, int linhas, int colunas);

/**
* Verifica o estado do bit.
*
* Nota: a indexação começa do zero, ou seja, a primeira posição é (0, 0).
*
* Retorna   0   se o bit está no estado 'false' ou está fora da posição válida,
*           1   se o bit está no estado 'true'.
*/
int recebe_bit_(MatrizBinaria *matriz, int linha, int coluna);

/**
* Alterna o bit na posição dada para 1.
*
* Nota: a indexação começa do zero, ou seja, a primeira posição é (0, 0).
*
* Retorna   0   se não foi possível acessar a posição dada,
*           1   se o bit foi alterado com sucesso.
*/
int define_bit_verdadeiro_(MatrizBinaria *matriz, int linha, int coluna);

/**
* Alterna o bit na posição dada para 0.
*
* Nota: a indexação começa do zero, ou seja, a primeira posição é (0, 0).
*
* Retorna   0   se não foi possível acessar a posição dada,
*           1   se o bit foi alterado com sucesso.
*/
int define_bit_falso_(MatrizBinaria *matriz, int linha, int coluna);

/**
* Libera os recursos alocados para a matriz binária.
*/
void liberar_matriz_binaria(MatrizBinaria **matriz);


#endif /* MATRIZ_BINARIA_H */
