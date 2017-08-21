#include <stdio.h>
#include <stdlib.h>
#include "lab02.h"
#include "lista.h"


int main() {
    /**
    * número de chaves
    */
    int num_chaves;
    scanf("%d", &num_chaves);

    /**
    * número de requisições
    */
    int num_requisicoes;
    scanf("%d", &num_requisicoes);

    /**
    * vetor de requisições
    */
    int *requisicoes = malloc(num_requisicoes * sizeof(int));
    if(requisicoes == NULL) {
        fprintf(stderr, "Erro ao inicializar memória dinâmica para requisições.\n");
        return 1;
    }
    {
        int i;
        for(i = 0; i < num_requisicoes; i++) {
            scanf("%d", (requisicoes + i));
        }
    }


    /**
    * apontador para lista
    */
    Item *lista = NULL;

    /*
    * Fazemos para o método Move-To-Front (MTF)
    */
    {
        if(!inicializar_lista(&lista, num_chaves)) {
            fprintf(stderr, "Erro ao inicializar lista.\n");
            free(requisicoes);
            return 1;
        }

        /**
        * Variável que será usada para calcular o custo
        */
        int custo = 0, custo_total = 0;

        {
            Item *no = NULL;
            int i, chave_requisitada;
            for(i = 0; i < num_requisicoes; i++) {
                chave_requisitada = *(requisicoes + i);
                // Se a chave não foi encontrada, continuamos o programa
                if(!buscar_chave(lista, &no, &custo, chave_requisitada)) {
                    custo_total += custo;
                    continue;
                }

                // Somamos o custo total e colocamos o nó no topo da lista
                custo_total += custo;
                // printf("Custo = %d ", custo);
                colocar_na_cabeca(&lista, chave_requisitada);
                // imprimir_lista(lista);
            }
        }

        liberar_lista(&lista);
        printf("%d ", custo_total);
    }

    /*
    * Fazemos para o método Transpose (TR)
    */
    {
        if(!inicializar_lista(&lista, num_chaves)) {
            fprintf(stderr, "Erro ao inicializar lista.\n");
            free(requisicoes);
            return 1;
        }
        // imprimir_lista(lista);

        /**
        * Variável que será usada para calcular o custo
        */
        int custo = 0, custo_total = 0;

        {
            Item *no_atual = NULL;
            int i, chave_requisitada;
            for(i = 0; i < num_requisicoes; i++) {
                chave_requisitada = *(requisicoes + i);
                // Se a chave não foi encontrada, continuamos o programa
                if(!buscar_chave(lista, &no_atual, &custo, chave_requisitada)) {
                    custo_total += custo;
                    continue;
                }

                // Não utilizamos o valor do nó
                no_atual = lista;

                // Somamos o custo total
                custo_total += custo;

                /*
                * Caso a chave já está no primeiro item, voltamos as requisi-
                * ções.
                */
                if(no_atual->chave == chave_requisitada ||
                no_atual->proximo == NULL) {
                    // imprimir_lista(lista);
                    continue;
                }

                /*
                * Caso a chave esteja no segundo item, a variável lista deve
                * receber o endereço do segundo item, cujo 'proximo' será a
                * antiga cabeça da lista, tendo, por sua vez, como 'proximo'
                * o terceiro item da lista, seja lá qual ele for.
                */
                if(no_atual->proximo->chave == chave_requisitada) {
                    lista = no_atual->proximo;
                    no_atual->proximo = lista->proximo;
                    lista->proximo = no_atual;
                    // imprimir_lista(lista);
                    // Continuamos para a próxima iteração, não faremos o laço
                    // que vem a seguir.
                    continue;
                }

                /*
                * O trecho a seguir poderia facilmente ser resolvido com uma
                * função posicao(Item *lista, Item **no, int posicao)....
                * Mas eu só pensei nisso depois, quando eu imaginei como seria
                * no caso de listas serem vetores.
                */

                /*
                * Devemos trocar de posição a chave desejada com o anterior
                * sabendo que o elemento está pelo menos na terceira posição.
                *
                * Suponha que desejamos o item 3
                *    lista --> 1 -> 2 -> 3 -> 4 -> NULL
                * Devemos fazer 2.proximo -> 4 e 1.proximo -> 3 e 3.proximo ->
                * 2
                * Para isso, devemos guardar a posição anterior à posição ante-
                * rior à chave desejada. Devemos conferir, portanto o próximo
                * elemento do próximo elemento do no_atual pela chave desejada.
                *
                * Nota: já sabemos que no_atual->proximo não é NULL.
                */
                while(no_atual != NULL) {
                    /*
                    * Se no_atual->proximo->proximo é diferente de NULL e
                    * Se o próximo elemento de no_atual é o elemento cuja chave
                    * desejamos, devemos apontar no_atual->proximo para o ele-
                    * mento no_atual->proximo->proximo. Seja lá qual for.
                    *
                    * Em resumo:
                    * 1: no_atual
                    * 2: no_atual->proximo [anterior]
                    * 3: no_atual->proximo->proximo [chave]
                    * 4: no_atual->proximo->proximo->proximo [posterior]
                    *
                    * 2.proximo --> 4
                    * 1.proximo --> 3
                    * 3.proximo --> 2
                    */
                    if(no_atual->proximo->proximo != NULL &&
                    no_atual->proximo->proximo->chave == chave_requisitada) {
                        Item *chave = no_atual->proximo->proximo;
                        Item *anterior = no_atual->proximo;
                        Item *posterior = no_atual->proximo->proximo->proximo;

                        anterior->proximo = posterior;  // 2 --> 4
                        no_atual->proximo = chave;      // 1 --> 3
                        chave->proximo = anterior;      // 3 --> 2
                        // imprimir_lista(lista);
                        break;
                    } else {
                        no_atual = no_atual->proximo;
                    }
                }
            }
        }

        liberar_lista(&lista);
        printf("%d ", custo_total);
    }

    /*
    * Fazemos para o método Count (C)
    */
    {
        if(!inicializar_lista(&lista, num_chaves)) {
            fprintf(stderr, "Erro ao inicializar lista.\n");
            free(requisicoes);
            return 1;
        }

        /**
        * Variável que será usada para calcular o custo
        */
        int custo = 0, custo_total = 0;

        {
            Item *no_removido = NULL, *no_atual = NULL;
            int i, chave_requisitada;
            for(i = 0; i < num_requisicoes; i++) {
                chave_requisitada = *(requisicoes + i);
                // Se a chave não foi encontrada, continuamos o programa
                if(!buscar_chave(lista, &no_removido, &custo, chave_requisitada)) {
                    custo_total += custo;
                    continue;
                }

                // Somamos o custo total e incrementamos o contator. Reordenan-
                // do o nó
                custo_total += custo;
                no_removido->contador++;
                // printf("Custo = %d ", custo);

                if(!remover_item(&lista, &no_removido, chave_requisitada)) {
                    fprintf(stderr, "Chave previamente encontrada na lista não \
                    foi encontrada na lista!\n");
                    liberar_lista(&lista);
                    free(requisicoes);
                    return 1;
                }

                // Agora que removemos o nó da lista, devemos recolocá-lo no
                // ponto tal que seu contador é maior ou igual ao próximo.

                // Caso particular: removido deve vir em primeiro na lista
                if(no_removido->contador >= lista->contador) {
                    // Colocamos o no_removido na cabeça da lista
                    no_removido->proximo = lista;
                    lista = no_removido;

                    // imprimir_lista(lista);
                    // imprimir_lista_contador(lista);
                    // Continuamos para o próximo item se chegamos neste caso
                    continue;
                }

                // Se chegamos aqui, no_removido não deve estar na cabeça da
                // lista
                no_atual = lista;
                while(no_atual != NULL) {
                    if(no_atual->proximo != NULL &&
                    no_removido->contador >= no_atual->proximo->contador) {
                        // Colocamos a continuação da lista em no_removido
                        no_removido->proximo = no_atual->proximo;
                        // E re-inserimos o no_removido na lista
                        no_atual->proximo = no_removido;
                        break;
                    } else {
                        no_atual = no_atual->proximo;
                    }
                }

                // imprimir_lista(lista);
                // imprimir_lista_contador(lista);
            }
        }

        liberar_lista(&lista);
        printf("%d\n", custo_total);
    }

    free(requisicoes);
    return 0;
}

