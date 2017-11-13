/* Rafael Sartori Martins dos Santos (186154) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* O vetor deve possuir DIMENSAO 3 */
#include "vetor.h"
#include "lab12.h"
#include "matriz_binaria.h"
#include "conjuntos.h"


/** Retorna x * x, ou x^2 */
static inline int quadrado(int x) {
    return x * x;
}


/** Retorna x * x, ou x^2 */
static inline double dquadrado(double x) {
    return x * x;
}


/** Calcula a distância entre 2 asteróides no tempo dado t */
static inline void calcular_distancia(DiferencaAsteroide *dif, double t) {
    dif->distancia = (double) comprimento_quadrado(&(dif->posicao)) +
        (double) comprimento_quadrado(&(dif->velocidade)) * dquadrado(t) +
        (double) produto_interno(&(dif->posicao), &(dif->velocidade)) * t * 2;
}


/** Resolve equação do segundo grau a*x^2 + b * x + c, retorna o número de
* raízes maiores do que zero e as raízes nos ponteiros t1 e t2 */
static inline int resolver_segundo_grau(
    double a, double b, double c, double *t1, double *t2
) {
    if(a == 0 && b == 0) {
        /* Não há raízes ou todos os tempos são raízes, ignoramos */
        return 0;
    } else if(a == 0) {
        /* Trata-se de uma reta y = b * t + c, obtemos sua raiz com
        * -c / b */
        double t = (((double) c * (-1.0)) / ((double) b));

        if(t > 0.0) {
            *t1 = t;
            return 1;
        } else {
            return 0;
        }
    } else {
        /** Discriminante (delta) */
        int d = quadrado(b) - 4 * a * c;

        /* Ignoramos raízes que não existem ou não mudam a resposta */
        if(d <= 0) {
            return 0;
        }

        double t1_, t2_;
        {
            /* Guardamos em variáveis convenientes para re-uso */
            double _2a = (double) a * 2.0;
            double sqrtd = sqrt((double) d);
            t1_ = ((b * (-1.0)) + sqrtd) / _2a;
            t2_ = ((b * (-1.0)) - sqrtd) / _2a;
        }

        /* Verificamos se é uma raiz válida */
        if(t1_ > 0.0 && t2_ > 0.0) {
            *t1 = t1_;
            *t2 = t2_;
            return 2;
        } else if(t1_ > 0.0) {
            *t1 = t1_;
            return 1;
        } else if(t2_ > 0.0) {
            *t1 = t2_;
            return 1;
        } else {
            return 0;
        }
    }
}


static inline void calcular_interseccao(
    MatrizDiferenca *matriz_dif,
    DiferencaAsteroide *asteroide_0,
    int linha_asteroide_1, int coluna_asteroide_1,
    MatrizBinaria *interseccoes,
    Instante *instantes
) {
    /* Pulamos o mesmo item */
    if(linha_asteroide_1 == asteroide_0->linha &&
        coluna_asteroide_1 == asteroide_0->coluna) {
        return;
    }

    DiferencaAsteroide *asteroide_1 = buscar(
        matriz_dif,
        linha_asteroide_1,
        coluna_asteroide_1
    );

    /* Ignoramos explicitamente (coordenadas mudam pela matriz simétrica) o
    * mesmo item */
    if(asteroide_0->indice == asteroide_1->indice) {
        return;
    }

    /* Conferimos se a intersecção já foi calculada */
    if(recebe_bit_(
        interseccoes, asteroide_0->indice, asteroide_1->indice
    ) == 1) {
        // printf(
        //     "Ignorando #%d e #%d\n",
        //     asteroide_0->indice, asteroide_1->indice
        // );
        return;
    }
    // printf(
    //     "Calculando #%d e #%d\n", asteroide_0->indice, asteroide_1->indice
    // );

    /* Marcamos a instersecção como calculada */
    define_bit_verdadeiro_(
        interseccoes, asteroide_0->indice, asteroide_1->indice
    );

    /** Coeficiente de t^2 */
    int a = comprimento_quadrado(&(asteroide_0->velocidade)) -
        comprimento_quadrado(&(asteroide_1->velocidade));

    /** Coeficiente de t */
    int b = 2 * (produto_interno(
        &(asteroide_0->posicao), &(asteroide_0->velocidade)
    ) - produto_interno(
        &(asteroide_1->posicao), &(asteroide_1->velocidade)
    ));

    /** Termo independente */
    int c = comprimento_quadrado(&(asteroide_0->posicao)) -
        comprimento_quadrado(&(asteroide_1->posicao));

    double t1, t2;
    int raizes = resolver_segundo_grau(a, b, c, &t1, &t2);
    if(raizes == 2) {
        inserir_ordenado(
            instantes, t1, asteroide_0->indice, asteroide_1->indice
        );
        inserir_ordenado(
            instantes, t2, asteroide_0->indice, asteroide_1->indice
        );
    } else if(raizes == 1) {
        inserir_ordenado(
            instantes, t1, asteroide_0->indice, asteroide_1->indice
        );
    }
}


