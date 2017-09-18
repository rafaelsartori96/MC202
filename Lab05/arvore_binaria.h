#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H


/** Estrutura que representa um nó de uma árvore ArvoreBinaria */
struct No {
    /** Chave do nó */
    char chave;
    /** Filho da esquerda, NULL se não existente */
    struct No *esquerda;
    /** Filho da direita, NULL se não existente */
    struct No *direita;
};
typedef struct No No;

/** Estrutura que representa uma árvore binária com os nós do tipo No */
struct ArvoreBinaria {
    /** Raiz da árvore */
    No *raiz;
};
typedef struct ArvoreBinaria ArvoreBinaria;


/**
* A função utiliza pré-ordem para encontrar o nó com a chave desejada.
*
* Retorna   0   se não encontramos a chave na árvore,
*           1   se encontramos.
*/
// int encontrar_no(ArvoreBinaria *arvore, char chave, No **encontrado);

/**
* A função utiliza pré-ordem para encontrar o pai da chave desejada.
*
* Retorna   0   se não encontramos a chave na árvore,
*           1   se encontramos.
*/
// int encontrar_pai(ArvoreBinaria *arvore, char chave_filho, No **encontrado);

/**
* A função verifica se o filho de chave dada é filho a esquerda.
*
* Retorna   0   se não encontramos filho a esquerda com esta chave,
*           1   se o filho de chave dada é um filho a esquerda.
*/
// int filho_da_esquerda(ArvoreBinaria *arvore, char chave_filho);

/**
* A função cria um filho a esquerda do nó pai dado.
*
* Retorna   -1  se não foi possível alocar memória para o filho,
*            0  se existe filho a esquerda no pai,
*            1  se criamos e substituímos o ponteiro 'pai->esquerda'.
*/
int criar_filho_esquerda(No *pai);

/**
* A função cria um filho a direita do nó pai dado.
*
* Retorna   -1  se não foi possível alocar memória para o filho,
*            0  se existe filho a direita no pai,
*            1  se criamos e substituímos o ponteiro 'pai->direita'.
*/
int criar_filho_direita(No *pai);

/**
* A função cria um nó raiz em 'arvore'.
*
* Retorna   -1  se não foi possível alocar memória para o nó,
*            0  se existe raiz,
*            1  se criamos e substituímos o ponteiro 'arvore->raiz'.
*/
int criar_raiz(ArvoreBinaria *arvore);

/**
* Inicializa a árvore binária 'arvore'.
*
* Retorna   -1  caso não tenha sido possível alocar memória para a árvore,
*            0  caso já exista uma árvore em 'arvore',
*            1  caso inicializamos com sucesso.
*/
int inicializar_arvore(ArvoreBinaria **arvore);

/**
* Limpa todos os nós da árvore 'arvore'.
*/
void limpar_arvore(ArvoreBinaria *arvore);

/**
* Apaga a variável 'arvore' liberando sua memória. Esta função utiliza a função
* limpar_arvore(ArvoreBinaria).
*/
void destruir_arvore(ArvoreBinaria **arvore);

/**
* Imprime todos os nós utilizando o método pós-ordem.
*/
void imprimir_pos_ordem(ArvoreBinaria *arvore);


#endif /* ARVORE_BINARIA_H */
