#ifndef VETOR_CIRCULAR_H
#define VETOR_CIRCULAR_H


#define CAPACIDADE_INICIAL 8
#define FATOR_INCREMENTO 1.5
#define FATOR_DECREMENTO 0.5
#define LIMIAR_DECREMENTO 0.25


struct VetorCircular {
    /** Vetor que será usado como circular */
    int *vetor;
    /** Posição de início do vetor circular. Indexado em zero. */
    int inicio;
    /** Capacidade do vetor */
    int capacidade;
    /* Número de itens do vetor */
    int tamanho;
};

typedef struct VetorCircular VetorCircular;


/**
* Inicializa o vetor circular.
*
* Retorna   -1  caso não foi possível alocar memória para o vetor,
*            0  caso já exista vetor no ponteiro dado,
*            1  caso foi possível criar o vetor circular.
*/
int inicializar_vetor_circular(VetorCircular **vetor_circ);

/**
* Inicializa o vetor circular previamente alocado.
*
* Retorna   -1  caso não foi possível alocar memória para o vetor,
*            1  caso foi possível criar o vetor circular.
*/
int inicializar_vetor_circular_(VetorCircular *vetor_circ);

/**
* Retorna o valor do vetor na posição requisitada no ponteiro dado.
*
* Retorna   0   se não foi possível acessar 'posicao',
*           1   se o ponteiro foi substituído.
*/
int recebe_valor(VetorCircular *vetor_circ, int posicao, int *valor);

/**
* Retorna se o valor pertence ou não ao vetor.
*
* Retorna   0   se não pertence,
*           1   se pertence.
*/
int pertence(VetorCircular *vetor_circ, int valor);

/**
* Insere algum valor no início do vetor circular.
*
* Retorna   -1  caso não foi possível realocar o vetor e inserir o item,
*            0  caso não foi possível acessar a posição inicial do vetor,
*            1  caso foi possível inserir o item no início do vetor.
*/
int insere_valor_inicio(VetorCircular *vetor_circ, int valor);

/**
* Insere algum valor no fim do vetor circular.
*
* Retorna   -1  caso não foi possível realocar o vetor e inserir o item,
*            0  caso não foi possível acessar a posição final do vetor,
*            1  caso foi possível inserir o item no fim do vetor.
*/
int insere_valor_fim(VetorCircular *vetor_circ, int valor);

/**
* Remove o item do início do vetor e retorna seu valor no ponteiro dado.
*
* Retorna   0   caso não foi possível acessar a posição do início do vetor ou
*               ele está vazio,
*           1   caso o item foi removido com sucesso.
*/
int remove_inicio(VetorCircular *vetor_circ, int *valor);

/**
* Remove o item do fim do vetor e retorna seu valor no ponteiro dado.
*
* Retorna   0   caso não foi possível acessar a posição do fim do vetor ou
*               ele está vazio,
*           1   caso o item foi removido com sucesso.
*/
int remove_fim(VetorCircular *vetor_circ, int *valor);

/**
* Libera os recursos alocados para o vetor circular.
*/
void liberar_vetor_circular(VetorCircular **vetor_circ);

/**
* Libera os recursos alocados para o vetor circular alocado previamente.
*/
void liberar_vetor_circular_(VetorCircular *vetor_circ);

#endif /* VETOR_CIRCULAR_H */
