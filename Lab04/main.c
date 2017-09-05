#include <stdio.h>
#include "vetor_circular.h"


int main() {
    while(1) {
        /** Número de cartas */
        int n;
        scanf("%d", &n);

        /* Terminamos caso recebemos 0 */
        if(n == 0) {
            return 0;
        } else if(n < 0) {
            fprintf(stderr, "Input incorreto! n < 0!\n");
            return -1;
        }

        /* Inicializamos a fila */
        Queue *queue = NULL;
        if(!iniciar_queue(&queue, n))
            return -1;

        /* Inserimos no final da fila todos os números */
        {
            int i;
            for(i = 1; i <= n; i++) {
                inserir_no_fim(queue, i);
            }
        }

        /* Agora fazemos o algoritmo do jogo:
        * Enquanto houver pelo menos duas cartas, retire a carta que está no
        * topo do baralho, descarte-a e coloque a carta seguinte no fundo do
        * baralho. */
        printf("Cartas jogadas:");
        int primeira = 1;
        int descarte;
        while(queue->tamanho > 1) {
            /* Removemos a primeira carta do baralho */
            if(!remover_do_topo(queue, &descarte)) {
                fprintf(stderr, "Ocorreu um erro durante a remoção!\n");
                limpar_queue(&queue);
                return -1;
            }

            /* Imprimimos seu número */
            if(!primeira)
                printf(",");
            else
                primeira = 0;

            printf(" %d", descarte);

            /* Passamos a "segunda" para o fundo */
            if(!remover_do_topo(queue, &descarte) ||
                    !inserir_no_fim(queue, descarte)) {
                fprintf(stderr, "Ocorreu um erro durante o transporte para o "
                    "fim.\n");
                limpar_queue(&queue);
                return -1;
            }
        }

        /* Imprimimos a carta restante */
        if(!remover_do_topo(queue, &descarte)) {
            fprintf(stderr, "Ocorreu um erro durante a última remoção!\n");
            limpar_queue(&queue);
            return -1;
        }
        printf("\nCarta restante: %d\n", descarte);
        limpar_queue(&queue);
    }
}
