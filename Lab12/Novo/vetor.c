/* Rafael Sartori Martins dos Santos (186154) */

#include "vetor.h"


/** Retorna o quadrado do inteiro dado */
static int quadrado(int inteiro) {
    return inteiro * inteiro;
}


int comprimento_quadrado(Vetor *vetor) {
    int comprimento = 0;
    /* Somatório de xi^2 onde xi é a coordenada da i-ésima dimensão do vetor */
    for(int coordenada = 0; coordenada < DIMENSAO; coordenada++) {
        comprimento += quadrado(vetor->coordenadas[coordenada]);
    }
    return comprimento;
}


int produto_interno(Vetor *vetor_a, Vetor *vetor_b) {
    int prod_interno = 0;
    /* Somatório de ai*bi onde xi é a coordenada da i-ésima dimensão do vetor
    * x */
    for(int coordenada = 0; coordenada < DIMENSAO; coordenada++) {
        prod_interno +=
            vetor_a->coordenadas[coordenada] *
            vetor_b->coordenadas[coordenada];
    }
    return prod_interno;
}


void diferenca(Vetor *vetor_resposta, Vetor *vetor_a, Vetor *vetor_b) {
    for(int coordenada = 0; coordenada < DIMENSAO; coordenada++) {
        vetor_resposta->coordenadas[coordenada] =
            vetor_a->coordenadas[coordenada] -
            vetor_b->coordenadas[coordenada];
    }
}


void copiar(Vetor *vetor_fonte, Vetor *vetor_destino) {
    for(int coordenada = 0; coordenada < DIMENSAO; coordenada++) {
        vetor_destino->coordenadas[coordenada] =
            vetor_fonte->coordenadas[coordenada];
    }
}


void oposto(Vetor *vetor) {
    for(int coordenada = 0; coordenada < DIMENSAO; coordenada++) {
        vetor->coordenadas[coordenada] *= -1;
    }
}