int inicializar_lista(Item **lista, int num_chaves) {
    /*
    * Inicializamos a lista de chaves, consideramos "1...N" do enunciado
    * como um intervalo inclusivo.
    */
    int i;
    for(i = 1; i <= num_chaves; i++) {
        if(!adicionar_item_no_fim(lista, i)) {
            liberar_lista(lista);
            return 0;
        }
    }

    return *lista != NULL;
}

int buscar_chave(Item *lista, Item **no, int *custo, int chave) {
    Item *no_atual = lista;
    *custo = 0;

    while(no_atual != NULL) {
        (*custo)++;
        // Buscamos a chave
        if(no_atual->chave == chave) {
            *no = no_atual;
            return 1;
        } else {
            no_atual = no_atual->proximo;
        }
    }
    return 0;
}

int colocar_na_cabeca(Item **lista, int chave) {
    Item *item_atual = *lista, *auxiliar = NULL;
    while(item_atual != NULL) {
        if(item_atual->proximo != NULL && item_atual->proximo->chave == chave) {
            auxiliar = item_atual->proximo;
            item_atual->proximo = auxiliar->proximo;
            auxiliar->proximo = *lista;
            *lista = auxiliar;
            return 1;
        } else {
            /*
            * item_atual->proximo é NULL ou não encontramos a chave desejada:
            * (a) iremos parar de pesquisar ao checarmos a condição do while,
            * (b) iremos continuar procurando dentro do próximo nó.
            */
            item_atual = item_atual->proximo;
        }
    }
    return 0;
}

void imprimir_lista_contador(Item *lista) {
    printf("Contador = {");
    while(lista != NULL) {
        printf("%d", lista->contador);
        if(lista->proximo != NULL)
            printf(", ");
        lista = lista->proximo;
    }
    printf("};\n");
}
