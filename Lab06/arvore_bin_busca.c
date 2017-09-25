#include <stdio.h>
#include <stdlib.h>
#include "arvore_bin_busca.h"
#include "arvore_bin_busca_auxiliar.h"


int inicializar_arvore(ArvoreBinariaBusca **arvore) {
    /* Conferimos se existe árvore na variável */
    if(*arvore != NULL) {
        return 0;
    }

    *arvore = malloc(sizeof(ArvoreBinariaBusca));
    /* Conferimos se conseguimos alocar memória dinâmica para a árvore */
    if(*arvore == NULL) {
        return -1;
    }

    /* Inicializamos seus atributos */
    (*arvore)->raiz = NULL;
    return 1;
}


int criar_no(No **no) {
    /* Caso exista um nó no ponteiro, não fazemos nada. */
    if((*no) != NULL) {
        return 0;
    }

    *no = malloc(sizeof(No));
    /* Verificamos se foi possível alocar memória para o nó */
    if((*no) == NULL) {
        return -1;
    }

    /* Inicializamos o nó */
    (*no)->direita = NULL;
    (*no)->esquerda = NULL;
    return 1;
}


int criar_raiz(ArvoreBinariaBusca *arvore) {
    int criar_no_ = criar_no(&(arvore->raiz));
    /* Conferimos se foi possível criar o nó */
    if(criar_no_) {
        /* Definimos o pai */
        arvore->raiz->pai = NULL;
    }
    return criar_no_;
}


int criar_filho_esquerda(No *pai) {
    int criar_no_ = criar_no(&(pai->esquerda));
    /* Conferimos se foi possível criar o nó */
    if(criar_no_) {
        /* Definimos o pai */
        pai->esquerda->pai = pai;
    }
    return criar_no_;
}


int criar_filho_direita(No *pai) {
    int criar_no_ = criar_no(&(pai->direita));
    /* Conferimos se foi possível criar o nó */
    if(criar_no_) {
        /* Definimos o pai */
        pai->direita->pai = pai;
    }
    return criar_no_;
}


int sucessor(No *atual, No **sucessor) {
    if(atual->direita != NULL) {
        /* Devemos pegar o máximo da subárvore da direita de atual, fazemos isso
        * através do elemento da direita em si, ou o mais a esquerda dele */
        No *mais_a_esquerda = atual->direita;

        while(mais_a_esquerda->esquerda != NULL) {
            mais_a_esquerda = mais_a_esquerda->esquerda;
        }

        /* Como encontramos o sucessor, retornamos sucesso */
        (*sucessor) = mais_a_esquerda;
        return 1;
    } else {
        /* Devemos pegar o primeiro pai cuja chave é maior que atual */
        No *pai = atual->pai;

        /* Enquanto existe pai (subimos a árvore), procuramos */
        while(pai != NULL) {
            /* Se encontramos o pai, retornamos com sucesso */
            if(pai->chave > atual->chave) {
                *(sucessor) = pai;
                return 1;
            }

            pai = pai->pai;
        }

        /* Caso chegamos aqui, pai foi NULL e, portanto, não há sucessor. */
        return 0;
    }
}


int inserir(ArvoreBinariaBusca *arvore, int chave) {
    if(arvore->raiz != NULL) {
        return inserir_r(chave, arvore->raiz);
    } else {
        /* Conferimos se foi possível criar a raiz */
        if(!criar_raiz(arvore)) {
            return -1;
        }

        /* Alteramos a chave da raiz */
        arvore->raiz->chave = chave;
        return 1;
    }
}


int inserir_r(int chave, No *raiz) {
    /* Impedimos a inserção de elementos repetidos */
    if(raiz->chave == chave) {
        return 0;
    }

    /* Conferimos se deve estar a direita ou a esquerda da raiz atual */
    if(chave > raiz->chave) {
        /* Conferimos se há um elemento da direita */
        if(raiz->direita != NULL) {
            /* Verificamos para a direita */
            return inserir_r(chave, raiz->direita);
        } else {
            /* Como não há item a direita e temos que inserir a direita da raiz
            * atual, criamos o item. */

            /* Conferimos se foi possível criar o elemento */
            if(!criar_filho_direita(raiz)) {
                return -1;
            }

            /* Mudamos a chave do item criado */
            raiz->direita->chave = chave;
            return 1;
        }
    } else {
        /* Conferimos se há um elemento da esquerda */
        if(raiz->esquerda != NULL) {
            /* Conferimos para a chave da esquerda recursivamente */
            return inserir_r(chave, raiz->esquerda);
        } else {
            /* Conferimos se foi possível criar o elemento */
            if(!criar_filho_esquerda(raiz)) {
                return -1;
            }

            /* Mudamos a chave do item criado */
            raiz->esquerda->chave = chave;
            return 1;
        }
    }
}


