/* Rafael Sartori Martins dos Santos (186154) */

#ifndef VETOR_H
#define VETOR_H

#define DIMENSAO 3


struct Vetor {
    /** Coordenadas no universo */
    int coordenadas[DIMENSAO];
};

typedef struct Vetor Vetor;


/**
* Calcula o comprimento do vetor ao quadrado (eficiente, pois não executamos a
* raiz quadrada).
*
* Retorna o comprimento do vetor ao quadrado.
*/
int comprimento_quadrado(Vetor *vetor);

/**
* Calcula o produto interno dos vetores dados. Eles devem ser de mesmo tipo (e
* mesma dimensão).
*
* Retorna o produto interno dos vetores dados
*/
int produto_interno(Vetor *vetor_a, Vetor *vetor_b);

/**
* Calcula a diferença entre os vetores 'vetor_a' e 'vetor_b', inserindo o
* resultado no vetor 'vetor_resposta'.
*/
void diferenca(Vetor *vetor_resposta, Vetor *vetor_a, Vetor *vetor_b);

/**
* Copia o vetor de fonte para destino. Ambos devem ter sido alocados da maneira
* mais conveniente.
*/
void copiar(Vetor *vetor_fonte, Vetor *vetor_destino);

/**
* Troca o sinal das coordenadas do vetor dado que deve existir.
*/
void oposto(Vetor *vetor);


#endif /* VETOR_H */
