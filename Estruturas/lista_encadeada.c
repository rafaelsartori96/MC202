#include <stdio.h>
#include <stdlib.h>
#include "lista_encadeada.h"


int inicializar_lista(ListaE **lista) {
    liberar_lista(lista);

    /* Alocamos memória para a lista */
    *lista = malloc(sizeof(ListaE));
    if((*lista) == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a estrutura da lista.\n");
        return 0;
    }

    /* Inicializamos seus atributos */
    (*lista)->cabeca = NULL;
    (*lista)->tamanho = 0;
    return 1;
}


void liberar_lista(ListaE **lista) {
    /* Ignoramos uma lista não inicializada */
    if(*lista == NULL) return;

    ItemE *auxiliar = NULL;
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


int adicionar_item_na_cabeca(ListaE *lista, ItemE **item_criado) {
    /* Alocamos memória para um novo elemento */
    ItemE *item = malloc(sizeof(ItemE));
    if(item == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo item.\n");
        return 0;
    }

    /* Adicionamos o resto da lista na nova cabeça da lista */
    item->proximo = lista->cabeca;
    /* Adicionamos a cabeça à lista */
    lista->cabeca = item;
    lista->tamanho++;

    /* Retornamos o item ao usuário */
    *item_criado = item;
    return 1;
}


int adicionar_item_a_cauda(ListaE *lista, ItemE **item_criado) {
    /* Alocamos memória para um novo elemento */
    ItemE *item = malloc(sizeof(ItemE));
    if(item == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo item.\n");
        return 0;
    }

    item->proximo = NULL;
    /* Adicionamos a nova cauda ao último elemento da lista */
    if(lista->cabeca != NULL) {
        ItemE *auxiliar = lista->cabeca;
        while(1) {
            /* Se encontramos o final da lista, adicionamos o último elemento */
            if(auxiliar->proximo == NULL) {
                /* Adicionamos a lista */
                auxiliar->proximo = item;
                lista->tamanho++;
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
        lista->tamanho++;
        /* Retornamos ao usuário */
        *item_criado = item;
        return 1;
    }
}


int remover_item_sem_liberar(ListaE *lista, int chave, ItemE **item_removido) {
    ItemE *no_atual = lista->cabeca;

    /* Conferimos se o item está no início da lista (caso especial, alteramos
    * lista) */
    if(lista->cabeca->chave == chave) {
        /* Removemos da lista */
        lista->cabeca = lista->cabeca->proximo;
        lista->tamanho--;
        /* Retornamos ao usuário */
        *item_removido = no_atual;
        return 1;
    }

    /* Agora, conferimos se está no meio/fim da lista */
    while(no_atual != NULL) {
        if(no_atual->proximo != NULL && no_atual->proximo->chave == chave) {
            /* Colocamos o item removido no ponteiro dado */
            *item_removido = no_atual->proximo;
            /* Tornamos nulo seu próximo elemento */
            (*item_removido)->proximo = NULL;

            /* Removemos da lista */
            no_atual->proximo = no_atual->proximo->proximo;
            lista->tamanho--;
            return 1;
        }

        no_atual = no_atual->proximo;
    }
    return 0;
}


int remover_item(ListaE *lista, int chave) {
    ItemE *item_removido = NULL;
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