void mudar_filho(ArvoreBinariaBusca *arvore, No *filho_atual, No *novo_filho) {
    /* Se o filho_atual é a raiz */
    if(arvore->raiz == filho_atual) {
        /* Atualizamos a raiz */
        arvore->raiz = novo_filho;
    } else {
        /* Conferimos se o filho_atual é filho da esquerda ou da direita */
        if(filho_atual == filho_atual->pai->esquerda) {
            /* Atualizamos o filho da esquerda */
            filho_atual->pai->esquerda = novo_filho;
        } else {
            filho_atual->pai->direita = novo_filho;
        }
    }

    if(novo_filho != NULL) {
        /* De qualquer forma, mudamos o pai do novo_filho, seja para ser a raiz
        * (NULL) ou seja para ser filho (filho_atual->pai) */
        novo_filho->pai = filho_atual->pai;
    }
}


int remover(ArvoreBinariaBusca *arvore, int chave) {
    No *remover_ = NULL;

    /* Procuramos o elemento */
    if(!buscar(arvore->raiz, chave, &remover_)) {
        return 0;
    }

    /* Conferimos se devemos utilizar o sucessor */
    if(remover_->esquerda != NULL && remover_->direita != NULL) {
        No *sucessor_ = NULL;

        /* Conseguimos o sucessor */
        if(!sucessor(remover_, &sucessor_)) {
            fprintf(
                stderr,
                "O nó %d deveria possuir um sucessor.\n", remover_->chave
            );
            return -1;
        }

        /* Conferimos se o sucessor é filho a esquerda */
        if(sucessor_->pai->chave > sucessor_->chave) {
            /* Note que aqui, tendo a chave menor que a do pai, o sucessor_
            * é um filho a esquerda.
            * Passamos o filho a direita (pois não há a esquerda) do sucessor
            * para o pai. Se não existir, apenas removemos a ocorrência do
            * filho a esquerda (que é sucessor_). */
            mudar_filho(arvore, sucessor_, sucessor_->direita);
            mudar_filho(arvore, remover_, sucessor_);

            /* Criamos o vínculo sucessor_ <=> remover_->direita, já que o
            * filho a esquerda de remover_ será colocado mais tarde. */
            sucessor_->direita = remover_->direita;
            remover_->direita->pai = sucessor_;
        } else {
            /* Se o sucessor_ é filho a direita, não precisamos removê-lo da
            * árvore e colocá-lo como pai de alguém que está a direita de
            * remover_ pois ele está.
            * Desta forma, precisamos apenas remover remover_ da árvore e ligar
            * seu pai ao sucessor_ */
            mudar_filho(arvore, remover_, sucessor_);
        }

        /* Finalmente, colocamos o filho a esquerda de remover_ para sucessor_ */
        sucessor_->esquerda = remover_->esquerda;
        remover_->esquerda->pai = sucessor_;
    } else if(remover_->direita != NULL) {
        /* Se há apenas filho a direita, passamos para aquele que está a sua
        * direita, se existir. */
        mudar_filho(arvore, remover_, remover_->direita);
    } else if(remover_->esquerda != NULL) {
        /* Se há apenas filho a esquerda, passamos a ligação para aquele que
        * está a sua esquerda */
        mudar_filho(arvore, remover_, remover_->esquerda);
    } else {
        /* Se não há filhos, apenas retiramos a ligação pai -> filho */
        mudar_filho(arvore, remover_, NULL);
    }

    /* Finalmente, liberamos o removido */
    free(remover_);
    return 1;
}


int pertence(ArvoreBinariaBusca *arvore, int chave) {
    return buscar(arvore->raiz, chave, NULL);
}

int buscar(No *raiz, int chave, No **busca) {
    /* Conferimos se a árvore é nula */
    if(raiz == NULL) {
        return 0;
    }

    return buscar_r(raiz, chave, busca);
}


int buscar_r(No *raiz, int chave, No **busca) {
    /* Conferimos se encontramos a chave desejada */
    if(raiz->chave == chave) {
        /* Conferimos se a variável de busca deve ser substituída */
        if(busca != NULL) {
            (*busca) = raiz;
        }

        return 1;
    }

    if(chave > raiz->chave) {
        /* Conferimos se existe a sub-árvore da direita */
        if(raiz->direita != NULL) {
            return buscar(raiz->direita, chave, busca);
        } else {
            return 0;
        }
    } else {
        /* Conferimos se existe a sub-árvore da esquerda */
        if(raiz->esquerda != NULL) {
            return buscar(raiz->esquerda, chave, busca);
        } else {
            return 0;
        }
    }
}


int minimo(ArvoreBinariaBusca *arvore, No **minimo_) {
    if(arvore->raiz == NULL) {
        return 0;
    }

    return minimo_aux(arvore->raiz, minimo_);
}


int minimo_aux(No *raiz, No **minimo_) {
    /* Enquanto existir elemento a esquerda, mudamos */
    while(raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }

    (*minimo_) = raiz;
    return 1;
}


