#include <stdio.h>
#include <stdlib.h>
#include "GrafoMatriz.h"

pGrafo criarGrafo(int n){
    int i, j;
    pGrafo g = (pGrafo) malloc(sizeof(GRAFO));
    g->n = n;
    g->adjacencia = (int**) malloc(n * sizeof(int *));
    for(i = 0; i < n; i++){
        g->adjacencia[i] = (int*) malloc(n * sizeof(int));
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            g->adjacencia[i][j] = 0;
        }
    }
    return g;
}

void destruirGrafo(pGrafo g){
    int i;
    for(i = 0; i < g->n; i++){
        free(g->adjacencia[i]);
    }
    free(g->adjacencia);
    free(g);
}

void inserirAresta(pGrafo g, int u, int v){
    g->adjacencia[u][v] = 1;
    g->adjacencia[v][u] = 1;
}

void removerAresta(pGrafo g, int u, int v){
    g->adjacencia[u][v] = 0;
    g->adjacencia[v][u] = 0;
}

int verificarAresta(pGrafo g, int u, int v){
    return g->adjacencia[u][v];
}

pGrafo lerGrafo(){
    int n, m, i, u, v;
    pGrafo g;
    printf("Digite Tamanho Grafo: \n");
    scanf("%d", &n);
    printf("Digite Quantidade de Aresta: \n");
    scanf("%d", &m);
    g = criarGrafo(n);
    for(i = 0; i < m; i++){
        printf("Digite Aresta 1: \n");
        scanf("%d", &u);
        printf("Digite Aresta 2: \n");
        scanf("%d", &v);
        inserirAresta(g, u, v);
    }
    return g;
}

void imprimirArestas(pGrafo g){
    int u, v;
    for(u = 0; u < g->n; u++){
        for(v = u + 1; v < g->n; v++){
            if(g->adjacencia[u][v]){
                printf("{%d,%d}", u, v);
            }
        }
    }
}

int grau(pGrafo g, int u){
    int v, grau = 0;
    for(v = 0; v < g->n; v++){
        if(g->adjacencia[u][v]){
            grau++;
        }
    }
    return grau;
}

int maisPopular(pGrafo g){
    int u, max, grauMax, grauAtual;
    max = 0;
    grauMax = grau(g, 0);
    for(u = 1; u < g->n; u++){
        grauAtual = grau(g, u);
        if(grauAtual > grauMax){
            grauMax = grauAtual;
            max = u;
        }
    }
    return max;
}

void imprimirRecomendacoes(pGrafo g, int u){
    int v, w;
    for(v = 0; v < g->n; v++){
        if(g->adjacencia[u][v]){
            for(w = 0; w < g->n; w++){
                if(g->adjacencia[v][w] && w != u && !g->adjacencia[u][w]){
                    printf("%d\n", w);
                }
            }
        }
    }
}

//Busca em Profundidade
int buscaRec(pGrafo g, int *visitado, int v, int t){
    int w;
    if(v == t){
        return 1;
    }
    visitado[v] = 1;
    for(w = 0; w < g->n; w++){
        if(g->adjacencia[v][w] && !visitado[w]){
            if(buscaRec(g, visitado, w, t)){
                return 1;
            }
        }
    }
    return 0;
}

int existeCaminho(pGrafo g, int s, int t){
    int encontrou, i, *visitado = (int*) malloc(g->n * sizeof(int));
    for(i = 0; i < g->n; i++){
        visitado[i] = 0;
    }
    encontrou = buscaRec(g, visitado, s, t);
    free(visitado);
    return encontrou;
}