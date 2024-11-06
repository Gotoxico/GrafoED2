#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

typedef struct noGrafo{
    int v;
    int peso;
}NOGRAFO;

typedef NOGRAFO* pNoGrafo;

typedef struct grafo{
    pNoGrafo** adjacencia;
    int n;
}GRAFO;

typedef GRAFO* pGrafo;

typedef struct nofila{
    int valor;
    struct nofila* prox;
}NOFILA;

typedef struct fila{
    NOFILA* inicio;
    NOFILA* fim;
}FILA;

typedef FILA* pFila;

typedef struct nopilha{
    int valor;
    struct nopilha* ant;
}NOPILHA;

typedef struct pilha{
    NOPILHA* topo;
}PILHA;

typedef PILHA* pPilha;

typedef struct item{
    int prioridade;
    int vertice;
}ITEM;

typedef struct fp{
    ITEM* v;
    int* indice;
    int n, tamanho;
}FP;

typedef FP* pFp;

pGrafo criarGrafo(int n);
void destruirGrafo(pGrafo g);
void inserirAresta(pGrafo g, int u, int v, int p);
void removerAresta(pGrafo g, int u, int v);
int verificarAresta(pGrafo g, int u, int v);
pGrafo lerGrafo();
void imprimirArestas(pGrafo g);
int grau(pGrafo g, int u);
int maisPopular(pGrafo g);
void imprimirRecomendacoes(pGrafo g, int u);
//Busca em Profundidade
//Buscar pra ver se existe caminho entre um ponto e outro
int buscaRec(pGrafo g, int *visitado, int v, int t);
int existeCaminho(pGrafo g, int s, int t);
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

#include "GrafoMatriz.c"
#endif