int maximo(ArvoreBinariaBusca *arvore, No **maximo_) {
    if(arvore->raiz == NULL) {
        return 0;
    }

    return maximo_aux(arvore->raiz, maximo_);
}


int maximo_aux(No *raiz, No **maximo_) {
    /* Enquanto existir elemento a direita, mudamos */
    while(raiz->direita != NULL) {
        raiz = raiz->direita;
    }

    (*maximo_) = raiz;
    return 1;
}


int imprimir_pre_ordem(ArvoreBinariaBusca *arvore) {
    if(arvore->raiz != NULL) {
        imprimir_pre_ordem_r(arvore->raiz);
        printf("\n");
        return 1;
    }
    return 0;
}


int imprimir_em_ordem(ArvoreBinariaBusca *arvore) {
    if(arvore->raiz != NULL) {
        imprimir_em_ordem_r(arvore->raiz);
        printf("\n");
        return 1;
    }
    return 0;
}


int imprimir_pos_ordem(ArvoreBinariaBusca *arvore) {
    if(arvore->raiz != NULL) {
        imprimir_pos_ordem_r(arvore->raiz);
        printf("\n");
        return 1;
    }
    return 0;
}


void imprimir_pre_ordem_r(No *raiz) {
    /* Imprimimos a chave da raiz atual */
    printf("%d ", raiz->chave);

    /* Imprimimos, se existir, raiz da esquerda */
    if(raiz->esquerda != NULL) {
        imprimir_pre_ordem_r(raiz->esquerda);
    }

    /* Imprimimos, se existir, raiz da direita */
    if(raiz->direita != NULL) {
        imprimir_pre_ordem_r(raiz->direita);
    }
}


void imprimir_em_ordem_r(No *raiz) {
    /* Imprimimos, se existir, raiz da esquerda */
    if(raiz->esquerda != NULL) {
        imprimir_em_ordem_r(raiz->esquerda);
    }

    /* Imprimimos a chave da raiz atual */
    printf("%d ", raiz->chave);

    /* Imprimimos, se existir, raiz da direita */
    if(raiz->direita != NULL) {
        imprimir_em_ordem_r(raiz->direita);
    }
}


void imprimir_pos_ordem_r(No *raiz) {
    /* Imprimimos, se existir, raiz da esquerda */
    if(raiz->esquerda != NULL) {
        imprimir_pos_ordem_r(raiz->esquerda);
    }

    /* Imprimimos, se existir, raiz da direita */
    if(raiz->direita != NULL) {
        imprimir_pos_ordem_r(raiz->direita);
    }

    /* Imprimimos a chave da raiz atual */
    printf("%d ", raiz->chave);
}


int imprimir_em_largura(ArvoreBinariaBusca *arvore) {
    /* Não imprimimos caso a árvore esteja vazia */
    if(arvore->raiz == NULL) {
        return 0;
    }

    /* Caso não esteja, imprimimos. */
    int nivel = 0;
    while(imprimir_em_largura_r(0, nivel, arvore->raiz)) {
        nivel++;
    }
    printf("\n");
    return 1;
}


int imprimir_em_largura_r(int nivel_atual, int nivel_alvo, No *raiz) {
    if(nivel_atual == nivel_alvo) {
        /* Se estamos no nível alvo (note que já conferimos se ele existe),
        * imprimimos */
        printf("%d ", raiz->chave);
        return 1;
    } else if(nivel_atual < nivel_alvo) {
        /* Chamamos recursivamente para a esquerda e para a direita */
        int impresso = 0;

        if(
            raiz->esquerda != NULL &&
            imprimir_em_largura_r(nivel_atual + 1, nivel_alvo, raiz->esquerda)
        ) {
            impresso = 1;
        }

        if(
            raiz->direita != NULL &&
            imprimir_em_largura_r(nivel_atual + 1, nivel_alvo, raiz->direita)
        ) {
            impresso = 1;
        }

        /* Retornamos 1 caso houve impressão */
        return impresso;
    } else {
        /* Não chegamos neste nível */
        return 0;
    }
}


void limpar_arvore(ArvoreBinariaBusca *arvore) {
    /* Liberamos a árvore recursivamente */
    if(arvore->raiz != NULL) {
        limpar_arvore_r(arvore->raiz);
        free(arvore->raiz);
        arvore->raiz = NULL;
    }
}


void limpar_arvore_r(No *raiz) {
    /* Liberamos a raiz da esquerda */
    if(raiz->esquerda != NULL) {
        limpar_arvore_r(raiz->esquerda);
        free(raiz->esquerda);
    }

    /* Liberamos a raiz da direita */
    if(raiz->direita != NULL) {
        limpar_arvore_r(raiz->direita);
        free(raiz->direita);
    }
}


void destruir_arvore(ArvoreBinariaBusca **arvore) {
    if(*arvore == NULL) {
        return;
    }

    /* Liberamos a árvore após limpar seus nós */
    limpar_arvore(*arvore);
    free(*arvore);
    *arvore = NULL;
}
