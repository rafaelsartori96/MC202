#include <stdio.h>
#include <stdlib.h>
#include "vetor_circular_dinamico.h"


/**
* Retorna um ponteiro para o item na posição requisitada, podendo editá-lo.
*
* Retorna    NULL   se o item não existe na lista.
*
* Nota: esta função não está declarada na biblioteca "vetor_circular_dinamico.h"
*/
int * acessar(VetorCircularD *vetor_circular, int posicao);


/**
* Esta função realoca o tamanho do vetor para nova_capacidade, que deve ser no
* mínimo o mínimo entre 1 e o número de elementos válidos do vetor.
*
* Retorna   -1  se não conseguimos alocar ou acessar a memória do vetor,
*            1  se conseguimos realocar o vetor.
*
* Nota: esta função não está declarada na biblioteca "vetor_circular_dinamico.h"
*/
int realocar_vetor(VetorCircularD *vetor_circular, int nova_capacidade);


int iniciar_vetor_circular(VetorCircularD **vet_circ, int capacidade) {
    limpar_vetor_circular(vet_circ);

    /* Conferimos a capacidade inicial */
    if(capacidade <= 0) {
        fprintf(stderr, "Erro: capacidade deve ser maior ou igual a zero.\n");
        return 0;
    }

    /* Inicializamos o vetor circular */
    (*vet_circ) = malloc(sizeof(VetorCircularD));
    if((*vet_circ) == NULL) {
        fprintf(stderr, "Erro ao alocar memória dinâmica para o vetor circular.\n");
        return -1;
    }

    /* Inicializamos o vetor do VetorCircularD */
    (*vet_circ)->vetor = malloc(capacidade * sizeof(int));
    if((*vet_circ)->vetor == NULL) {
        free((*vet_circ));
        (*vet_circ) = NULL;
        fprintf(stderr, "Erro ao alocar memória dinâmica para os itens do"
            " vetor circular.\n");
        return -1;
    }

    /* Inicializamos os atributos do vetor */
    (*vet_circ)->capacidade = capacidade;
    (*vet_circ)->inicio = 0;
    (*vet_circ)->tamanho = 0;
    return 1;
}


void limpar_vetor_circular(VetorCircularD **vet_circ) {
    if((*vet_circ) == NULL)
        return;

    /* Liberar memória alocada para o vetor */
    free((*vet_circ)->vetor);
    free((*vet_circ));
    /* Tornamos NULL o ponteiro */
    (*vet_circ) = NULL;
}


int inserir_no_fim(VetorCircularD *vet_circ, int item) {
    /* Conferimos se a vet_circ terá tamanho suficiente para o vetor */
    if(
        (vet_circ->tamanho + 1) >= vet_circ->capacidade &&
        !realocar_vetor(vet_circ, vet_circ->capacidade * FATOR_CRESCIMENTO)
    ) {
        return -1;
    }

    int *posicao_item = acessar(vet_circ, vet_circ->tamanho);
    if(posicao_item == NULL) {
        fprintf(stderr, "Erro ao acessar vetor ao inserir no fim do vetor.\n");
        return 0;
    }
    (*posicao_item) = item;
    vet_circ->tamanho++;
    return 1;
}


int inserir_no_topo(VetorCircularD *vet_circ, int item) {
    /* Conferimos se a vet_circ terá tamanho suficiente para o vetor */
    if((vet_circ->tamanho + 1) >= vet_circ->capacidade &&
            !realocar_vetor(vet_circ, vet_circ->capacidade * FATOR_CRESCIMENTO)) {
        return -1;
    }

    int * posicao_item = acessar(vet_circ, -1);
    if(posicao_item == NULL) {
        fprintf(stderr, "Erro ao acessar vetor ao inserir no fim do vetor.\n");
        return 0;
    }
    /* Adicionamos o item */
    (*posicao_item) = item;
    vet_circ->tamanho++;
    vet_circ->inicio--;
    /* Corrigimos a variável de início, se necessário */
    if(vet_circ->inicio < 0)
        vet_circ->inicio += vet_circ->capacidade;
    return 1;
}


