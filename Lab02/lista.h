#ifndef LISTA_H
#define LISTA_H


typedef struct Item {
    int chave;
    int contador;
    struct Item* proximo;
} Item;


/**
* A função adiciona um Item como a cabeça da lista dada, que terá seu valor
* alterado.
*
* Retorna 0 caso não conseguir alocar memória para o novo item.
*/
int adicionar_item_no_topo(Item **lista, int chave);

/**
* A função adiciona um Item como a cauda da lista dada, que terá seu valor
* alterado.
*
* Retorna 0 caso não conseguir alocar memória para o novo item.
*/
int adicionar_item_no_fim(Item **lista, int chave);

/**
* Esta função remove o elemento da lista, mantendo-a ligada e sem liberar o
* item.
*
* Retorna 0 caso o item não tenha sido encontrado.
*/
int remover_item(Item **lista, Item **removido, int chave);

/**
* Esta função liberará toda a memória alocada para a lista. O ponteiro dado re-
* ceberá NULL.
*/
void liberar_lista(Item **lista);

/**
* Esta função simplesmente imprimirá a lista.
*/
void imprimir_lista(Item *lista);

#endif /* LISTA_H */
