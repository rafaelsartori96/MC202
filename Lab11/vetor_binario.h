#ifndef VETOR_BINARIO_H
#define VETOR_BINARIO_H


struct VetorBinario {
    /** Número de bytes no vetor */
    int bytes;
    /** Vetor de bits */
    char *bits;
};

typedef struct VetorBinario VetorBinario;


/**
* Inicializa o vetor de bits.
*
* Retorna   -1  se não foi possível alocar memória para o vetor,
*            0  se ja existe um vetor no ponteiro dado,
*            1  se inicializamos com sucesso.
*/
int inicializar_vetor_binario(VetorBinario **vetor, int capacidade);

/**
* Verifica o estado do bit.
*
* Nota: a indexação começa do zero.
*
* Retorna   0   se o bit está no estado 'false' ou está fora da posição válida,
*           1   se o bit está no estado 'true'.
*/
int recebe_bit(VetorBinario *vetor, int posicao);

/**
* Alterna o bit na posição dada para 1.
*
* Nota: a indexação começa do zero.
*
* Retorna   0   se não foi possível acessar a posição dada,
*           1   se o bit foi alterado com sucesso.
*/
int define_bit_verdadeiro(VetorBinario *vetor, int posicao);

/**
* Alterna o bit na posição dada para 0.
*
* Nota: a indexação começa do zero.
*
* Retorna   0   se não foi possível acessar a posição dada,
*           1   se o bit foi alterado com sucesso.
*/
int define_bit_falso(VetorBinario *vetor, int posicao);

/**
* Libera os recursos alocados para o vetor binario.
*/
void liberar_vetor_binario(VetorBinario **vetor);


#endif /* VETOR_BINARIO_H */
