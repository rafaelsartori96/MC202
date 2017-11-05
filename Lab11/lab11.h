#ifndef LAB11_H
#define LAB11_H
#include "vetor_circular.h"


#define TAMANHO_MAXIMO 20000


struct Vertice {
    /** Palavra do vértice */
    char palavra[21];
    /** Vetor de vizinhos */
    VetorCircular vizinhos;

    /* Para a busca em largura */
    /** Armazena 1 se o vértice foi ou 0, se não visitado */
    int visitado;
    /** Armazena a distância até o vértice inicial da busca */
    int distancia;
};

struct Grafo {
    /** Vetor de vértices */
    struct Vertice *vertices;
    /** Capacidade do vetor de vértices */
    int capacidade_vertices;
    /** Número de nós no grafo */
    int numero_vertices;
};


typedef struct Vertice Vertice;
typedef struct Grafo Grafo;


/**
* Inicializa o grafo e seus atributos. Utiliza o macro TAMANHO_MAXIMO para o
* tamanho inicial dos vetores.
*
* Retorna   -2  caso não for possível inicializar a matriz de adjacências,
*           -1  caso não for possível alocar recursos para o grafo,
*            0  caso o grafo já exista na variável,
*            1  se o grafo for criado com sucesso.
*/
int inicializar_grafo(Grafo **grafo);

/**
* Adiciona a palavra ao grafo, reconhecendo vizinhos.
* 'palavra' deve ser alocada dinâmicamente.
*/
void adiciona_vertice(Grafo *grafo, char *palavra_nova);

/**
* Calcula a maior distância entre qualquer vértice e os vértices mais distantes.
*
* Retorna   -1  caso não tenha diso possível criar as estruturas de dados
*               auxiliares,
*            x  a maior distância.
*/
int maior_distancia(Grafo *grafo);

/**
* Libera recursos alocados para o grafo.
*/
void liberar_grafo(Grafo **grafo);

#endif /* LAB11_H */
