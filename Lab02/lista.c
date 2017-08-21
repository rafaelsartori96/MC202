#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


int adicionar_item_no_topo(Item **lista, int chave) {
    Item *item = malloc(sizeof(Item));
    if(item == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo item.\n");
        return 0;
    }

    item->chave = chave;
    item->contador = 0;
    // Adicionamos o resto da lista na nova cabeça da lista
    item->proximo = *lista;
    // Adicionamos a cabeça à lista
    *lista = item;
    return 1;
}

int adicionar_item_no_fim(Item **lista, int chave) {
    Item *item = malloc(sizeof(Item));
    if(item == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo item.\n");
        return 0;
    }

    item->chave = chave;
    item->contador = 0;
    item->proximo = NULL;
    // Adicionamos a cauda no último elemento da lista
    if(*lista != NULL) {
        Item *auxiliar = *lista;
        while(1) {
            // Se encontramos o final da lista, adicionamos o último elemento
            if(auxiliar->proximo == NULL) {
                auxiliar->proximo = item;
                return 1;
            } else {
                auxiliar = auxiliar->proximo;
            }
        }
    } else {
        // Se a lista estiver vazia, simplesmente adicionamos item
        *lista = item;
        return 1;
    }
}

int remover_item(Item **lista, Item **removido, int chave) {
    Item *no_atual = *lista;

    // Conferimos se o item está no início da lista (caso especial, alteramos
    // lista)
    if((*lista)->chave == chave) {
        *lista = (*lista)->proximo;
        return 1;
    }

    // Agora, conferimos se está no meio/fim da lista
    while(no_atual != NULL) {
        if(no_atual->proximo != NULL && no_atual->proximo->chave == chave) {
            // Colocamos o item removido
            *removido = no_atual->proximo;
            // Removemos da lista
            no_atual->proximo = no_atual->proximo->proximo;
            // Para manter-mos o item isolado, tornamos nulo seu próximo elemen-
            // to
            (*removido)->proximo = NULL;
            return 1;
        }

        no_atual = no_atual->proximo;
    }
    return 0;
}

void liberar_lista(Item **lista) {
    Item *auxiliar = NULL;

    while(*lista != NULL) {
        auxiliar = *lista;
        *lista = (*lista)->proximo; // parará a iteração quando a lista acabar
        free(auxiliar);
    }

    *lista = NULL;
}

void imprimir_lista(Item *lista) {
    printf("Lista = {");
    while(lista != NULL) {
        printf("%d", lista->chave);
        if(lista->proximo != NULL)
            printf(", ");
        lista = lista->proximo;
    }
    printf("};\n");
}
