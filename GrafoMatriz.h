#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

typedef struct grafo{
    int **adjacencia;
    int n;
}GRAFO;

typedef GRAFO* pGrafo;

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


#include "GrafoMatriz.c"
#endif