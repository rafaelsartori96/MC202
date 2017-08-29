/* Rafael Sartori Martins dos Santos (RA: 186154) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disco.h"


/**
* A função retorna um inteiro que representa o número de Kb para o caractere
* dado.
*
* Retorna 0 caso não encontramos o caractere
*/
int char_para_capacidade(char c);

/**
* A função retorna um inteiro em capacidade lida do vetor de caracteres entrada.
*
* A função espera que entrada esteja apontando para o início do número.
*
* Retorna 0 caso não seja possível determinar a capacidade.
*/
int ler_capacidade(char *entrada, int *capacidade);


int main() {
    Disco *disco = NULL;
    /**
    * Usaremos essa variável para determinar se iremos executar os comandos ou
    * se o disco está lotado.
    */
    int executando_comandos = 1;
    while(1) {
        char entrada[32]; // calculo que o tamanho máximo seja 27
        fgets(entrada, 32, stdin);

        // Removemos o \n
        entrada[strlen(entrada) - 1] = '\0';

        // Começamos nosso 'parser'
        char primeiro_caractere = entrada[0];

        // Se o primeiro caractere for um número...
        if(primeiro_caractere >= 48 && primeiro_caractere <= 57) {
            char ultimo_caractere = entrada[strlen(entrada) - 1];

            // Se o último caractere é uma letra...
            if(ultimo_caractere >= 65 && ultimo_caractere <= 122) {
                /*
                * Estamos lendo a capacidade
                *
                * Devemos, então, liberar, imprimir o disco passado, se
                * existente, e criar um novo disco.
                */

                /* Imprimimos o disco antes de liberá-lo */
                if(disco != NULL) {
                    if(executando_comandos == 0)
                        printf("ERRO: disco cheio\n");
                    else
                        imprimir_disco(disco);
                }

                /* Liberamos o disco passado */
                liberar_disco(&disco);

                /* Lemos a capacidade do disco */
                int capacidade;
                if(!ler_capacidade(entrada, &capacidade)) {
                    fprintf(stderr, "Erro ao ler a capacidade do disco.\n");
                    return -1;
                }

                /* Tentamos criar o disco */
                if(criar_disco(capacidade, &disco) != 1) {
                    return -1;
                }

                /* Agora que o disco está pronto, aguardamos comandos */
                executando_comandos = 1;
            } else {
                /*
                * Estamos lendo o número de operações, ignoramos se não for 0.
                */

                int operacoes;
                sscanf(entrada, "%d", &operacoes);

                if(operacoes == 0) {
                    if(disco != NULL) {
                        /* Imprimimos o disco */
                        if(executando_comandos == 0)
                            printf("ERRO: disco cheio\n");
                        else
                            imprimir_disco(disco);

                        /* Liberamos o disco */
                        liberar_disco(&disco);
                    }
                    return 0;
                }
            }
        } else if(executando_comandos) {
            /*
            * Estamos lendo um comando
            *
            * Identificamos o comando:
            * Se formos otimizar, não precisamos de mais informações
            * Se não, precisamos do nome do arquivo e, no caso de inserir, de
            * seu tamanho.
            */

            char comando[8];
            sscanf(entrada, "%s", comando);

            if(strcmp(comando, "otimiza") == 0) {
                otimizar_disco(disco);
            } else {
                /* Recebemos o tamanho, fazendo o shift da string de entrada
                * por conta dos espaços */
                char nome_do_arquivo[11];
                sscanf(entrada + strlen(comando) + 1, "%s", nome_do_arquivo);

                if(strcmp(comando, "insere") == 0) {
                    /* Pedimos o tamanho do arquivo em
                    * entrada + strlen(comando) + strlen(nome_do_arquivo) + 2
                    * por conta das leituras anteriores que não usam o espaço. */
                    int tamanho_do_arquivo;
                    if(!ler_capacidade(
                        entrada + strlen(comando) + strlen(nome_do_arquivo) + 2,
                        &tamanho_do_arquivo
                    )) {
                        fprintf(stderr, "Erro ao ler o tamanho do arquivo.\n");
                        liberar_disco(&disco);
                        return -1;
                    }

                    /* Tentamos inserir no disco */
                    int retorno = inserir_no_disco(
                        disco,
                        tamanho_do_arquivo,
                        nome_do_arquivo
                    );
                    if(retorno == 0) {
                        /* 0 => não há espaço em disco, já tentamos otimizá-lo */
                        executando_comandos = 0;
                    } else if(retorno < 0) {
                        fprintf(stderr, "Erro ao inserir arquivo no disco.\n");
                        liberar_disco(&disco);
                        return -1;
                    }
                } else if (strcmp(comando, "remove") == 0) {
                    /* Se formos remover do disco, não precisamos de mais
                    * informações que o nome */
                    remover_arquivo(disco, nome_do_arquivo);
                } else {
                    /*
                    * Caso não encontramos o comando, imprimimos o erro e saímos
                    */

                    fprintf(stderr, "Comando não reconhecido: %s\n", comando);
                    liberar_disco(&disco);
                    return -1;
                }
            }
        }
    }

    /* Não devemos chegar nisso */
    return -1;
}

