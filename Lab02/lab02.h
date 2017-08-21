#ifndef LAB02_H
#define LAB02_H
#include "lista.h"


int main();

/**
* Esta função retornará um ponteiro em lista, uma lista inicializada por chaves
* em ordem 1..num_chaves inclusive.
*
* A função checa por erros de alocação.
*/
int inicializar_lista(Item **lista, int num_chaves);

/**
* Esta função retornará um ponteiro para o nó buscado em 'no', o custo da busca
* em 'custo'.
*
* Retorna 0 caso não exista a chave.
*/
int buscar_chave(Item *lista, Item **no, int *custo, int chave);

/**
* Esta função move o item de chave dada para o começo da lista.
*
* A chave deve pertencer a lista. Retorna 0 caso não encontrar a chave.
*/
int colocar_na_cabeca(Item **lista, int chave);

/**
* Esta função imprime a variável contador de cada item da lista.
*/
void imprimir_lista_contador(Item *lista);


#endif /* LAB02_H */
