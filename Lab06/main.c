#include <stdio.h>
#include <string.h>
#include "arvore_bin_busca.h"


int main() {
    ArvoreBinariaBusca *arvore = NULL;

    /* Inicializamos a árvore */
    if(inicializar_arvore(&arvore) == -1) {
        fprintf(
            stderr,
            "memoria insuficiente\n"
        );
        /* Para todos os casos de memória, devemos continuar, porém não posso
        * evitar este */
        return 0;
    }


    while(1) {
        /* Lemos o comando */
        char linha_comando[128];
        fgets(linha_comando, 128, stdin);

        /* Interpretamos */
        char comando[32];
        sscanf(linha_comando, "%s", comando);
        // printf("comando = \"%s\"\n", linha_comando);

        /* Casos de interpretação */
        if(strcmp(comando, "inserir") == 0) {
            int chave;
            sscanf(linha_comando + strlen(comando) + 1, "%d", &chave);

            if(inserir(arvore, chave) == -1) {
                fprintf(
                    stderr,
                    "memoria insuficiente\n"
                );
            }
        } else if(strcmp(comando, "excluir") == 0) {
            int chave;
            sscanf(linha_comando + strlen(comando) + 1, "%d", &chave);

            remover(arvore, chave);
        } else if(strcmp(comando, "buscar") == 0) {
            int chave;
            sscanf(linha_comando + strlen(comando) + 1, "%d", &chave);

            printf(pertence(arvore, chave) ? "pertence\n" : "nao pertence\n");
        } else if(strcmp(comando, "minimo") == 0) {
            No *minimo_ = NULL;

            if(!minimo(arvore, &minimo_)) {
                printf("vazia\n");
            } else {
                printf("%c\n", minimo_->chave);
            }
        } else if(strcmp(comando, "maximo") == 0) {
            No *maximo_ = NULL;

            if(!maximo(arvore, &maximo_)) {
                printf("vazia\n");
            } else {
                printf("%c\n", maximo_->chave);
            }
        } else if(strcmp(comando, "pos-ordem") == 0) {
            if(!imprimir_pos_ordem(arvore)) {
                printf("vazia\n");
            }
        } else if(strcmp(comando, "em-ordem") == 0) {
            if(!imprimir_em_ordem(arvore)) {
                printf("vazia\n");
            }
        } else if(strcmp(comando, "pre-ordem") == 0) {
            if(!imprimir_pre_ordem(arvore)) {
                printf("vazia\n");
            }
        } else if(strcmp(comando, "largura") == 0) {
            if(!imprimir_em_largura(arvore)) {
                printf("vazia\n");
            }
        } else if(strcmp(comando, "terminar") == 0) {
            destruir_arvore(&arvore);
            return 0;
        } else {
            fprintf(
                stderr,
                "Erro ao ler comando da linha \"%s\"!\n",
                linha_comando
            );
            destruir_arvore(&arvore);
            return -2;
        }
    }

    /* Nunca devemos chegar aqui */
    return -3;
}
