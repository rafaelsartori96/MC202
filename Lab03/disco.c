/* Rafael Sartori Martins dos Santos (RA: 186154) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disco.h"


int procurar_menor_bloco_livre(Disco *disco, int tamanho, Arquivo **arquivo_anterior) {
    /* Conferimos se há espaço disponível para o bloco livre desejado */
    if(tamanho > (disco->capacidade - disco->espaco_ocupado)) {
        return 0;
    }

    /* Se há espaço e não há itens, estamos inserindo o primeiro item. */
    if(disco->arquivo_inicial == NULL) {
        *arquivo_anterior = NULL;
        return 1;
    }

    /* Guardamos as variáveis para o menor bloco a ser buscado */
    int definimos_menor_arquivo = 0;
    /** menor_arquivo_anterior irá guardar o arquivo anterior ao item inserido,
    * de modo a inseri-lo na ordem correta */
    Arquivo *menor_arquivo_anterior = NULL;
    int menor_tamanho = disco->capacidade;

    /*
    * Caso haja um vácuo entre o início do disco e o primeiro item, utilizamos
    * o endereço do primeiro item para verificarmos se devemos colocar o arquivo
    * neste vácuo.
    *
    * Fazemos isso ao considerarmos o menor tamanho o vácuo inicial entre o
    * primeiro arquivo e o ínicio do disco, se houver.
    *
    * Acredito que esse era o erro dos meus testes passados... Lembro de pensar
    * neste código nas últimas tentativas, mas também lembro de pensar que teria
    * algum caso que não funcionaria. No entanto, possivelmente esta minha
    * implementação não terá problemas.
    */
    if(disco->arquivo_inicial->endereco_inicio != 0 &&
            disco->arquivo_inicial->endereco_inicio >= tamanho) {
        menor_tamanho = disco->arquivo_inicial->endereco_inicio;
        definimos_menor_arquivo = 1;
    }

    /* Buscamos pelo disco pelo menor bloco através de 'arquivo' */
    /** arquivo começa do primeiro arquivo da lista */
    Arquivo *arquivo = disco->arquivo_inicial;
    for(; arquivo != NULL; arquivo = arquivo->proximo) {
        /* Guardamos em espaço livre o endereço do próximo item */
        int espaco_livre;
        if(arquivo->proximo != NULL)
            espaco_livre = arquivo->proximo->endereco_inicio;
        else
            espaco_livre = disco->capacidade;

        /* Tiramos do espaço livre o endereço do item atual, assim obtemos o
        * tamanho do espaço entre o item atual e o próximo */
        int endereco_possivel = arquivo->endereco_inicio + arquivo->tamanho;
        espaco_livre -= endereco_possivel;


        /* Se encontramos um espaço livre menor que o salvo anteriormente,
        * substituímos */
        if(espaco_livre >= tamanho && espaco_livre < menor_tamanho) {
            menor_arquivo_anterior = arquivo;
            menor_tamanho = espaco_livre;
            definimos_menor_arquivo = 1;
        }
    }


    if(!definimos_menor_arquivo) {
        /* Se não definimos o menor bloco, não encontramos espaço contíguo e
        * devemos otimizar o disco. Retornamos o item no final do disco enquanto
        * ele é otimizado */
        *arquivo_anterior = otimizar_disco(disco);
    } else {
        /* Se não for -1, encontramos o menor bloco possível capaz de armazenar
        * o arquivo de tamanho dado. */
        *arquivo_anterior = menor_arquivo_anterior;
    }
    return 1;
}

Arquivo * otimizar_disco(Disco *disco) {
    Arquivo *arquivo = disco->arquivo_inicial;
    int ultimo_endereco = 0;
    for(; arquivo != NULL; ) {
        /* Passamos todos os arquivos para frente, eliminando espaços entre
        * arquivos. */
        arquivo->endereco_inicio = ultimo_endereco;
        ultimo_endereco += arquivo->tamanho;

        /* Continuamos até encontrarmos o fim da lista */
        if(arquivo->proximo == NULL)
            return arquivo;
        else
            arquivo = arquivo->proximo;
    }
}

