#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "vetor_binario.h"


int inicializar_vetor_binario(VetorBinario **vetor, int capacidade) {
    /* Verificar se o vetor já existe */
    if((*vetor) != NULL) {
        return 0;
    }

    /* Tentamos alocar recursos para a estrutura do vetor */
    (*vetor) = malloc(sizeof(VetorBinario));
    if((*vetor) == NULL) {
        return -1;
    }

    /* Calculamos quantos bytes precisaremos.
    * Se o resto da divisão do número de bits necessários pelo número de
    * bits num char é maior do que zero, precisamos alocar um caractere a
    * mais do que a divisão inteira. */
    int numero_bytes = (capacidade / CHAR_BIT) +
        ((capacidade % CHAR_BIT) > 0 ? 1 : 0);

    /* Tentar alocar recursos para o vetor de bits */
    (*vetor)->bits = calloc(numero_bytes, sizeof(char));
    if((*vetor)->bits == NULL) {
        /* Liberamos os recursos alocados */
        free(*vetor);
        (*vetor) = NULL;
        return -1;
    }

    /* Agora inicializamos os atributos */
    (*vetor)->bytes = numero_bytes;

    return 1;
}


int recebe_bit(VetorBinario *vetor, int posicao) {
    /* Calculamos a posição do bit no vetor linearizado */
    /* Utilizamos a divisão pra encontrar o byte correto */
    int posicao_byte = posicao / CHAR_BIT;
    /* Utilizamos o resto da divisão para encontrar o lugar do bit no byte */
    int posicao_bit = posicao % CHAR_BIT;

    /* Verificamos se estamos dentro do intervalo permitido */
    if(posicao_byte >= vetor->bytes) {
        return 0;
    }

    /* Agora verificamos o bit dado na posição correta.
    * Usamos uma máscara com apenas um bit 1 que estará na posição do bit,
    * fazemos a operação AND e descobriremos se o bit é 1 ou 0 com o resultado
    * desta operação (que não deve substituir o vetor de bits, pois estragaria
    * os registros).
    * Se o bit fosse 1, a operação AND resultaria em 1 e o valor resultante
    * teria um número binário diferente de zero. Se fosse 0, a operação AND
    * resultaria em 0 e o vetor todo seria zero. */
    return (*(vetor->bits + posicao_byte) & (1 << posicao_bit)) > 0;
}


int define_bit_verdadeiro(VetorBinario *vetor, int posicao) {
    /* Calculamos a posição do bit no vetor linearizado */
    /* Utilizamos a divisão pra encontrar o byte correto */
    int posicao_byte = posicao / CHAR_BIT;
    /* Utilizamos o resto da divisão para encontrar o lugar do bit no byte */
    int posicao_bit = posicao % CHAR_BIT;

    /* Verificamos se estamos dentro do intervalo permitido */
    if(posicao_byte >= vetor->bytes) {
        return 0;
    }

    /* Agora mudamos o bit dado na posição correta.
    * Usamos uma máscara com apenas um bit 1 que estará na posição do bit.
    * Fazemos a operação OR para torná-lo true. */
    *(vetor->bits + posicao_byte) |= (1 << posicao_bit);
    return 1;
}


int define_bit_falso(VetorBinario *vetor, int posicao) {
    /* Calculamos a posição do bit no vetor linearizado */
    /* Utilizamos a divisão pra encontrar o byte correto */
    int posicao_byte = posicao / CHAR_BIT;
    /* Utilizamos o resto da divisão para encontrar o lugar do bit no byte */
    int posicao_bit = posicao % CHAR_BIT;

    /* Verificamos se estamos dentro do intervalo permitido */
    if(posicao_byte >= vetor->bytes) {
        return 0;
    }

    /* Agora mudamos o bit dado na posição correta.
    * Usamos uma máscara com apenas um bit 1 que estará na posição do bit.
    * Invertemos esta máscara para não alterarmos os outros bits e fazemos a
    * operação AND para torná-lo false. */
    *(vetor->bits + posicao_byte) &= (~(1 << posicao_bit));
    return 1;
}


int copiar_vetor_binario(VetorBinario *fonte, VetorBinario *dest) {
    /* Conferimos se o vetor destino é capaz de suportar a cópia. */
    if(dest->bytes < fonte->bytes) {
        return 0;
    }

    /* Executamos a cópia byte a byte */
    memcpy(dest->bits, fonte->bits, fonte->bytes);
    return 1;
}


void limpar_vetor_binario(VetorBinario *vetor) {
    for(int i = 0; i < vetor->bytes; i++) {
        /* Tornamos todos os bytes zero */
        *(vetor->bits + i) = 0;
    }
}


void liberar_vetor_binario(VetorBinario **vetor) {
    /* Verificamos se o vetor existe */
    if((*vetor) == NULL) {
        return;
    }

    /* Liberamos recursos */
    free((*vetor)->bits);
    free(*vetor);
    (*vetor) = NULL;
}
