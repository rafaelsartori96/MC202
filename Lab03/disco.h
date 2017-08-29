/* Rafael Sartori Martins dos Santos (RA: 186154) */
#ifndef DISCO_H
#define DISCO_H


/**
* Estrutura que representa arquivo na memória do disco.
*
* Utilizaremos, como unidade de espaço ocupado em disco, kb.
*/
typedef struct Arquivo {
    /** Endereço inicial em kb do bloco */
    int endereco_inicio;
    /** Tamanho em kb do bloco */
    int tamanho;
    /** Nome do arquivo, '\0' se for espaço em branco */
    char nome_arquivo[11];
    /** Apontador para o próximo bloco */
    struct Arquivo *proximo;
} Arquivo;

/**
* Estrutura que representa o disco.
*
* Sua capacidade é no máximo 1023Gb, ou seja, se utilizarmos Kb, podemos usar
* int.
*/
typedef struct Disco {
    /** Capacidade do disco em kb */
    int capacidade;
    /** Espaço ocupado por arquivos em kb */
    int espaco_ocupado;
    /** Lista de arquivos em disco */
    Arquivo *arquivo_inicial;
} Disco;


/**
* Esta função cria um disco na variável dada.
*
* Retorna    1  se o discro foi criado com sucesso,
*           -1  se houve erro de alocação de memória.
*/
int criar_disco(int capacidade, Disco **disco);

/**
* Libera todas as informações alocadas dinâmicamente de disco.
*/
void liberar_disco(Disco **disco);

/**
* Esta função procura em Disco o menor bloco livre cujo tamanho excede 'tamanho'
* dado e retorna o arquivo anterior a ele, para que possamos inserir na lista.
*
* Retorna    1  se encontramos um bloco livre, modificando a variável
*               'endereco_encontrado' se o endereço encontrado não for o início
*               da lista,
*            0  se não será possível um bloco livre do tamanho requisitado.
*/
int procurar_menor_bloco_livre(Disco *disco, int tamanho, Arquivo **arquivo_anterior);

/**
* Esta função otimiza o disco, eliminando espaços livres entre arquivos,
* mantendo-os no final do disco.
*
* Retorna o último arquivo do disco, que é usado em "procurar_menor_bloco_livre"
* por exemplo.
*/
Arquivo * otimizar_disco(Disco *disco);

/**
* Esta função remove arquivos do disco pelo nome, liberando sua memória e
* contabilizando em "espaco_ocupado" do disco.
*
* Retorna   1   se o arquivo foi removido,
*           0   se o arquivo não foi encontrado.
*/
int remover_arquivo(Disco *disco, char nome_do_arquivo[11]);

/**
* Esta função insere arquivos no menor bloco livre cujo tamanho seja maior que
* o tamanho do arquivo.
*
* Retorna    1  se foi inserido corretamente,
*            0  se não há espaço no disco,
*           -1  se ocorreu uma falha ao alocar memória para a estrutura do
*               arquivo.
*/
int inserir_no_disco(Disco *disco, int tamanho, char nome_arquivo[11]);

/**
* Imprime uma representação do disco
*/
void imprimir_disco(Disco *disco);


#endif /* DISCO_H */
