#include <stdlib.h>
#include <stdio.h>
#include "matriz_binaria.h"


int inicializar_matriz_binaria(MatrizBinaria **matriz, int linhas, int colunas) {
    /* Verificar se a matriz já existe */
    if((*matriz) != NULL) {
        return 0;
    }

    /* Tentamos alocar recursos para a estrutura da matriz */
    (*matriz) = malloc(sizeof(MatrizBinaria));
    if((*matriz) == NULL) {
        fprintf(
            stderr,
            "Não foi possível iniciar estrutura da matriz binária!\n"
        );
        return -1;
    }

    /* Verificamos se o vetor foi inicializado com sucesso */
    (*matriz)->bits = NULL;
    int inicializacao = inicializar_vetor_binario(
        &(*matriz)->bits, linhas * colunas
    );
    if(inicializacao != 1) {
        fprintf(
            stderr,
            "Não foi possível iniciar vetor de bits para a matriz!\n"
        );
        free(*matriz);
        (*matriz) = NULL;
        return inicializacao;
    }

    /* Agora inicializamos os atributos */
    (*matriz)->linhas = linhas;
    (*matriz)->colunas = colunas;

    return 1;
}


int recebe_bit_(MatrizBinaria *matriz, int linha, int coluna) {
    /* Calculamos a posição do bit no vetor linearizado */
    return recebe_bit(matriz->bits, (linha * matriz->colunas) + coluna);
}


int define_bit_verdadeiro_(MatrizBinaria *matriz, int linha, int coluna) {
    /* Calculamos a posição do bit no vetor linearizado */
    return define_bit_verdadeiro(
        matriz->bits, (linha * matriz->colunas) + coluna
    );
}


int define_bit_falso_(MatrizBinaria *matriz, int linha, int coluna) {
    /* Calculamos a posição do bit no vetor linearizado */
    return define_bit_falso(matriz->bits, (linha * matriz->colunas) + coluna);
}


void liberar_matriz_binaria(MatrizBinaria **matriz) {
    /* Verificamos se a matriz existe */
    if((*matriz) == NULL) {
        return;
    }

    /* Liberamos recursos */
    liberar_vetor_binario(&(*matriz)->bits);
    free(*matriz);
    (*matriz) = NULL;
}