static void quicksort_np(DiferencaAsteroide *vector, int start, int end) {
    int i = start, j = end, middle = ((i + j) >> 1);
    double pivot = (vector + middle)->distancia;

    do {
        while((vector + i)->distancia < pivot) i++;
        while((vector + j)->distancia > pivot) j--;

        if(i <= j) {
            DiferencaAsteroide auxiliary = *(vector + i);
            *(vector + i) = *(vector + j);
            *(vector + j) = auxiliary;
            i++;
            j--;
        }
    } while(j > i);

    if(start < j) quicksort_np(vector, start, j);
    if(i < end) quicksort_np(vector, i, end);
}


int main() {
    int num_asteroides;
    scanf("%d\n", &num_asteroides);

    /* Alocamos memória para os asteroides */
    Asteroide *asteroides = malloc(num_asteroides * sizeof(Asteroide));
    if(asteroides == NULL) {
        fprintf(
            stderr,
            "Falha ao alocar memória para o vetor de asteróides.\n"
        );
        return -1;
    }

    /* Recebemos os dados de cada asteróide. Inicializamos os vetores de
    * diferença, usado no cálculo das distâncias */
    for(int indice = 0; indice < num_asteroides; indice++) {
        Asteroide *asteroide = (asteroides + indice);

        /* Lemos cada asteroide */
        scanf(
            "%d %d %d %d %d %d\n",
            /* Lemos as coordenadas da posição inicial */
            &(asteroide->posicao_inicial.coordenadas[0]),
            &(asteroide->posicao_inicial.coordenadas[1]),
            &(asteroide->posicao_inicial.coordenadas[2]),
            /* Lemos as componentes da velocidade do vetor */
            &(asteroide->velocidade.coordenadas[0]),
            &(asteroide->velocidade.coordenadas[1]),
            &(asteroide->velocidade.coordenadas[2])
        );
    }

    /* Criamos uma matriz de distancias de asteróides simétrica */
    MatrizDiferenca matriz_dif;
    /** Número de combinações de asteróides */
    int combinacoes = ((num_asteroides * (num_asteroides - 1)) / 2);
    /* Alocamos memória para a matriz linearizada de distancias entre os
    * asteróides */
    matriz_dif.vetor = malloc(combinacoes * sizeof(DiferencaAsteroide));
    if(matriz_dif.vetor == NULL) {
        fprintf(
            stderr,
            "Falha ao alocar memória para as distâncias entre os asteróides.\n"
        );
        free(asteroides);
        return -1;
    }
    /* Definimos previamente os índices da matriz linearizada */
    for(int indice = 0; indice < combinacoes; indice++) {
        (matriz_dif.vetor + indice)->indice = indice;
    }

    /* Preenchemos as distâncias para cada combinação de asteróide */
    for(int linha = 1; linha < num_asteroides; linha++) {
        Asteroide *ast_linha = (asteroides + linha);

        /* Para cada outro asteroide, calculamos os vetores de diferença */
        for(int coluna = 0; coluna < (num_asteroides - 1); coluna++) {
            Asteroide *ast_coluna = (asteroides + coluna);

            /* Calculamos a estrutura de distância entre esses dois
            * asteróides */

            /** Diferença entre asteroide linha e coluna */
            DiferencaAsteroide *diferenca_ast = buscar(
                &matriz_dif, linha, coluna
            );

            /* Criamos os vetores de diferença para posição e velocidade */
            diferenca(
                &(diferenca_ast->posicao),
                &(ast_linha->posicao_inicial), &(ast_coluna->posicao_inicial)
            );
            diferenca(
                &(diferenca_ast->velocidade),
                &(ast_linha->velocidade), &(ast_coluna->velocidade)
            );

            /* Inicializamos as coordenadas na matriz (indice linearizado já
            * foi inicializado) */
            diferenca_ast->linha = linha;
            diferenca_ast->coluna = coluna;
        }
    }

    /** Lista de instantes de tempo */
    Instante *instantes = malloc(sizeof(Instante));
    instantes->t = 0.0;
    instantes->proximo = NULL;

    {
        MatrizBinaria *interseccoes = NULL;
        if(inicializar_matriz_binaria(&interseccoes, combinacoes) != 1) {
            fprintf(
                stderr,
                "Falha ao alocar memória ao vetor de bits de combinações.\n"
            );
            liberar_lista(instantes);
            free(matriz_dif.vetor);
            free(asteroides);
            return -1;
        }

        /* Calculamos os instantes das colisões de distâncias para cada par
        * que contém os dois indices da função de distância */
        for(int indice = 0; indice < (combinacoes / 2) + 1; indice++) {
            DiferencaAsteroide *asteroide_0 = (matriz_dif.vetor + indice);
            int linha   = asteroide_0->linha,
                coluna  = asteroide_0->coluna;

            /* Pegamos todas as diferenças da mesma coluna que a linha */
            for(int linha_ = 1; linha_ < num_asteroides; linha_++) {
                calcular_interseccao(
                    &matriz_dif,
                    /* Asteroide que será comparado */
                    asteroide_0,
                    /* O par que vamos intersectar asteroide_0 */
                    linha_, coluna,
                    /* As intersecções já feitas */
                    interseccoes,
                    /* A lista de tempos */
                    instantes
                );
            }

            /* Pegamos todas as diferenças da mesma linha que a linha */
            for(int coluna_ = 0; coluna_ < linha; coluna_++) {
                calcular_interseccao(
                    &matriz_dif,
                    asteroide_0,
                    linha, coluna_,
                    interseccoes,
                    instantes
                );
            }
        }

        liberar_matriz_binaria(&interseccoes);
    }

    {
        Instante *instante_0 = instantes;
        Instante *instante_1 = instante_0->proximo;

        while(instante_1 != NULL) {
            /* Excluímos tempos irrelevantes ou duplicates */
            if(fabs(instante_1->t - instante_0->t) < 1.0e-6) {
                Instante *auxiliar = instante_1;
                instante_0->proximo = instante_1->proximo;
                instante_1 = instante_1->proximo;
                free(auxiliar);
            } else {
                /* Fazemos o mesmo para o próximo */
                instante_0 = instante_1;
                instante_1 = instante_1->proximo;
            }

            // /* Verificamos se precisamos inserir o último tempo */
            // if(instante_1 == NULL &&
            //     inserir_ordenado(instantes, 2.0 * instante_0->t) < 0) {
            //     fprintf(
            //         stderr,
            //         "Falha ao alocar memória para o último instante de "
            //         "tempo.\n"
            //     );
            //     liberar_lista(instantes);
            //     free(matriz_dif.vetor);
            //     free(asteroides);
            //     return -1;
            // }
        }
    }

    /* Fazemos as simulações da árvore geradora mínima */
    {
        int mudancas = 0;

        Instante     *instante_0 = instantes;
        Conjuntos    *vertices = NULL;
        VetorBinario *vertices_incluidos = NULL;
        VetorBinario *arestas_0 = NULL;
        VetorBinario *arestas_1 = NULL;

        /* Inicializamos o conjunto */
        inicializar_conjuntos(&vertices, num_asteroides);
        /* Inicializamos os vetores binários */
        inicializar_vetor_binario(&vertices_incluidos, num_asteroides);
        inicializar_vetor_binario(&arestas_0, combinacoes);
        inicializar_vetor_binario(&arestas_1, combinacoes);

        /* Simulamos as árvores geradoras */
        while(instante_0 != NULL) {
            // double t = (instante_0->t + instante_1->t) / 2.0;
            double t = instante_0->t + 0.5e-6;
            // printf(
            //     "\n\nt0 = %.7lf => t = %.7lf (aresta #%d: %d <=> %d e "
            //     "aresta #%d: %d <=> %d)\n",
            //     instante_0->t, t,
            //     instante_0->arestas[0],
            //     (matriz_dif.vetor + (instante_0->arestas[0]))->linha,
            //     (matriz_dif.vetor + (instante_0->arestas[0]))->coluna,
            //     instante_0->arestas[1],
            //     (matriz_dif.vetor + (instante_0->arestas[1]))->linha,
            //     (matriz_dif.vetor + (instante_0->arestas[1]))->coluna
            // );

            /* Calculamos a distância para todas as diferenças */
            for(int indice = 0; indice < combinacoes; indice++) {
                calcular_distancia(matriz_dif.vetor + indice, t);
            }

            /* Ordenamos o vetor de combinações */
            quicksort_np(matriz_dif.vetor, 0, combinacoes - 1);

            /* Inserimos as menores arestas */
            for(int indice = 0; indice < combinacoes; indice++) {
                DiferencaAsteroide *aresta = (matriz_dif.vetor + indice);
                int inserido = 0;

                /* Inserimos o asteroide */
                int repr_linha = representante(vertices, aresta->linha);
                int repr_coluna = representante(vertices, aresta->coluna);
                // printf(
                //     "representante de linha %d = %d, da coluna %d, é %d\n",
                //     aresta->linha, repr_linha,
                //     aresta->coluna, repr_coluna
                // );
                if(repr_coluna != repr_linha) {
                    uniao(vertices, aresta->linha, aresta->coluna);
                    inserido = 1;
                } else {
                    continue;
                }

                // printf(
                //     "inserida %d aresta #%d (%d <=> %d), distancia = %f\n",
                //     inserido, aresta->indice, aresta->linha, aresta->coluna,
                //     aresta->distancia
                // );

                /* Se havia algum vértice não inserido, inserimos */
                if(inserido != 0) {
                    define_bit_verdadeiro(vertices_incluidos, aresta->linha);
                    define_bit_verdadeiro(vertices_incluidos, aresta->coluna);
                    define_bit_verdadeiro(arestas_1, aresta->indice);
                }
            }

            /* Vemos se é diferente do vetor anterior */
            for(int byte = 0; byte < arestas_0->bytes; byte++) {
                char byte_0 = *(arestas_0->bits + byte);
                char byte_1 = *(arestas_1->bits + byte);

                /* Conferimos se os bytes são diferentes através da operação
                * binária AND. */
                // printf(
                //     "%d != %d? usamos %d (byte_0 & byte_1) e %d"
                //     " (byte_0 | byte_1)\n",
                //     byte_0, byte_1, (byte_0 & byte_1), (byte_0 | byte_1)
                // );
                if((byte_0 & byte_1) != (byte_0 | byte_1)) {
                    // printf("Reconhecemos uma mudança!\n");
                    mudancas++;
                    /* Saímos do loop de comparação de bytes */
                    break;
                }
            }

            /* Passamos para o próximo tempo */
            instantes = instantes->proximo;
            free(instante_0);
            instante_0 = instantes;

            /* Limpamos os conjuntos de vértices */
            limpar_conjuntos(vertices);
            limpar_vetor_binario(vertices_incluidos);
            /* Passamos o conjunto de arestas do tempo atual (t = "1") para o
            * tempo anterior (t = "0", isto é, ele se tornará "antigo") */
            copiar_vetor_binario(arestas_1, arestas_0);
            limpar_vetor_binario(arestas_1);
        }

        /* Liberamos os conjuntos */
        liberar_conjuntos(&vertices);
        /* Liberamos os vetores binários */
        liberar_vetor_binario(&vertices_incluidos);
        liberar_vetor_binario(&arestas_0);
        liberar_vetor_binario(&arestas_1);

        /* Imprimimos a resposta */
        printf("%d\n", mudancas);
    }

    /* Liberamos os recursos alocados */
    liberar_lista(instantes);
    free(matriz_dif.vetor);
    free(asteroides);

    return 0;
}
