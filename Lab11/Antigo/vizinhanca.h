#ifndef LISTAS_VIZINHOS_H
#define LISTAS_VIZINHOS_H


struct Vizinho {
    /** Vértice do vizinho */
    int vertice;
    /** Apontador para o próximo vizinho */
    struct Vizinho *proximo;
};

struct Vizinhanca {
    /** Vetor de listas de vizinhos */
    struct Vizinho **vizinhos;
    /** Número de listas de vizinhos */
    int listas;
};

typedef struct Vizinho Vizinho;
typedef struct Vizinhanca Vizinhanca;


/**
* Inicializa a lista de vizinhos.
*
* Retorna   -1  se não foi possível alocar memória para a estrutura,
*            0  se ja existe uma estrutura de vizinhos no ponteiro dado,
*            1  se inicializamos com sucesso.
*/
int inicializar_lista_de_vizinhanca(Vizinhanca **vizinhanca, int vizinhos);

/**
* Verifica se o vertice_a possui como vizinho vertice_b.
*
* Retorna   0   se não possui como vizinho,
*           1   se possui como vizinho.
*/
int possui_vizinho(Vizinhanca *vizinhanca, int vertice_a, int vertice_b);

/**
* Cria vizinhança entre o vertice_a e o vertice_b.
*
* Retorna   -1  se não foi possível criar vizinhança,
*            0  se a vizinhança já existe,
*            1  se a vizinhança foi criada.
*/
int criar_vizinhanca(Vizinhanca *vizinhanca, int vertice_a, int vertice_b);

/**
* Libera os recursos alocados para a matriz de adjacências.
*/
void liberar_vizinhanca(Vizinhanca **vizinhanca);


#endif /* LISTAS_VIZINHOS_H */
