#include <stdio.h>
#include <stdlib.h>
#include "lista_dupla_encadeada.h"


int inicializar_lista(ListaD **lista) {
    liberar_lista(lista);

    /* Alocamos memória para a lista */
    *lista = malloc(sizeof(ListaD));
    if((*lista) == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a estrutura da lista.\n");
        return 0;
    }

    /* Inicializamos seus atributos */
    (*lista)->cabeca = NULL;
    (*lista)->cauda = NULL;
    (*lista)->tamanho = 0;
    return 1;
}


void liberar_lista(ListaD **lista) {
    /* Ignoramos uma lista não inicializada */
    if(*lista == NULL) return;

    (*lista)->cauda = NULL;
    ItemD *auxiliar = NULL;
    while((*lista)->cabeca != NULL) {
        auxiliar = (*lista)->cabeca;
        /* Parará a iteração quando a lista acabar */
        (*lista)->cabeca = (*lista)->cabeca->proximo;
        (*lista)->tamanho--;
        free(auxiliar);
    }

    /* Checamos por falhas de execução */
    if((*lista)->tamanho != 0)
        fprintf(
            stderr,
            "A lista tem tamanho %d quando devia ser 0!\n",
            (*lista)->tamanho
        );

    /* Liberamos o resto da lista agora */
    free(*lista);
    *lista = NULL;
}


int adicionar_item_na_cabeca(ListaD *lista, ItemD **item_criado) {
    /* Alocamos memória para um novo elemento */
    ItemD *item = malloc(sizeof(ItemD));
    if(item == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo item.\n");
        return 0;
    }

    if(lista->cauda == NULL) {
        /* Se a lista estiver vazia, temos de definir a cauda */
        lista->cauda = item;
        /* Note que faremos de qualquer forma 'lista->cabeca' ser atualizado */
    } else {
        /* Se há primeiro item, fazemos ele apontar 'anterior' para a
        * nova cabeça que estamos criando */
        lista->cabeca->anterior = item;
    }

    /* Adicionamos o resto da lista na nova cabeça da lista */
    item->proximo = lista->cabeca;
    item->anterior = NULL;

    /* Adicionamos a cabeça à lista */
    lista->cabeca = item;
    lista->tamanho++;

    /* Retornamos o item ao usuário */
    *item_criado = item;
    return 1;
}


int adicionar_item_a_cauda(ListaD *lista, ItemD **item_criado) {
    /* Alocamos memória para um novo elemento */
    ItemD *item = malloc(sizeof(ItemD));
    if(item == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo item.\n");
        return 0;
    }

    /* Adicionamos a nova cauda ao último elemento da lista */
    if(lista->cabeca != NULL) {
        ItemD *auxiliar = lista->cabeca;
        while(1) {
            /* Se encontramos o final da lista, adicionamos o último elemento */
            if(auxiliar->proximo == NULL) {
                /* Adicionamos a lista */
                auxiliar->proximo = item;
                lista->cauda = item;
                lista->tamanho++;

                /* Modificamos os ponteiros de ligação do item.
                * Como estamos inserindo no FINAL de uma lista NÃO VAZIA,
                * teremos que o próximo apontará para NULL e o anterior, ao
                * auxiliar */
                item->proximo = NULL;
                item->anterior = auxiliar;

                /* Retornamos ao usuário */
                *item_criado = item;
                return 1;
            } else {
                auxiliar = auxiliar->proximo;
            }
        }
    } else {
        /* Se a lista estiver vazia, simplesmente adicionamos item */
        lista->cabeca = item;
        lista->cauda = item;
        lista->tamanho++;

        /* Como a lista está vazia, não há para onde apontar */
        item->proximo = NULL;
        item->anterior = NULL;

        /* Retornamos ao usuário */
        *item_criado = item;
        return 1;
    }
}


int remover_item_sem_liberar(ListaD *lista, int chave, ItemD **item_removido) {
    ItemD *no_atual = lista->cabeca;
    /* Se a lista está vazia, não fazemos nada */
    if(no_atual == NULL) return 0;

    /* Conferimos se o item está no início da lista (caso especial, alteramos
    * lista) */
    if(lista->cabeca->chave == chave) {
        /* Removemos da cabeça da lista */
        lista->cabeca = lista->cabeca->proximo;
        lista->tamanho--;

        /* Verificamos se a nova cabeça é um item válido, pois precisamos
        * atualizar o seu 'anterior' */
        if(lista->cabeca != NULL) {
            lista->cabeca->anterior = NULL;
        }

        /* Verificamos se a cauda é o item que removemos da cabeça.
        * Nota: não precisamos verificar se é NULL, pois a lista contém
        *       elementos */
        if(lista->cauda->chave == chave) {
            /* Se é o único elemento da lista, devemos retirar a cauda também */
            lista->cauda = NULL;
        }

        /* Retornamos ao usuário */
        *item_removido = no_atual;
        return 1;
    }

    /* Agora, conferimos se está no meio/fim da lista */
    while(no_atual != NULL) {
        if(no_atual->proximo != NULL && no_atual->proximo->chave == chave) {
            /* Colocamos o item removido no ponteiro dado */
            *item_removido = no_atual->proximo;

            /* Tornamos nulo seus apontadores */
            (*item_removido)->proximo = NULL;
            (*item_removido)->anterior = NULL;

            /* Removemos da lista atualizando os ponteiros.
            * Note:  aqui, o no_atual é aquele cujo proximo possuia a chave
            *        que desejávamos remover */
            no_atual->proximo = no_atual->proximo->proximo;
            no_atual->proximo->anterior = no_atual;

            lista->tamanho--;
            return 1;
        }

        no_atual = no_atual->proximo;
    }
    return 0;
}


int remover_item(ListaD *lista, int chave) {
    ItemD *item_removido = NULL;
    if(!remover_item_sem_liberar(lista, chave, &item_removido)) {
        /* Retornamos falha caso ele não tenha sido encontrado */
        return 0;
    } else {
        /* Liberamos a memória do item caso ele tenha sido removido da lista
        * com sucesso */
        free(item_removido);
        return 1;
    }
}
