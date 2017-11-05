#include <stdlib.h>
#include "vetor_circular.h"


static int max(int a, int b) {
    return a > b ? a : b;
}


int *posicao_vetor(VetorCircular *vetor_circ, int indice) {
    int capacidade = vetor_circ->capacidade;

    /* Verificamos os limites do vetor */
    if(indice < -1 || indice > vetor_circ->tamanho || indice >= capacidade) {
        return NULL;
    }


    int pos_final = (indice < 0 ?
        /* Ajustamos o vetor para índices negativos voltarem ao fim do vetor */
        ((vetor_circ->inicio + indice + capacidade) % capacidade) :
        /* Ajustamos para índices positivos voltarem ao início do vetor */
        ((vetor_circ->inicio + indice) % capacidade)
    );

    return vetor_circ->vetor + pos_final;
}


int alterar_capacidade(VetorCircular *vetor_circ, int nova_capacidade) {
    /* Verifica se é seguro */
    if(nova_capacidade <= vetor_circ->tamanho) {
        return 0;
    }

    /* Definimos o chão da capacidade */
    nova_capacidade = max(nova_capacidade, CAPACIDADE_INICIAL);

    /* Altera o tamanho */
    int *auxiliar = malloc(nova_capacidade * sizeof(int));
    if(auxiliar == NULL) {
        return -1;
    }

    /* Copiamos todos os atributos para o novo vetor */
    int i;
    for(i = 0; i < vetor_circ->tamanho; i++) {
        *(auxiliar + i) = *posicao_vetor(vetor_circ, i);
    }

    /* Passamos o novo item para o vetor, já que a capacidade foi alterada com
    * sucesso */
    free(vetor_circ->vetor);
    vetor_circ->vetor = auxiliar;
    vetor_circ->inicio = 0;
    vetor_circ->capacidade = nova_capacidade;

    return 1;
}


int inicializar_vetor_circular(VetorCircular **vetor_circ) {
    /* Verifica se o vetor já existe */
    if((*vetor_circ) != NULL) {
        return 0;
    }

    /* Aloca memória para o vetor */
    (*vetor_circ) = malloc(sizeof(VetorCircular));
    if((*vetor_circ) == NULL) {
        return -1;
    }

    /* Inicia o vetor circular com a capacidade inicial */
    (*vetor_circ)->vetor = malloc(CAPACIDADE_INICIAL * sizeof(int));
    if((*vetor_circ)->vetor == NULL) {
        free(*vetor_circ);
        (*vetor_circ) = NULL;
        return -1;
    }

    /* Inicializa os atributos */
    (*vetor_circ)->inicio = 0;
    (*vetor_circ)->tamanho = 0;
    (*vetor_circ)->capacidade = CAPACIDADE_INICIAL;

    return 1;
}


int inicializar_vetor_circular_(VetorCircular *vetor_circ) {
    /* Inicia o vetor circular com a capacidade inicial */
    vetor_circ->vetor = malloc(CAPACIDADE_INICIAL * sizeof(int));
    if(vetor_circ->vetor == NULL) {
        return -1;
    }

    /* Inicializa os atributos */
    vetor_circ->inicio = 0;
    vetor_circ->tamanho = 0;
    vetor_circ->capacidade = CAPACIDADE_INICIAL;

    return 1;
}


int recebe_valor(VetorCircular *vetor_circ, int posicao, int *valor) {
    int *posicao_vetor_ = posicao_vetor(vetor_circ, posicao);

    /* Conferimos se a posição é válida */
    if(posicao_vetor_ == NULL) {
        return 0;
    } else {
        *valor = *posicao_vetor_;
        return 1;
    }
}


int pertence(VetorCircular *vetor_circ, int valor) {
    int i;
    for(i = 0; i < vetor_circ->tamanho; i++) {
        /* Vê se o valor existe no vetor circular */
        if(*posicao_vetor(vetor_circ, i) == valor) {
            return 1;
        }
    }

    return 0;
}


