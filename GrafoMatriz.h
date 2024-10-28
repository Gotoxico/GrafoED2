#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

typedef struct grafo{
    int **adjacencia;
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

pGrafo criarGrafo(int n);
void destruirGrafo(pGrafo g);
void inserirAresta(pGrafo g, int u, int v);
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


#include "GrafoMatriz.c"
#endif