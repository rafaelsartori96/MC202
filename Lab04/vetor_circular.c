#include <stdio.h>
#include <stdlib.h>
#include "vetor_circular.h"


int iniciar_queue(Queue **queue, int capacidade) {
    limpar_queue(queue);

    /* Conferimos a capacidade inicial */
    if(capacidade <= 0) {
        fprintf(stderr, "Erro: capacidade deve ser maior ou igual a zero.\n");
        return 0;
    }

    /* Inicializamos a queue */
    (*queue) = malloc(sizeof(Queue));
    if((*queue) == NULL) {
        fprintf(stderr, "Erro ao alocar memória dinâmica para a queue.\n");
        return -1;
    }

    /* Inicializamos o vetor da queue */
    (*queue)->vetor = malloc(capacidade * sizeof(int));
    if((*queue)->vetor == NULL) {
        free((*queue));
        (*queue) = NULL;
        fprintf(stderr, "Erro ao alocar memória dinâmica para os itens da"
            " queue.\n");
        return -1;
    }

    /* Inicializamos os atributos da fila */
    (*queue)->capacidade = capacidade;
    (*queue)->inicio = 0;
    (*queue)->tamanho = 0;
    return 1;
}


void limpar_queue(Queue **queue) {
    if((*queue) == NULL)
        return;

    /* Liberar memória alocada para o vetor */
    free((*queue)->vetor);
    free((*queue));
    /* Tornamos NULL o ponteiro */
    (*queue) = NULL;
}


int realocar_vetor(Queue *queue, int nova_capacidade) {
    if(nova_capacidade < queue->tamanho || nova_capacidade <= 0) {
        fprintf(stderr, "Não é possível alterar capacidade para %d quando o"
            " tamanho é %d\n", nova_capacidade, queue->tamanho);
        return 0;
    }

    /* Realocamos um vetor com nova capacidade */
    //int *_vetor = malloc(nova_capacidade * sizeof(int));
    int *_vetor = calloc(nova_capacidade, sizeof(int));
    if(_vetor == NULL) {
        fprintf(stderr, "Erro ao realocar memória para o vetor.");
        return -1;
    }

    {
        /* Atualizamos o novo vetor com os elementos do antigo */
        int i;
        for(i = 0; i < queue->tamanho; i++) {
            /* Recebemos o ponteiro para o i-ésimo elemento */
            int *item = acessar(queue, i);
            if(item == NULL) {
                fprintf(stderr, "Erro ao acessar elemento do vetor\n");
                free(_vetor);
                return -1;
            }

            /* Colocamos o i-ésimo elemento do antigo vetor no novo vetor */
            *(_vetor + i) = (*item);
        }
    }

    /* Substituímos o antigo vetor */
    free(queue->vetor);
    queue->vetor = _vetor;
    queue->inicio = 0;
    queue->capacidade = nova_capacidade;
    return 1;
}


int * acessar(Queue *queue, int posicao) {
    /* Ignoramos posições inválidas, que saem do limite +/- 1 */
    if(posicao > queue->tamanho || posicao < -1)
        return NULL;

    /* Procuramos a partir do início do vetor */
    return (
        queue->vetor +
        ((queue->inicio + posicao + queue->capacidade) % (queue->capacidade))
    );
}


int inserir_no_fim(Queue *queue, int item) {
    /* Conferimos se a queue terá tamanho suficiente para o vetor */
    if((queue->tamanho + 1) >= queue->capacidade &&
            !realocar_vetor(queue, queue->capacidade * FATOR_CRESCIMENTO)) {
        return -1;
    }

    int *posicao_item = acessar(queue, queue->tamanho);
    if(posicao_item == NULL) {
        fprintf(stderr, "Erro ao acessar vetor ao inserir no fim da fila.\n");
        return 0;
    }
    (*posicao_item) = item;
    queue->tamanho++;
    return 1;
}


int inserir_no_topo(Queue *queue, int item) {
    /* Conferimos se a queue terá tamanho suficiente para o vetor */
    if((queue->tamanho + 1) >= queue->capacidade &&
            !realocar_vetor(queue, queue->capacidade * FATOR_CRESCIMENTO)) {
        return -1;
    }

    int *posicao_item = acessar(queue, -1);
    if(posicao_item == NULL) {
        fprintf(stderr, "Erro ao acessar vetor ao inserir no fim da fila.\n");
        return 0;
    }
    (*posicao_item) = item;
    queue->tamanho++;
    queue->inicio--;
    if(queue->inicio < 0)
        queue->inicio += queue->capacidade;
    return 1;
}


int remover_do_topo(Queue *queue, int *item_removido) {
    /* Conferimos se temos o que remover */
    if(queue->tamanho <= 0)
        return 0;

    /* Conferimos se temos que diminuir o tamanho do vetor */
    if(queue->tamanho < (queue->capacidade * DECRESCIMENTO_THRESHOLD) &&
            !realocar_vetor(queue, queue->capacidade * FATOR_DECRESCIMENTO)) {
        /* Como esse erro não prejudica o vetor, apenas anunciamos o erro */
        fprintf(stderr, "Falha ao diminuir o vetor durante remoção!\n");
    }

    /* Tentamos remover o item */
    int *removido = acessar(queue, 0);
    if(removido == NULL)
        return 0;
    else
        *item_removido = *removido;

    /* Passamos o início para frente já que removemos com sucesso */
    queue->inicio++;
    if(queue->inicio >= queue->capacidade)
        queue->inicio -= queue->capacidade;
    queue->tamanho--;
    return 1;
}


int remover_do_fim(Queue *queue, int *item_removido) {
    /* Conferimos se temos o que remover */
    if(queue->tamanho <= 0)
        return 0;

    /* Conferimos se temos que diminuir o tamanho do vetor */
    if(queue->tamanho < (queue->capacidade * DECRESCIMENTO_THRESHOLD) &&
            !realocar_vetor(queue, queue->capacidade * FATOR_DECRESCIMENTO)) {
        /* Como esse erro não prejudica o vetor, apenas anunciamos o erro */
        fprintf(stderr, "Falha ao diminuir o vetor durante remoção!\n");
    }

    /* Tentamos remover o item */
    int *removido = acessar(queue, queue->tamanho - 1);
    if(removido == NULL)
        return 0;
    else
        *item_removido = *removido;

    /* Apenas diminuímos o tamanho pois não precisamos alterar mais nada */
    queue->tamanho--;
    return 1;
}


void imprimir_fila(Queue *queue) {
    printf("Queue = { ");
    int i;
    for(i = 0; i < queue->tamanho; i++) {
        if(i > 0)
            printf(", ");
        printf("%d", *acessar(queue, i));
    }
    printf(" } tamanho = %d\n", queue->tamanho);

    printf("Vetor = { ");
    for(i = 0; i < queue->capacidade; i++) {
        if(i > 0)
            printf(", ");
        printf("%d", *(queue->vetor + i));
    }
    printf(" } capacidade = %d\n", queue->capacidade);
}
