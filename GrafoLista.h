#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

typedef struct no{
    int v;
    struct no *prox;
}NO;

typedef NO* pNo;

typedef struct grafo{
    pNo* adjacencia;
    int n; 
}GRAFO;

typedef GRAFO* pGrafo;

pGrafo criarGrafo(int n);
void liberarLista(pNo lista);
void destruirGrafo(pGrafo g);
pNo inserirNaLista(pNo lista, int v);
void inserirAresta(pGrafo g, int u, int v);
pNo removerDaLista(pNo lista, int v);
void removerAresta(pGrafo g, int u, int v);
int verificarAresta(pGrafo g, int u, int v);
pGrafo lerGrafo();
void imprimirArestas(pGrafo g);
int grau(pGrafo g, int u);
int maisPopular(pGrafo g);
int encontrarArestas(pGrafo g, int u, int v);
void imprimirRecomendacoes(pGrafo g, int u);


#include "GrafoLista.c"
#endif