#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H


typedef struct ItemE {
    int chave;
    struct ItemE* proximo;
} ItemE;


typedef struct {
    int tamanho;
    ItemE *cabeca;
} ListaE;


/**
* A função inicializa uma lista alocada dinâmicamente
*
* Retorna 0 caso não conseguir alocar memória para a variável lista, 1 caso
* executar corretamente.
*/
int inicializar_lista(ListaE **lista);

/**
* Esta função liberará toda a memória alocada para a lista. O ponteiro dado re-
* ceberá NULL.
*/
void liberar_lista(ListaE **lista);

/**
* A função adiciona um item como a cabeça da lista dada, que terá seu valor
* definido pelo usuário.
*
* Retorna 0 caso não conseguir alocar memória para o novo item.
*/
int adicionar_item_na_cabeca(ListaE *lista, ItemE **item_criado);

/**
* A função adiciona um item como a cauda da lista dada, que terá seu valor
* definido pelo usuário.
*
* Retorna 0 caso não conseguir alocar memória para o novo item.
*/
int adicionar_item_a_cauda(ListaE *lista, ItemE **item_criado);

/**
* Esta função remove o elemento da lista, mantendo-a ligada e sem liberar o
* item.
*
* Retorna 0 caso o item não tenha sido encontrado.
*/
int remover_item_sem_liberar(ListaE *lista, int chave, ItemE **item_removido);

/**
* Esta função remove o elemento da lista, mantendo-a ligada.
*
* Retorna 0 caso o item não tenha sido encontrado.
*/
int remover_item(ListaE *lista, int chave);


#endif /* LISTA_ENCADEADA_H */
