#include <stdio.h>
#include <stdlib.h>
#include "GrafoLista.h"

pGrafo criarGrafo(int n){
    int i;
    pGrafo g = (pGrafo) malloc(sizeof(GRAFO));
    g->n = n;
    g->adjacencia = (pNo*) malloc(n * sizeof(pNo));
    for(i = 0; i < n; i++){
        g->adjacencia[i] = NULL;
    }
    return g;
}

void liberarLista(pNo lista){
    if(lista != NULL){
        liberarLista(lista->prox);
        free(lista);
    }
}

void destruirGrafo(pGrafo g){
    int i;
    for(i = 0; i < g->n; i++){
        liberarLista(g->adjacencia[i]);
    }
    free(g->adjacencia);
    free(g);
}

pNo inserirNaLista(pNo lista, int v){
    pNo novo = (pNo) malloc(sizeof(NO));
    novo->v = v;
    novo->prox = lista;
    return novo;
}

void inserirAresta(pGrafo g, int u, int v){
    g->adjacencia[v] = inserirNaLista(g->adjacencia[v], u);
    g->adjacencia[u] = inserirNaLista(g->adjacencia[u], v);
}

pNo removerDaLista(pNo lista, int v){
    pNo proximo;
    if(lista == NULL){
        return NULL;
    }
    else{
        if(lista->v == v){
            proximo = lista->prox;
            free(lista);
            return proximo;
        }
        else{
            lista->prox = removerDaLista(lista->prox, v);
            return lista;
        }
    }
}

void removerAresta(pGrafo g, int u, int v){
    g->adjacencia[v] = removerDaLista(g->adjacencia[v], u);
    g->adjacencia[u] = removerDaLista(g->adjacencia[u], v);
}

int verificarAresta(pGrafo g, int u, int v){
    pNo t;
    for(t = g->adjacencia[u]; t != NULL; t = t->prox){
        if(t->v == v){
            return 1;
        }
    }
    return 0;
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
    int u;
    for(u = 0; u < g->n; u++){
        while(g->adjacencia[u] != NULL){
            printf("{%d,%d}", u, g->adjacencia[u]->v);
            g->adjacencia[u] = g->adjacencia[u]->prox;
        }
    }
}

int grau(pGrafo g, int u){
    int grau = 0;
    while(g->adjacencia[u] != NULL){
        grau++;
        g->adjacencia[u] = g->adjacencia[u]->prox;
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

int encontrarArestas(pGrafo g, int u, int v){
    while(g->adjacencia[u] != NULL){
        if(g->adjacencia[u]->v == v){
            return 1;
        }
        g->adjacencia[u] = g->adjacencia[u]->prox;
    }
    return 0;
}

void imprimirRecomendacoes(pGrafo g, int u){
    int v, w;
    while(g->adjacencia[u] != NULL){
        v = g->adjacencia[u]->v;
        while(g->adjacencia[v] != NULL){
            w = g->adjacencia[v]->v;
            if(!encontrarArestas(g, u, w)){
                printf("%d\n", w);
            }
            g->adjacencia[v] = g->adjacencia[v]->prox;
        }
        g->adjacencia[u] = g->adjacencia[u]->prox;
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
        if(g->adjacencia[v]->v == w && !visitado[w]){
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



