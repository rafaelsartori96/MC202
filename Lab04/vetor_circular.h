#ifndef VETOR_CIRCULAR_H
#define VETOR_CIRCULAR_H

/* Definimos o fator de crescimento como 1,4 */
#define FATOR_CRESCIMENTO 2
/* Definimos o fator de decrescimento como 0,6 */
#define FATOR_DECRESCIMENTO 0.5
/* Definimos o threshold para decrescer quando o tamanho do vetor chegar em
* 30% da capacidade */
#define DECRESCIMENTO_THRESHOLD 0.3


typedef struct Queue {
    /** Ponteiro para a queue */
    int inicio;
    /** Ponteiro para o vetor completo */
    int *vetor;
    /** Tamanho utilizado do vetor */
    int tamanho;
    /** Capacidade máxima do vetor */
    int capacidade;
} Queue;


/**
* Esta função inicializa a queue utilizando memória dinãmica com a capacidade
* dada.
*
* Retorna   -1  se não foi possível alocar memória,
*            1  se executou perfeitamente.
*/
int iniciar_queue(Queue **queue, int capacidade);

/**
* Esta função libera toda a memória da fila.
*/
void limpar_queue(Queue **queue);

/**
* Retorna um ponteiro para o item na posição requisitada.
*
* Retorna    NULL   se o item não existe na lista.
*/
int * acessar(Queue *queue, int posicao);

/**
* Insere o item no inicio da fila, realocando se necessário.
*
* Retorna   -1  se não conseguimos realocar o vetor,
*            0  se não conseguimos acessar o vetor,
*            1  se inserimos corretamente.
*/
int inserir_no_topo(Queue *queue, int item);

/**
* Insere o item no final da fila, realocando se necessário.
*
* Retorna   -1  se não conseguimos realocar o vetor,
*            0  se não conseguimos acessar o vetor,
*            1  se inserimos corretamente.
*/
int inserir_no_fim(Queue *queue, int item);

/**
* Remove o item do topo da fila salvando-o em 'item_removido', realocando se
* necessário.
*
* Retorna   -1  se não conseguimos realocar o vetor,
*            0  se não há itens na fila ou se houve falha ao acessá-lo,
*            1  se removemos um item com sucesso.
*/
int remover_do_topo(Queue *queue, int *item_removido);

/**
* Remove o item do fim da fila salvando-o em 'item_removido', realocando se
* necessário.
*
* Retorna   -1  se não conseguimos realocar o vetor,
*            0  se não há itens na fila ou se houve falha ao acessá-lo,
*            1  se removemos um item com sucesso.
*/
int remover_do_fim(Queue *queue, int *item_removido);

/**
* Esta função realoca o tamanho do vetor da fila para nova_capacidade, que deve
* ser no mínimo o mínimo entre 1 e o tamanho atual da fila.
*
* Retorna   -1  se não conseguimos alocar ou acessar a memória do vetor,
*            1  se conseguimos realocar o vetor.
*/
int realocar_vetor(Queue *queue, int nova_capacidade);

/**
* Esta função imprime o estado atual da fila.
*/
void imprimir_fila(Queue *queue);


#endif /* VETOR_CIRCULAR_H */
