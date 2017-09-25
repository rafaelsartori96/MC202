#ifndef ARVORE_BIN_BUSCA_AUX_H
#define ARVORE_BIN_BUSCA_AUX_H


/**
* Função auxiliar para criar_filho_esquerda, criar_filho_direita e criar_raiz.
*
* Retorna   -1  quando não for possível alocar memória para o nó,
*            0  caso exista filho na variável dada e
*            1  caso for possível.
*/
int criar_no(No **no);

/**
* A função cria um filho a esquerda do nó pai dado.
*
* Retorna   -1  se não foi possível alocar memória para o filho,
*            0  se existe filho a esquerda no pai,
*            1  se criamos e substituímos o ponteiro 'pai->esquerda'.
*/
int criar_filho_esquerda(No *pai);

/**
* A função cria um filho a direita do nó pai dado.
*
* Retorna   -1  se não foi possível alocar memória para o filho,
*            0  se existe filho a direita no pai,
*            1  se criamos e substituímos o ponteiro 'pai->direita'.
*/
int criar_filho_direita(No *pai);

/**
* A função cria um nó raiz em 'arvore'.
*
* Retorna   -1  se não foi possível alocar memória para o nó,
*            0  se existe raiz,
*            1  se criamos e substituímos o ponteiro 'arvore->raiz'.
*/
int criar_raiz(ArvoreBinariaBusca *arvore);

/**
* Procura o sucessor do nó 'atual' na árvore binária de busca e modificamos o
* apontador 'sucessor' caso encontramos.
*
* Sucessor é definido na prática como a chave numéricamente imediatamente acima
* de 'atual->chave' na árvore.
*
* Retorna   0   caso não haja sucessor,
*           1   caso encontramos um sucessor.
*/
int sucessor(No *atual, No **sucessor);

/** Função auxiliar para inserir(ArvoreBinariaBusca, int) */
int inserir_r(int chave, No *raiz);

/** Função auxiliar para remover(ArvoreBinariaBusca, int) */
void mudar_filho(ArvoreBinariaBusca *arvore, No *filho_atual, No *novo_filho);

/** Função auxiliar recursiva para pertence(ArvoreBinariaBusca, int) */
int buscar(No *raiz, int chave, No **busca);

/** Função auxiliar recursiva para buscar(No *, int, No **) */
int buscar_r(No *raiz, int chave, No **busca);

/** Função auxiliar para minimo(ArvoreBinariaBusca, No **) */
int minimo_aux(No *raiz, No **minimo);

/** Função auxiliar para maximo(ArvoreBinariaBusca, No **) */
int maximo_aux(No *raiz, No **maximo);

/** Função auxiliar recursiva a limpar_arvore. Utiliza pós-ordem. */
void limpar_arvore_r(No *raiz);

/** Função auxiliar recursiva a imprimir_pre_ordem. */
void imprimir_pre_ordem_r(No *raiz);

/** Função auxiliar recursiva a imprimir_em_ordem. */
void imprimir_em_ordem_r(No *raiz);

/** Função auxiliar recursiva a imprimir_pos_ordem. */
void imprimir_pos_ordem_r(No *raiz);

/**
* Função auxiliar recursiva a imprimir_em_largura.
*
* Retorna   1   caso imprimimos algum elemento,
*           0   caso não imprimimos nenhum elemento (nível vazio).
*/
int imprimir_em_largura_r(int nivel_atual, int nivel_alvo, No *raiz);


#endif /* ARVORE_BIN_BUSCA_AUX_H */
