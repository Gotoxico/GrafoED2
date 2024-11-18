#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

/// @brief Estrutura de nó de lista
typedef struct no{
    int v;
    int peso;
    struct no *prox;
}NO;

/// @brief Ponteiro para nó
typedef NO* pNo;

/// @brief Estrutura de grafo
typedef struct grafo{
    pNo* adjacencia;
    int n; 
}GRAFO;

/// @brief Ponteiro para grafo
typedef GRAFO* pGrafo;

/// @brief Estrutura de nó de fila
typedef struct nofila{
    int valor;
    struct nofila* prox;
}NOFILA;

/// @brief Estrutura de fila
typedef struct fila{
    NOFILA* inicio;
    NOFILA* fim;
}FILA;

/// @brief Ponteiro para fila
typedef FILA* pFila;

/// @brief Estrutura de nó de pilha
typedef struct nopilha{
    int valor;
    struct nopilha* ant;
}NOPILHA;

/// @brief Estrutura de pilha
typedef struct pilha{
    NOPILHA* topo;
}PILHA;

/// @brief Ponteiro para pilha
typedef PILHA* pPilha;

/// @brief Estrutura de item
typedef struct item{
    int prioridade;
    int vertice;
}ITEM;

/// @brief Estrutura de fila de prioridade
typedef struct fp{
    ITEM* v;
    int* indice;
    int n, tamanho;
}FP;

/// @brief Ponteiro para fila de prioridade
typedef FP* pFp;

//Funções 
pGrafo criarGrafo(int n);
void liberarLista(pNo lista);
void destruirGrafo(pGrafo g);
pNo inserirNaLista(pNo lista, int v, int peso);
void inserirAresta(pGrafo g, int u, int v, int peso);
pNo removerDaLista(pNo lista, int v);
void removerAresta(pGrafo g, int u, int v);
int verificarAresta(pGrafo g, int u, int v);
pGrafo lerGrafo();
void imprimirArestas(pGrafo g);
int grau(pGrafo g, int u);
int maisPopular(pGrafo g);
int encontrarArestas(pGrafo g, int u, int v);
void imprimirRecomendacoes(pGrafo g, int u);
//Busca em Profundidade
//Criar caminho entre todos os pontos
void buscaEmProfundidade(pGrafo g, int *pai, int p, int v);
int* encontrarCaminhos(pGrafo g, int s);
//Criar caminho entre todos os pontos utilizando Pilha
PILHA* criarPilha();
void destruirPilha(PILHA* pilha);
void empilhar(PILHA* pilha, int s);
int desempilhar(PILHA* pilha);
int pilhaVazia(PILHA* pilha);
int* buscaEmProfundidadePilha(pGrafo g, int s);
void imprimirCaminhoReverso(int v, int *pai);
void imprimirCaminho(int v, int *pai);
//Buscar pra ver se existe caminho entre um ponto e outro
int buscaRec(pGrafo g, int *visitado, int v, int t);
int existeCaminho(pGrafo g, int s, int t);
//End Busca em Profundidade
void visitarRec(pGrafo g, int *componentes, int comp, int v);
int* encontrarComponentes(pGrafo g);
//Busca em Largura
FILA* criarFila();
void destruirFila(FILA* fila);
void enfileirar(FILA* fila, int s);
int desenfileirar(FILA* fila);
int filaVazia(FILA* fila);
int* buscaEmLargura(pGrafo g, int s);
//End Busca em Largura
//Ordenacao Topologica
void visitarRec2(pGrafo g, int *visitado, int v);
void ordenacaoTopologica(pGrafo g);
//End Ordenacao Topologica
//Dijkstra
pFp criarFprio(int tamanho);
void inserirFprio(pFp fprio, int vertice, int prioridade);
int extrairMinimo(pFp fprio);
int prioridade(pFp fprio, int vertice);
void diminuirPrioridade(pFp fprio, int vertice, int novaPrioridade);
int vazia(pFp fprio);
int* dijkstra(pGrafo g, int s);
//End Dijkstra
//Arvore Geradora Minima
int* prim(pGrafo g, int s);
//End Arvore Geradora Minima

#include "GrafoLista.c"
#endif