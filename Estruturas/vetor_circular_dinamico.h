#ifndef VETOR_CIRCULAR_DINAMICO_H
#define VETOR_CIRCULAR_DINAMICO_H

/* Definimos o fator de crescimento como 1,4 */
#define FATOR_CRESCIMENTO 2
/* Definimos o fator de decrescimento como 0,6 */
#define FATOR_DECRESCIMENTO 0.5
/* Definimos o threshold para decrescer quando o tamanho do vetor chegar em
* 30% da capacidade */
#define DECRESCIMENTO_THRESHOLD 0.3


typedef struct {
    /** Posição do início do vetor */
    int inicio;
    /** Ponteiro para o vetor completo */
    int *vetor;
    /** Tamanho utilizado do vetor */
    int tamanho;
    /** Capacidade máxima do vetor */
    int capacidade;
} VetorCircularD;


/**
* Esta função inicializa o vetor circular utilizando memória dinãmica com a
* capacidade requisitada.
*
* Retorna   -1  se não foi possível alocar memória,
*            1  se executou perfeitamente.
*/
int iniciar_vetor_circular(VetorCircularD **vetor_circular, int capacidade);

/**
* Esta função libera toda a memória do vetor.
*/
void limpar_vetor_circular(VetorCircularD **vetor_circular);

/**
* Obtém o valor do vetor na posição dada em 'item_requisitado'.
*
* Retorna    0  se o item não pôde ser acessado,
*            1  se o item foi buscado com sucesso.
*/
int obter(VetorCircularD *vetor_circular, int posicao, int *item_requisitado);

/**
* Insere o item no inicio do vetor, realocando se necessário.
*
* Retorna   -1  se não conseguimos realocar o vetor,
*            0  se não conseguimos acessar o vetor,
*            1  se inserimos corretamente.
*/
int inserir_no_inicio(VetorCircularD *vetor_circular, int item);

/**
* Insere o item no final do vetor, realocando se necessário.
*
* Retorna   -1  se não conseguimos realocar o vetor,
*            0  se não conseguimos acessar o vetor,
*            1  se inserimos corretamente.
*/
int inserir_no_fim(VetorCircularD *vetor_circular, int item);

/**
* Remove o item do topo do vetor circular salvando-o em 'item_removido',
* realocando se necessário.
*
* Retorna   -1  se não conseguimos realocar o vetor,
*            0  se não há itens no vetor ou se houve falha ao acessá-lo,
*            1  se removemos um item com sucesso.
*/
int remover_do_inicio(VetorCircularD *vetor_circular, int *item_removido);

/**
* Remove o item do fim do vetor circular salvando-o em 'item_removido',
* realocando se necessário.
*
* Retorna   -1  se não conseguimos realocar o vetor,
*            0  se não há itens no vetor ou se houve falha ao acessá-lo,
*            1  se removemos um item com sucesso.
*/
int remover_do_fim(VetorCircularD *vetor_circular, int *item_removido);


#endif /* VETOR_CIRCULAR_DINAMICO_H */
