/**
 * Rafael Sartori Martins dos Santos (RA: 186154)
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double square(double d) {
    return d * d;
}

int main() {
    /*
     * Apesar de eu odiar por não ser seguro, o testador exige que eu defina
     * antes dos laços.
     */
    int i, j;

    // Recebemos a ordem da matriz, que é o número de linhas que precisamos.
    int n;
    scanf("%d", &n);

    // Criamos o vetor base
    double **matriz = malloc(n * sizeof(double *));
    // Checamos a alocação
    if(matriz == NULL) {
        printf("Erro ao alocar memória dinâmica para a base da matriz.\n");
        return -1;
    }

    /*
     * Para cada linha i [0..n - 1] da matriz, criamos o vetor com i + 1 [0..i]
     * elementos. Lemos, então, os i + 1 elementos da entrada [0..i], guardando
     * sua soma em uma variável que, posteriormente, será usada para cálculo da
     * soma e desvio padrão.
     */
    double media = 0.0;
    for(i = 0; i < n; i++) {
        *(matriz + i) = malloc((i + 1) * sizeof(double));

        // Checamos a alocação
        if(*(matriz + i) == NULL) {
            printf("Erro ao alocar memória dinâmica para a linha %d da matriz.\n", i);
            for(j = 0; j < i; j++)
                free(*(matriz + j));
            free(matriz);
            return -2;
        }

        // Recebemos a entrada nesta linha da matriz e adicionamos a soma dos
        // elementos da matriz para cálculo da média
        for(j = 0; j <= i; j++) {
            scanf("%lf", *(matriz + i) + j);
            media += *(*(matriz + i) + j);
        }
    }

    media /= ((n * (n + 1)) / 2.0); // o número de itens é (n * (n + 1)) / 2

    /*
     * Calcularemos o desvio padrão (assumo populacional, que é aquele cujo
     * denominador é N e não N - 1): sqrt( sum(x - avg) / N )
     */
    double desvio_padrao = 0.0;
    // Calcularemos sum(x - avg)
    for(i = 0; i < n; i++) {
        for(j = 0; j <= i; j++) {
            desvio_padrao += square(*(*(matriz + i) + j) - media);
        }
    }
    // Dividiremos pelo número N de elementos
    desvio_padrao /= ((n * (n + 1)) / 2.0);
    // Fazemos a raiz quadrada
    desvio_padrao = sqrt(desvio_padrao);

    /*
     * Agora, alteraremos a matriz usando a fórmula x = (x - avg) / dp,
     * onde dp é o desvio padrão, avg, média, e x, elemento da matriz.
     */
    for(i = 0; i < n; i++) {
        for(j = 0; j <= i; j++) {
            *(*(matriz + i) + j) = (*(*(matriz + i) + j) - media) / desvio_padrao;
        }
    }

    /*
     * Agora, imprimimos a saída esperada:
     * matriz
     * média desvio_padrao
     */

    for(i = 0; i < n; i++) {
        for(j = 0; j <= i; j++) {
            printf("%.12lf ", *(*(matriz + i) + j));
        }
        printf("\n");
    }
    printf("\n%.12lf %.12lf \n", media, desvio_padrao);

    return 0;
}
