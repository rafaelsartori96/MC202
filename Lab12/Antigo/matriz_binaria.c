#include <stdlib.h>
#include "matriz_binaria.h"


static int min(int a, int b) {
    return a < b ? a : b;
}


static int max(int a, int b) {
    return a > b ? a : b;
}


int inicializar_matriz_binaria(
    MatrizBinaria **matriz, int linhas_colunas
) {
    /* Verificar se a matriz já existe */
    if((*matriz) != NULL) {
        return 0;
    }

    /* Tentamos alocar recursos para a estrutura da matriz */
    (*matriz) = malloc(sizeof(MatrizBinaria));
    if((*matriz) == NULL) {
        return -1;
    }

    /* Verificamos se o vetor foi inicializado com sucesso */
    (*matriz)->bits = NULL;
    int inicializacao = inicializar_vetor_binario(
        &(*matriz)->bits, (linhas_colunas * (linhas_colunas - 1)) / 2
    );
    if(inicializacao != 1) {
        free(*matriz);
        (*matriz) = NULL;
        return inicializacao;
    }

    /* Agora inicializamos os atributos */
    (*matriz)->linhas_colunas = linhas_colunas;

    return 1;
}


int recebe_bit_(MatrizBinaria *matriz, int linha, int coluna) {
    /* Calculamos a posição do bit no vetor linearizado */
    /** Linha corrigida para matriz simétrica */
    int linha_  = max(linha, coluna);
    /** Coluna corrigida para matriz simétrica */
    int coluna_ = min(linha, coluna);

    return recebe_bit(matriz->bits, (linha_ * (linha_ - 1) / 2) + coluna_);
}


int define_bit_verdadeiro_(MatrizBinaria *matriz, int linha, int coluna) {
    /* Calculamos a posição do bit no vetor linearizado */
    /** Linha corrigida para matriz simétrica */
    int linha_  = max(linha, coluna);
    /** Coluna corrigida para matriz simétrica */
    int coluna_ = min(linha, coluna);

    return define_bit_verdadeiro(
        matriz->bits, (linha_ * (linha_ - 1) / 2) + coluna_
    );
}


int define_bit_falso_(MatrizBinaria *matriz, int linha, int coluna) {
    /* Calculamos a posição do bit no vetor linearizado */
    /** Linha corrigida para matriz simétrica */
    int linha_  = max(linha, coluna);
    /** Coluna corrigida para matriz simétrica */
    int coluna_ = min(linha, coluna);

    return define_bit_falso(
        matriz->bits, (linha_ * (linha_ - 1) / 2) + coluna_
    );
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