int remover_arquivo(Disco *disco, char nome_do_arquivo[11]) {
    if(disco->arquivo_inicial == NULL) {
        return 0;
    }

    Arquivo *arquivo = disco->arquivo_inicial;

    /* Removemos se é o primeiro arquivo do disco */
    if(strcmp(arquivo->nome_arquivo, nome_do_arquivo) == 0) {
        /* Removemos o arquivo da lista */
        disco->arquivo_inicial = arquivo->proximo;
        disco->espaco_ocupado -= arquivo->tamanho;

        /* Liberamos sua memória */
        free(arquivo);
        return 1;
    }

    /* Verificamos no meio do disco */
    for(; arquivo->proximo != NULL; arquivo = arquivo->proximo) {
        if(strcmp(arquivo->proximo->nome_arquivo, nome_do_arquivo) == 0) {
            /* Salvamos o arquivo a ser removido */
            Arquivo *arquivo_removido = arquivo->proximo;

            /* Removemos o arquivo da lista */
            arquivo->proximo = arquivo_removido->proximo;
            disco->espaco_ocupado -= arquivo_removido->tamanho;

            /* Liberamos sua memória */
            free(arquivo_removido);
            return 1;
        }
    }

    return 0;
}

int inserir_no_disco(Disco *disco, int tamanho, char nome_arquivo[11]) {
    /* Procuramos espaço para o arquivo */
    Arquivo *arquivo_anterior;
    if(!procurar_menor_bloco_livre(disco, tamanho, &arquivo_anterior)) {
        return 0;
    }

    /* Criamos um novo arquivo */
    Arquivo *arquivo_inserido = malloc(sizeof(Arquivo));
    if(arquivo_inserido == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo arquivo.\n");
        return -1;
    }

    /* Colocamos as informações no arquivo criado */
    strcpy(arquivo_inserido->nome_arquivo, nome_arquivo);
    arquivo_inserido->tamanho = tamanho;
    disco->espaco_ocupado += tamanho;

    /* Por fim, adicionamos o item a lista */
    if(arquivo_anterior == NULL) {
        /* Continuamos a lista em arquivo inserido */
        arquivo_inserido->proximo = disco->arquivo_inicial;
        /* Adicionamos o item a lista */
        arquivo_inserido->endereco_inicio = 0;
        disco->arquivo_inicial = arquivo_inserido;
    } else {
        /* Definimos o tamanho do arquivo inserido */
        arquivo_inserido->endereco_inicio = arquivo_anterior->endereco_inicio +
            arquivo_anterior->tamanho;
        /* Adicionamos o item a lista */
        arquivo_inserido->proximo = arquivo_anterior->proximo;
        arquivo_anterior->proximo = arquivo_inserido;
    }
    return 1;
}

int criar_disco(int capacidade, Disco **disco) {
    /* Alocamos memória para um disco */
    (*disco) = malloc(sizeof(Disco));
    if((*disco) == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o disco.\n");
        return -1;
    }

    /* Inicializamos os atributos de disco */
    (*disco)->capacidade = capacidade;
    (*disco)->arquivo_inicial = NULL;
    (*disco)->espaco_ocupado = 0;
    return 1;
}

void liberar_disco(Disco **disco) {
    if((*disco) == NULL) {
        return;
    }

    Arquivo *arquivo = (*disco)->arquivo_inicial, *auxiliar = NULL;
    for(; (*disco)->arquivo_inicial != NULL; ) {
        /* Guardamos o arquivo inicial */
        auxiliar = (*disco)->arquivo_inicial;
        /* Substituímos pelo seu proximo */
        (*disco)->arquivo_inicial = auxiliar->proximo;
        /* Liberamos o inicial antigo */
        free(auxiliar);
    }
    free(*disco);
    *disco = NULL;
}
