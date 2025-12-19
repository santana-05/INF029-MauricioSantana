#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 10

#include "trabalho2.h"

typedef struct {
    int *elementos;
    int quantidade_ocupada;
    int tamanho_alocado;
} EstruturaAuxiliar;

EstruturaAuxiliar *vetorPrincipal[TAM]; 

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho) {

    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1;

    if (vetorPrincipal[indice] != NULL) {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    if (tamanho < 1) {
        return TAMANHO_INVALIDO;
    }

    EstruturaAuxiliar *novaEstrutura = (EstruturaAuxiliar *) malloc(sizeof(EstruturaAuxiliar));
    if (novaEstrutura == NULL) {
        return SEM_ESPACO_DE_MEMORIA; 
    }
    
    novaEstrutura->elementos = (int *) malloc(tamanho * sizeof(int));
    if (novaEstrutura->elementos == NULL) {
        free(novaEstrutura);
        return SEM_ESPACO_DE_MEMORIA;
    }
    
    novaEstrutura->quantidade_ocupada = 0;
    novaEstrutura->tamanho_alocado = tamanho; 

    vetorPrincipal[indice] = novaEstrutura;

    return SUCESSO; 
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }
    
    int indice = posicao - 1;

    if (vetorPrincipal[indice] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    
    EstruturaAuxiliar *aux = vetorPrincipal[indice];

    if (aux->quantidade_ocupada < aux->tamanho_alocado) {
        aux->elementos[aux->quantidade_ocupada] = valor;
        aux->quantidade_ocupada++;
        return SUCESSO;
    } else {
        return SEM_ESPACO;
    }
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1; 

    if (vetorPrincipal[indice] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *aux = vetorPrincipal[indice];

    if (aux->quantidade_ocupada == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    aux->quantidade_ocupada--;
        
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1; 

    if (vetorPrincipal[indice] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *aux = vetorPrincipal[indice];

    if (aux->quantidade_ocupada == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    int i;
    int encontrado = 0;
    for (i = 0; i < aux->quantidade_ocupada; i++) {
        if (aux->elementos[i] == valor) {
            encontrado = 1;
            break; 
        }
    }

    if (!encontrado) {
        return NUMERO_INEXISTENTE; 
    }

    for (int j = i; j < aux->quantidade_ocupada - 1; j++) {
        aux->elementos[j] = aux->elementos[j+1];
    }

    aux->quantidade_ocupada--;

    return SUCESSO;    
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1; 

    if (vetorPrincipal[indice] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *aux = vetorPrincipal[indice];
    for (int i = 0; i < aux->quantidade_ocupada; i++) {
        vetorAux[i] = aux->elementos[i];
    }

    return SUCESSO;
}

int comparar(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int indice = posicao - 1;
    if (vetorPrincipal[indice] == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    EstruturaAuxiliar *aux = vetorPrincipal[indice];
    if (aux->quantidade_ocupada == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    memcpy(vetorAux, aux->elementos, aux->quantidade_ocupada * sizeof(int));
    qsort(vetorAux, aux->quantidade_ocupada, sizeof(int), comparar);

    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int k = 0;
    int algumaNaoVazia = 0;

    for (int i = 0; i < TAM; i++) {
        EstruturaAuxiliar *aux = vetorPrincipal[i];
        if (aux != NULL && aux->quantidade_ocupada > 0) {
            algumaNaoVazia = 1;
            for (int j = 0; j < aux->quantidade_ocupada; j++) {
                vetorAux[k++] = aux->elementos[j];
            }
        }
    }

    return algumaNaoVazia ? SUCESSO : TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int resultado = getDadosDeTodasEstruturasAuxiliares(vetorAux);

    if (resultado == SUCESSO) {
        int total = 0;
        for (int i = 0; i < TAM; i++) {
            if (vetorPrincipal[i] != NULL) {
                total += vetorPrincipal[i]->quantidade_ocupada;
            }
        }
        qsort(vetorAux, total, sizeof(int), comparar);
    }

    return resultado;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int indice = posicao - 1;
    EstruturaAuxiliar *aux = vetorPrincipal[indice];

    if (aux == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    int novoTam = aux->tamanho_alocado + novoTamanho;

    if (novoTam < 1)
        return NOVO_TAMANHO_INVALIDO;

    int *novoArray = realloc(aux->elementos, novoTam * sizeof(int));
    if (novoArray == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    aux->elementos = novoArray;
    aux->tamanho_alocado = novoTam;

    if (aux->quantidade_ocupada > novoTam)
        aux->quantidade_ocupada = novoTam;

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int indice = posicao - 1;
    EstruturaAuxiliar *aux = vetorPrincipal[indice];

    if (aux == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    if (aux->quantidade_ocupada == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    return aux->quantidade_ocupada;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
     No *cabecote = (No *) malloc(sizeof(No));
    if (!cabecote)
        return NULL;

    cabecote->prox = NULL;
    No *atual = cabecote;
    int temElementos = 0;

    for (int i = 0; i < TAM; i++) {
        EstruturaAuxiliar *estrutura = vetorPrincipal[i];
        if (estrutura && estrutura->quantidade_ocupada > 0) {
            for (int j = 0; j < estrutura->quantidade_ocupada; j++) {
                No *novo = (No *) malloc(sizeof(No));
                if (!novo) {
                    destruirListaEncadeadaComCabecote(&cabecote);
                    return NULL;
                }
                novo->conteudo = estrutura->elementos[j];
                novo->prox = NULL;
                atual->prox = novo;
                atual = novo;
                temElementos = 1;
            }
        }
    }

    if (!temElementos) {
        free(cabecote);
        return NULL;
    }

    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    No *atual = inicio->prox; 
    int i = 0;
    while (atual != NULL) {
        vetorAux[i++] = atual->conteudo;
        atual = atual->prox;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No *atual = *inicio;
    while (atual != NULL) {
        No *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i] = NULL;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            free(vetorPrincipal[i]->elementos); 
            free(vetorPrincipal[i]);           
            vetorPrincipal[i] = NULL;
        }
    }
}
