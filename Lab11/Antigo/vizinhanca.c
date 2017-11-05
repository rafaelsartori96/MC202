#include <stdlib.h>
#include "vizinhanca.h"


static int min(int a, int b) {
    return a < b ? a : b;
}


static int max(int a, int b) {
    return a > b ? a : b;
}


int inicializar_lista_de_vizinhanca(Vizinhanca **vizinhanca, int vizinhos) {
    /* Verificar se a vizinhança já existe */
    if((*vizinhanca) != NULL) {
        return 0;
    }

    /* Tentamos alocar recursos para a estrutura da vizinhança */
    (*vizinhanca) = malloc(sizeof(Vizinhanca));
    if((*vizinhanca) == NULL) {
        return -1;
    }

    /* Verificamos se o vetor foi inicializado com sucesso */
    (*vizinhanca)->vizinhos = malloc(vizinhos * sizeof(Vizinho *));
    if((*vizinhanca)->vizinhos == NULL) {
        free(*vizinhanca);
        (*vizinhanca) = NULL;
        return -1;
    }

    /* Agora inicializamos os atributos da estrutura */
    (*vizinhanca)->listas = vizinhos;
    return 1;
}


int possui_vizinho(Vizinhanca *vizinhanca, int vertice_a, int vertice_b) {
    int vizinho_desejado = max(vertice_a, vertice_b);

    Vizinho *vizinho = *(vizinhanca->vizinhos + min(vertice_a, vertice_b));
    while(vizinho != NULL) {
        /* Verificamos se o vértice desejado pertence a lista de vizinhos */
        if(vizinho->vertice == vizinho_desejado) {
            return 1;
        }

        /* Procuramos no próximo vizinho */
        vizinho = vizinho->proximo;
    }

    return 0;
}


int criar_vizinhanca(Vizinhanca *vizinhanca, int vertice_a, int vertice_b) {
    int vertice_vizinho = max(vertice_a, vertice_b);
    Vizinho *vizinho = *(vizinhanca->vizinhos + min(vertice_a, vertice_b));

    /* Verificamos se o vizinho já possui essa vizinhança */
    if(vizinho != NULL) {
        if(vizinho->vertice == vertice_vizinho) {
            return 0;
        } else {
            /* Procuramos a vizinhança ou o últimmo vizinho */
            while(vizinho->proximo != NULL) {
                /* Verificamos se o vértice desejado pertence a lista de vizinhos */
                if(vizinho->proximo->vertice == vertice_vizinho) {
                    return 0;
                }

                /* Procuramos no próximo vizinho */
                vizinho = vizinho->proximo;
            }
        }
    }

    /* Se estamos aqui, precisamos criar a vizinhança pois ela não existe */
    Vizinho *vizinho_novo = malloc(sizeof(Vizinho));

    /* Inicializamos seus atributos */
    vizinho_novo->vertice = vertice_vizinho;
    vizinho_novo->proximo = NULL;

    /* Adicionamos vizinho */
    if(vizinho != NULL) {
        vizinho->proximo = vizinho_novo;
    } else {
        *(vizinhanca->vizinhos + min(vertice_a, vertice_b)) = vizinho_novo;
    }

    return 1;
}


void liberar_vizinhanca(Vizinhanca **vizinhanca) {
    /* Verificamos se a vizinhança existe */
    if((*vizinhanca) == NULL) {
        return;
    }

    /* Liberamos recursos */
    int i;
    for(i = 0; i < (*vizinhanca)->listas; i++) {
        Vizinho *vizinho = *((*vizinhanca)->vizinhos + i);

        /* Liberamos todos os vizinhos */
        while(vizinho != NULL) {
            Vizinho *auxiliar = vizinho;
            vizinho = vizinho->proximo;
            free(auxiliar);
        }
    }
    /* Liberamos o vetor */
    free((*vizinhanca)->vizinhos);
    free(*vizinhanca);
    (*vizinhanca) = NULL;
}
