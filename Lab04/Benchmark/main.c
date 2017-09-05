#include <stdio.h>
#include <stdlib.h>

void imprimir(int *vetor, int inicio, int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        printf("%d, ", *(vetor + inicio + i));
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);
    int *vetor = malloc(2 * n * sizeof(int));
    int inicio = 0;

    for(int i = 0; i < n; i++) {
        *(vetor + i) = i + 1;
    }

    int tamanho = n;

    while(tamanho > 1) {
        // Removemos o primeiro
        inicio++;
        tamanho--;
        // Movemos o segundo do início para o fim (o tamanho se mantém)
        *(vetor + inicio + tamanho) = *(vetor + inicio);
        inicio++;
        // imprimir(vetor, inicio, tamanho);
    }

    printf("%d\n", *(vetor + inicio));
    free(vetor);
}
