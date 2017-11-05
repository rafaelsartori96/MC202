#include <stdlib.h>
#include <string.h>
#include "lab11.h"
#include "vetor_circular.h"


/**
* Verifica se as duas palavras estão a um passo de edição.
*
* Returna   0   caso as palavras não estejam a um passo de edição,
*           1   caso estejam.
*/
int passo_de_edicao(char *palavra_1, char *palavra_2);

/**
* Executa a busca em largura a partir do vértice inicial.
*
* Retorna   -1  caso não tenha sido possível inicializar as estruturas de dados
*               auxiliares,
*            x  a distância entre o vértice inicial e o vértice mais distante.
*/
int busca_em_largura(Grafo *grafo, int vertice_inicial);


int inicializar_grafo(Grafo **grafo) {
    /* Verifica se o grafo foi inicializado */
    if((*grafo) != NULL) {
        return 0;
    }

    /* Aloca recursos para o grafo */
    (*grafo) = malloc(sizeof(Grafo));
    if((*grafo) == NULL) {
        return -1;
    }

    /* Inicializa a estrutura de vizinhança */
    (*grafo)->vizinhanca = NULL;
    if(inicializar_lista_de_vizinhanca(
        &(*grafo)->vizinhanca, TAMANHO_MAXIMO
    ) != 1) {
        free(*grafo);
        (*grafo) = NULL;
        return -2;
    }

    /* Aloca recursos para os vértices do grafo */
    (*grafo)->vertices = malloc(TAMANHO_MAXIMO * sizeof(Vertice));
    if((*grafo)->vertices == NULL) {
        liberar_vizinhanca(&(*grafo)->vizinhanca);
        free(*grafo);
        (*grafo) = NULL;
        return -1;
    }

    /* Inicializamos as variáveis */
    (*grafo)->capacidade_vertices = TAMANHO_MAXIMO;
    (*grafo)->numero_vertices = 0;

    return 1;
}


void adiciona_vertice(Grafo *grafo, char *palavra_nova) {
    /* Assumimos que a palavra não existe no vetor e criamos vértice */
    int posicao_nova = grafo->numero_vertices;
    Vertice *vertice_novo = (grafo->vertices + posicao_nova);

    /* Inicializamos o vértice criado */
    vertice_novo->palavra = palavra_nova;

    /* Verificamos se a palavra muda em 1 caractere dos outros vértices, isto é,
    * procuramos vizinhos */
    int posicao_vizinho;
    for(
        posicao_vizinho = 0;
        posicao_vizinho < grafo->numero_vertices;
        posicao_vizinho++
    ) {
        Vertice *vertice_vizinho = (grafo->vertices + posicao_vizinho);

        /* Ignoramos palavras que não estão a um passo de edição */
        if(passo_de_edicao(vertice_vizinho->palavra, palavra_nova) != 1) {
            continue;
        }

        /* Adicionamos o vizinho */
        criar_vizinhanca(grafo->vizinhanca, posicao_nova, posicao_vizinho);
    }

    /* Adicionamos o vértice criado */
    (grafo->numero_vertices)++;
}


int maior_distancia(Grafo *grafo) {
    int maior_distancia = 0;

    int i;
    for(i = 0; i < grafo->numero_vertices; i++) {
        /* Fazemos brute-force para descobrir a maior menor distância entre 2
        * palavras */
        int distancia = busca_em_largura(grafo, i);

        if(distancia < 0) {
            return -1;
        } else if(distancia > maior_distancia) {
            maior_distancia = distancia;
        }
    }

    return maior_distancia;
}


void liberar_grafo(Grafo **grafo) {
    /* Verificamos se o grafo existe */
    if((*grafo) == NULL) {
        return;
    }

    /* Liberamos a memória alocada para as arestas */
    liberar_vizinhanca(&(*grafo)->vizinhanca);

    /* Liberamos a memória alocada para os vértices */
    {
        Vertice *vertice;
        int i;
        for(i = 0; i < (*grafo)->numero_vertices; i++) {
            vertice = ((*grafo)->vertices + i);

            /* Liberamos a palavra de cada vértice */
            free(vertice->palavra);
        }
        free((*grafo)->vertices);
    }

    /* Finalmente, liberamos o grafo */
    free(*grafo);
    (*grafo) = NULL;
}


int busca_em_largura(Grafo *grafo, int vertice_inicial) {
    /* Marcamos os vértices como não visitados */
    int i;
    for(i = 0; i < grafo->numero_vertices; i++) {
        (grafo->vertices + i)->visitado = 0;
    }

    /* Criamos a fila da busca em largura */
    VetorCircular *fila = NULL;
    if(inicializar_vetor_circular(&fila) != 1) {
        return -1;
    }

    int menor_distancia = 0;

    /* Adicionamos o item inicial a fila "a visitar" com distância zero. */
    insere_valor_fim(fila, vertice_inicial);
    (grafo->vertices + vertice_inicial)->distancia = 0;

    /* Enquanto temos vértices para visitar... */
    while(fila->tamanho > 0) {
        /* Definimos variáveis para o vértice atual */
        int posicao_vertice;
        remove_inicio(fila, &posicao_vertice);
        Vertice *vertice = (grafo->vertices + posicao_vertice);

        /* Visitamos o vértice atual */
        vertice->visitado = 1;

        /* Atualizamos a maior "menor distância" (este algoritmo busca a menor
        * distância entre dois vértices) */
        if(vertice->distancia > menor_distancia) {
            menor_distancia = vertice->distancia;
        }

        /* Para a linha do vértice atual, conferimos seus vizinhos */
        for(int vizinho = 0; vizinho < grafo->numero_vertices; vizinho++) {
            /* Verificamos se o vértice tem vizinho */
            if(!possui_vizinho(grafo->vizinhanca, posicao_vertice, vizinho)) {
                continue;
            }

            /* Verificamos se o vértice já foi visitado */
            if((grafo->vertices + vizinho)->visitado == 1) {
                continue;
            }

            /* Verificamos se o vértice será visitado */
            if(pertence(fila, vizinho)) {
                continue;
            }

            /* Se é vizinho não visitado, adicionamos sua posição à fila */
            insere_valor_fim(fila, vizinho);
            (grafo->vertices + vizinho)->distancia = vertice->distancia + 1;
        }
    }

    /* Liberar memória para a fila */
    liberar_vetor_circular(&fila);

    return menor_distancia;
}


int passo_de_edicao(char *palavra_1, char *palavra_2) {
    /* Verificamos se as palavras possuem tamanho diferente */
    if(strlen(palavra_1) != strlen(palavra_2)) {
        return 0;
    }

    int edicoes = 0;
    int indice = 0;

    while(edicoes <= 1) {
        char caractere_1 = *(palavra_1 + indice);
        char caractere_2 = *(palavra_2 + indice);

        /* Verificamos se as letras são diferentes e se fizemos mais edições do
        * que devíamos */
        if(caractere_1 != caractere_2 && (++edicoes) > 1) {
            return 0;
        }

        /* Terminamos se os caracteres são nulos */
        if(caractere_1 == '\0' || caractere_2 == '\0') {
            return 1;
        }

        indice++;
    }

    /* Apenas para evitar avisos de compilação... */
    return 0;
}
