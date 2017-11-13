#ifndef CONJUNTOS_H
#define CONJUNTOS_H


/*
* Nota: funciona apenas para indexação em zero.
*/

struct Conjuntos {
    /** Vetor de representantes de cada conjunto */
    int *representantes;
    /** Número de conjuntos */
    int num_conjuntos;
};

typedef struct Conjuntos Conjuntos;


/**
* Inicializa o vetor que representam os conjuntos. Inicialmente, todos são
* conjuntos unitários.
*
* Retorna   -1  caso não tenha sido possível inicializar o vetor de conjuntos,
*            0  caso já exista um vetor no ponteiro dado,
*            1  caso a inicialização tenha acontecido corretamente.
*/
int inicializar_conjuntos(Conjuntos **conjuntos, int num_conjuntos);

/**
* Faz a união dos conjuntos, optando pelo menor representante.
*/
void uniao(Conjuntos *conjuntos, int conjunto_a, int conjunto_b);

/**
* Busca o representante do conjunto.
*
* Retorna o índice do representante.
*/
int representante(Conjuntos *conjuntos, int conjunto);

/**
* Reinicia todos os membros dos conjuntos como unitários.
*/
void limpar_conjuntos(Conjuntos *conjuntos);

/**
* Libera memória alocada para os conjuntos.
*/
void liberar_conjuntos(Conjuntos **conjuntos);


#endif /* CONJUNTOS_H */