int char_para_capacidade(char c) {
    switch(c) {
        case 'k':
        case 'K':
            return 1;
        case 'm':
        case 'M':
            return 1024 * char_para_capacidade('K');
        case 'g':
        case 'G':
            return 1024 * char_para_capacidade('M');
        default:
            fprintf(stderr, "Não reconheço o caractere %c para cálculo da "
            "capacidade/tamanho.\n", c);
            return 0;
    }
}

int ler_capacidade(char *entrada, int *capacidade) {
    char multiplo;
    /* Recebemos o número e a unidade */
    sscanf(entrada, "%d%c", capacidade, &multiplo);

    /* Calculamos em kb e conferimos se a resposta é esperada */
    (*capacidade) = (*capacidade) * char_para_capacidade(multiplo);
    return (*capacidade) != 0; /* Se for igual a zero, deve retornar "false" */
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a > b ? b : a;
}

char caractere_porcentagem(double porcentagem_usados) {
    /* 75 < P <= 100, 25 < P <= 75 ou 0 <= P <= 25 */
    if(porcentagem_usados >= 75.0) {
        return '#';
    } else if(25.0 <= porcentagem_usados && porcentagem_usados < 75.0) {
        return '-';
    } else {
        return ' ';
    }
}

void imprimir_disco(Disco *disco) {
    /** Porcentagem de bytes utilizados */
    double blocos[8] = {0.0};

    /* Para cada arquivo... */
    Arquivo *arquivo = disco->arquivo_inicial;
    for(; arquivo != NULL; arquivo = arquivo->proximo) {
        int endereco_final = arquivo->endereco_inicio + arquivo->tamanho;

        /* e para cada bloco... */
        int i;
        for(i = 0; i < 8; i++) {
            /*
            * ... verificamos a intersecção matemática entre os endereços dos 8
            * blocos de memória e os arquivos do disco.
            *
            * Otimizamos para pular algumas verificações
            */

            int endereco_bloco_inicio = i * (disco->capacidade / 8);
            int endereco_bloco_fim = (i + 1) * (disco->capacidade / 8);

            /* Verificamos se podemos ignorar esta iteração pois o bloco não
            * atinge o arquivo */
            if(endereco_final < endereco_bloco_inicio)
                continue;

            /* Verificamos se podemos já pular esse arquivo pois já contabili-
            * zamos esta iteração em blocos passados */
            if(endereco_bloco_inicio > endereco_final)
                /* Quebramos o laço em i */
                break;

            /* Verificamos os bytes contribuíntes através de uma intersecção de
            * endereços [do arquivo e do bloco] */
            int inicio = max(arquivo->endereco_inicio, endereco_bloco_inicio);
            int fim = min(endereco_final, endereco_bloco_fim);

            /* Se o intervalo de intersecção existe... */
            if(fim >= inicio) {
                /* ... adicionamos a porcentagem utilizada daquele bloco */
                blocos[i] += (double) (
                    ((fim - inicio) * 100.0) / (disco->capacidade / 8.0)
                );
            }
        }
    }

    {
        int i;
        for(i = 0; i < 8; i++) {
            /* Agora, imprimimos os intervalos utilizando os caracteres
            * apropriados :) */
            printf("[%c]", caractere_porcentagem(blocos[i]));
        }
        printf("\n");
    }
}
