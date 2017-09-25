#ifndef ARVORE_BIN_BUSCA_H
#define ARVORE_BIN_BUSCA_H


/** Estrutura que representa um nó de uma árvore ArvoreBinariaBusca */
struct No {
    /** Chave do nó */
    int chave;
    /** Pai */
    struct No *pai;
    /** Filho da esquerda, NULL se não existente */
    struct No *esquerda;
    /** Filho da direita, NULL se não existente */
    struct No *direita;
};
typedef struct No No;

/** Estrutura que representa uma árvore binária de busca com os nós tipo No */
struct ArvoreBinariaBusca {
    /** Raiz da árvore */
    No *raiz;
};
typedef struct ArvoreBinariaBusca ArvoreBinariaBusca;


/**
* Inicializa a árvore binária de busca 'arvore'.
*
* Retorna   -1  caso não tenha sido possível alocar memória para a árvore,
*            0  caso já exista uma árvore em 'arvore',
*            1  caso inicializamos com sucesso.
*/
int inicializar_arvore(ArvoreBinariaBusca **arvore);

/**
* Adiciona o item 'chave' na posição correta (de maneira a manter a ordem da
* árvore binária de busca 'arvore').
*
* Retorna   -1  se não houve memória suficiente para o novo elemento,
*            0  se o elemento já existia,
*            1  se o elemento foi inserido corretamente.
*/
int inserir(ArvoreBinariaBusca *arvore, int chave);

/**
* Remove o item 'chave' da árvore binária de busca 'arvore' mantendo sua ordem.
* Irá mover o sucessor de 'chave' para o lugar dela.
*
* Retorna   -1  caso não encontramos um sucessor quando esperávamos,
*            0  caso não haja chave,
*            1  caso removemos da árvore corretamente.
*/
int remover(ArvoreBinariaBusca *arvore, int chave);

/**
* Verificamos se a chave 'chave' pertence a árvore binária de busca 'arvore'.
*
* Retorna   0   caso a chave não foi encontrada na árvore,
*           1   caso a chave pertence a arvore.
*/
int pertence(ArvoreBinariaBusca *arvore, int chave);

/**
* Busca o menor elemento da árvore 'árvore' e o coloca no ponteiro 'minimo' caso
* existir.
*
* Retorna   0   caso a árvore esteja vazia,
*           1   caso executou com sucesso.
*/
int minimo(ArvoreBinariaBusca *arvore, No **minimo_);

/**
* Busca o máximo elemento da árvore 'árvore' e o coloca no ponteiro 'maximo' caso
* existir.
*
* Retorna   0   caso a árvore esteja vazia,
*           1   caso executou com sucesso.
*/
int maximo(ArvoreBinariaBusca *arvore, No **maximo_);

/**
* Imprime todos os nós utilizando o método pré-ordem.
*
* Retorna   0   caso a árvore esteja vazia,
*           1   caso os itens foram impressos.
*/
int imprimir_pre_ordem(ArvoreBinariaBusca *arvore);

/**
* Imprime todos os nós utilizando o método em-ordem.
*
* Retorna   0   caso a árvore esteja vazia,
*           1   caso os itens foram impressos.
*/
int imprimir_em_ordem(ArvoreBinariaBusca *arvore);

/**
* Imprime todos os nós utilizando o método pós-ordem.
*
* Retorna   0   caso a árvore esteja vazia,
*           1   caso os itens foram impressos.
*/
int imprimir_pos_ordem(ArvoreBinariaBusca *arvore);

/**
* Imprime todos os nós utilizando o método em largura.
*
* Retorna   0   caso a árvore esteja vazia,
*           1   caso os itens foram impressos.
*/
int imprimir_em_largura(ArvoreBinariaBusca *arvore);

/**
* Limpa todos os nós da árvore 'arvore'.
*/
void limpar_arvore(ArvoreBinariaBusca *arvore);

/**
* Apaga a variável 'arvore' liberando sua memória. Esta função utiliza a função
* limpar_arvore(ArvoreBinariaBusca).
*/
void destruir_arvore(ArvoreBinariaBusca **arvore);


#endif /* ARVORE_BIN_BUSCA_H */
