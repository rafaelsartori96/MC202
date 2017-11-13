/* Rafael Sartori Martins dos Santos (186154) */

#include <stdlib.h>
#include <math.h>
#include "lab12.h"


static int min(int a, int b) {
    return a < b ? a : b;
}


static int max(int a, int b) {
    return a > b ? a : b;
}


DiferencaAsteroide *buscar(
    MatrizDiferenca *matriz_dif, int linha, int coluna
) {
    /* Definimos a linha para ser a maior coordenada, assim podemos percorrê-la
    * facilmente entre as linhas E colunas. */

    /** Linha corrigida para matriz simétrica */
    int linha_  = max(linha, coluna);
    /** Coluna corrigida para matriz simétrica */
    int coluna_ = min(linha, coluna);

    return (matriz_dif->vetor + (linha_ * (linha_ - 1) / 2) + coluna_);
}


int inserir_ordenado(
    Instante *instantes, double t, int indice_0, int indice_1
) {
    Instante *auxiliar = instantes;

    /* Vemos se é menor que todos os tempos */
    if(t < auxiliar->t) {
        return 0;
    }

    /* Como sabemos que é inicializada pelo elemento zero, buscamos o nó
    * anterior ao nó de tempo maior que o tempo do instante dado */
    while(auxiliar->proximo != NULL && t > auxiliar->proximo->t) {
        auxiliar = auxiliar->proximo;
    }

    /* Criamos a estrutura */
    Instante *instante = malloc(sizeof(Instante));
    if(instante == NULL) {
        return -1;
    }

    /* Inicializamos o instante */
    instante->t = t;
    instante->arestas[0] = indice_0;
    instante->arestas[1] = indice_1;
    /* Colocamos o instante entre o novo e o próximo do auxiliar (seja
    * inexistente, seja de tempo maior ao que inserimos) */
    instante->proximo = auxiliar->proximo;
    auxiliar->proximo = instante;

    return 1;
}


void liberar_lista(Instante *instantes) {
    Instante *auxiliar = instantes;
    while(instantes != NULL) {
        instantes = instantes->proximo;
        free(auxiliar);
        auxiliar = instantes;
    }
}
