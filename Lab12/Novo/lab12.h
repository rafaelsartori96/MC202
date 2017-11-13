/* Rafael Sartori Martins dos Santos (186154) */

#ifndef LAB12_H
#define LAB12_H
/* Deve possuir DIMENSAO 3 */
#include "vetor.h"

/**
* Conceito por trás da resolução:
*
* Para calcular a distância entre 2 asteróides, usamos funções de distância,
* derivadas da função clássica: raiz quadrada da soma dos quadrados da
* diferença das coordenadas.
*
* São equações do segundo grau em função do tempo t. Usaremos elas para
* determinar quais instantes devemos executar o algoritmo de árvore geradora de
* mínimo e conferir quantas vezes as conexões de mínimo se alteram.
*
* A distância é dada por uma função de t:
*
* dist^2 AB(t) = a * t^2 + (2 * d) * t + c;
*
* Onde o termo independente é o quadrado do comprimento do vetor diferença de
* posição, o termo 'a', o quadrado do comprimento do vetor diferença de veloci-
* dade. O termo d é o produto interno entre esses dois vetores.
*
* Nota: a concavidade da função é sempre para cima, pois a >= 0.
*
* Usando a física do problema, conseguimos determinar uma função do segundo
* grau que calcula os instantes em que 2 asteróides ficam com mesma distância
* em relação a um terceiro. Desta maneira, é possível determinar possíveis
* instantes intermediários aos de distância coincidente para verificar se a
* árvore geradora de mínimo se altera.
*
* Nota: devemos ignorar tempos menores que zero (instante inicial dado).
*
* A função que chegamos deriva de
* dist^2 AB(t) = dist^2 AC(t)
* solucionamos para t, encontrando:
*
* a * t^2 + (2 * d) * t + c = 0;
*
* Onde o termo 'c' é a diferença dos quadrados dos comprimentos das diferenças
* de posições de cada asteroide em relação ao terceiro, o termo 'b', a
* diferença entre os produtos internos das diferenças de posição e velocidade
* dos asteroides em relação ao terceiro e o termo 'a' a diferença dos quadrados
* dos comprimentos das diferenças de velocidade de cada asteroide em relação ao
* terceiro.
*
* Usamos o discriminante para determinar se calculamos ou não calculamos os
* tempos. Ele deve ser positivo e não nulo para ser considerável (duas raízes
* reais). Devemos ainda filtrar por raízes positivas que não tenham sido
* adicionadas (com precisão e-6) na lista de instantes a serem analisados.
*/


struct DiferencaAsteroide {
    /** Guardará a diferença de posição inicial em cada coordenada. */
    Vetor posicao;
    /** Guardará a diferença de velocidade em cada coordenada. */
    Vetor velocidade;

    /** Distância entre os dois asteróides num instante definido */
    double distancia;

    /** Linha na matriz de distâncias dos asteroides */
    int linha;
    /** Coluna na matriz de distâncias dos asteróides */
    int coluna;
    /** Índice no vetor linearizado da matriz de distâncias dos asteróides */
    int indice;
};

struct MatrizDiferenca {
    /** Matriz linearizada simétrica */
    struct DiferencaAsteroide *vetor;
};

struct Asteroide {
    /** Posição inicial do asteroide */
    Vetor posicao_inicial;
    /** Velocidade do asteroide */
    Vetor velocidade;
};

typedef struct Asteroide Asteroide;
typedef struct DiferencaAsteroide DiferencaAsteroide;
typedef struct MatrizDiferenca MatrizDiferenca;


struct Instante {
    /** Instante de tempo t */
    double t;
    /** Arestas envolvidas */
    int arestas[2];
    /** Apontador para o próximo instante */
    struct Instante *proximo;
};

typedef struct Instante Instante;


/**
* Retorna um ponteiro para o elemento (linha, coluna) da matriz diferença, que
* deve ser uma matriz simétrica sem diagonal principal.
*/
DiferencaAsteroide *buscar(MatrizDiferenca *matriz_dif, int linha, int coluna);

/**
* Insere o instante dado 't' na lista 'instantes' de modo a manter a ordem da
* lista. Assumimos que a lista tenha sido inicializada com o instante t = 0.
*
* Retorna   -1  caso não tenha sido possível criar a estrutura de instante,
*            1  caso o item tenha sido inserido corretamente.
*/
int inserir_ordenado(
    Instante *instantes, double t, int indice_0, int indice_1
);

/**
* Libera toda memória alocada dinâmicamente para a lista de instantes
*/
void liberar_lista(Instante *instantes);


#endif /* LAB12_H */