int insere_valor_inicio(VetorCircular *vetor_circ, int valor) {
    /* Verificamos se o vetor está cheio e tentamos mudar seu tamanho */
    if(
        vetor_circ->tamanho >= vetor_circ->capacidade &&
        alterar_capacidade(
            vetor_circ, (int) (vetor_circ->capacidade * FATOR_INCREMENTO)
        ) != 1
    ) {
        return -1;
    }

    /* Verificamos a posição do item a ser inserido */
    int *posicao = posicao_vetor(vetor_circ, -1);
    if(posicao == NULL) {
        return 0;
    }

    /* Inserimos o vetor */
    *posicao = valor;
    vetor_circ->tamanho++;
    /* Alteramos o início */
    vetor_circ->inicio--;
    if(vetor_circ->inicio < 0) {
        vetor_circ->inicio += vetor_circ->capacidade;
    }

    return 1;
}


int insere_valor_fim(VetorCircular *vetor_circ, int valor) {
    /* Verificamos se o vetor está cheio e tentamos mudar seu tamanho */
    if(
        vetor_circ->tamanho >= vetor_circ->capacidade &&
        alterar_capacidade(
            vetor_circ, (int) (vetor_circ->capacidade * FATOR_INCREMENTO)
        ) != 1
    ) {
        return -1;
    }

    /* Verificamos a posição do item a ser inserido */
    int *posicao = posicao_vetor(vetor_circ, vetor_circ->tamanho);
    if(posicao == NULL) {
        return 0;
    }

    /* Inserimos o vetor */
    *posicao = valor;
    vetor_circ->tamanho++;

    return 1;
}


int remove_inicio(VetorCircular *vetor_circ, int *valor) {
    /* Verificamos se o vetor está vazio */
    if(vetor_circ->tamanho == 0) {
        return 0;
    }

    /* Atribuímos o valor ao ponteiro dado */
    *valor = *posicao_vetor(vetor_circ, 0);

    /* Removemos o item do início do vetor */
    vetor_circ->tamanho--;
    vetor_circ->inicio++;
    /* Verificamos se é necessário ajustar a posição de início do vetor */
    if(vetor_circ->inicio >= vetor_circ->capacidade) {
        vetor_circ->inicio -= vetor_circ->capacidade;
    }

    /* Verificamos se é necessário alterar o tamanho do vetor. Não nos
    * preocupamos com o sucesso ou não da alteração da capacidade. */
    if(
        vetor_circ->tamanho < (int) (vetor_circ->capacidade * LIMIAR_DECREMENTO)
    ) {
        alterar_capacidade(
            vetor_circ, (int) (vetor_circ->capacidade * FATOR_DECREMENTO)
        );
    }

    return 1;
}


int remove_fim(VetorCircular *vetor_circ, int *valor) {
    /* Verificamos se o vetor está vazio */
    if(vetor_circ->tamanho == 0) {
        return 0;
    }

    /* Atribuímos o valor ao ponteiro dado */
    *valor = *posicao_vetor(vetor_circ, vetor_circ->tamanho - 1);

    /* Removemos o item do fim do vetor */
    vetor_circ->tamanho--;

    /* Verificamos se é necessário alterar o tamanho do vetor. Não nos
    * preocupamos com o sucesso ou não da alteração da capacidade. */
    if(
        vetor_circ->tamanho < (int) (vetor_circ->capacidade * LIMIAR_DECREMENTO)
    ) {
        alterar_capacidade(
            vetor_circ, (int) (vetor_circ->capacidade * FATOR_DECREMENTO)
        );
    }

    return 1;
}


void liberar_vetor_circular(VetorCircular **vetor_circ) {
    /* Verificamos se o vetor existe */
    if((*vetor_circ) == NULL) {
        return;
    }

    /* Liberamos os recursos */
    free((*vetor_circ)->vetor);
    free(*vetor_circ);
    (*vetor_circ) = NULL;
}


void liberar_vetor_circular_(VetorCircular *vetor_circ) {
    /* Liberamos os recursos */
    free(vetor_circ->vetor);
}