int remover_do_inicio(VetorCircularD *vet_circ, int *item_removido) {
    /* Conferimos se temos o que remover */
    if(vet_circ->tamanho <= 0)
        return 0;

    /* Conferimos se temos que diminuir o tamanho do vetor */
    if(
        vet_circ->tamanho < (vet_circ->capacidade * DECRESCIMENTO_THRESHOLD) &&
        !realocar_vetor(vet_circ, vet_circ->capacidade * FATOR_DECRESCIMENTO)
    ) {
        /* Como esse erro não prejudica o vetor, apenas anunciamos o erro */
        fprintf(stderr, "Falha ao diminuir o vetor durante remoção!\n");
    }

    /* Tentamos remover o item */
    int *removido = acessar(vet_circ, 0);
    if(removido == NULL)
        return 0;
    else
        *item_removido = *removido;

    /* Passamos o início para frente já que removemos com sucesso */
    vet_circ->inicio++;
    if(vet_circ->inicio >= vet_circ->capacidade)
        vet_circ->inicio -= vet_circ->capacidade;
    vet_circ->tamanho--;
    return 1;
}


int remover_do_fim(VetorCircularD *vet_circ, int *item_removido) {
    /* Conferimos se temos o que remover */
    if(vet_circ->tamanho <= 0)
        return 0;

    /* Conferimos se temos que diminuir o tamanho do vetor */
    if(
        vet_circ->tamanho < (vet_circ->capacidade * DECRESCIMENTO_THRESHOLD) &&
        !realocar_vetor(vet_circ, vet_circ->capacidade * FATOR_DECRESCIMENTO)
    ) {
        /* Como esse erro não prejudica o vetor, apenas anunciamos o erro */
        fprintf(stderr, "Falha ao diminuir o vetor durante remoção!\n");
    }

    /* Tentamos remover o item */
    int *removido = acessar(vet_circ, vet_circ->tamanho - 1);
    if(removido == NULL)
        return 0;
    else
        *item_removido = *removido;

    /* Apenas diminuímos o tamanho pois não precisamos alterar mais nada */
    vet_circ->tamanho--;
    return 1;
}


int obter(VetorCircularD *vet_circ, int posicao, int *item_requisitado) {
    int *acesso = acessar(vet_circ, posicao);
    if(acesso == NULL) {
        return 0;
    } else {
        *item_requisitado = *acesso;
        return 1;
    }
}


int realocar_vetor(VetorCircularD *vet_circ, int nova_capacidade) {
    if(nova_capacidade < vet_circ->tamanho || nova_capacidade <= 0) {
        fprintf(stderr, "Não é possível alterar capacidade para %d quando o"
            " tamanho é %d\n", nova_capacidade, vet_circ->tamanho);
        return 0;
    }

    /* Realocamos um vetor com nova capacidade */
    int *_vetor = malloc(nova_capacidade * sizeof(int));
    if(_vetor == NULL) {
        fprintf(stderr, "Erro ao realocar memória para o vetor.");
        return -1;
    }

    {
        /* Atualizamos o novo vetor com os elementos do antigo */
        int i;
        for(i = 0; i < vet_circ->tamanho; i++) {
            /* Recebemos o ponteiro para o i-ésimo elemento */
            int *item = acessar(vet_circ, i);
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
    free(vet_circ->vetor);
    vet_circ->vetor = _vetor;
    vet_circ->inicio = 0;
    vet_circ->capacidade = nova_capacidade;
    return 1;
}


int * acessar(VetorCircularD *vet_circ, int posicao) {
    /* Ignoramos posições inválidas, que saem do limite +/- 1 */
    if(posicao > vet_circ->tamanho || posicao < -1)
        return NULL;

    /* Procuramos a partir do início do vetor */
    return (
        vet_circ->vetor +
        (
            (vet_circ->inicio + posicao + vet_circ->capacidade) %
            (vet_circ->capacidade)
        )
    );
}
