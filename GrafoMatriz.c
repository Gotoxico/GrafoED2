#include <stdio.h>
#include <stdlib.h>
#include "GrafoMatriz.h"
#include <limits.h>

pGrafo criarGrafo(int n){
    int i, j;
    pGrafo g = (pGrafo) malloc(sizeof(GRAFO));
    g->n = n;
    g->adjacencia = (pNoGrafo**) malloc(n * sizeof(pNoGrafo *));
    for(i = 0; i < n; i++){
        g->adjacencia[i] = (pNoGrafo*) malloc(n * sizeof(pNoGrafo));
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            g->adjacencia[i][j]->v = 0;
            g->adjacencia[i][j]->peso = 0;
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

void inserirAresta(pGrafo g, int u, int v, int p){
    g->adjacencia[u][v]->v = 1;
    g->adjacencia[v][u]->v = 1;
    g->adjacencia[u][v]->peso = p;
    g->adjacencia[v][u]->peso = p;
}

void removerAresta(pGrafo g, int u, int v){
    g->adjacencia[u][v]->v = 0;
    g->adjacencia[v][u]->v = 0;
    g->adjacencia[u][v]->peso = 0;
    g->adjacencia[v][u]->peso = 0;
}

int verificarAresta(pGrafo g, int u, int v){
    return g->adjacencia[u][v]->v;
}

pGrafo lerGrafo(){
    int n, m, i, u, v, p;
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
        printf("Digite Peso Aresta: \n");
        scanf("%d", &p);
        inserirAresta(g, u, v, p);
    }
    return g;
}

void imprimirArestas(pGrafo g){
    int u, v;
    for(u = 0; u < g->n; u++){
        for(v = u + 1; v < g->n; v++){
            if(g->adjacencia[u][v]->v){
                printf("{%d,%d} %d", u, v, g->adjacencia[u][v]->peso);
            }
        }
    }
}

int grau(pGrafo g, int u){
    int v, grau = 0;
    for(v = 0; v < g->n; v++){
        if(g->adjacencia[u][v]->v){
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
        if(g->adjacencia[u][v]->v){
            for(w = 0; w < g->n; w++){
                if(g->adjacencia[v][w]->v && w != u && !g->adjacencia[u][w]->v){
                    printf("%d\n", w);
                }
            }
        }
    }
}

//Busca em Profundidade
//Buscar pra ver se existe caminho entre um ponto e outro
int buscaRec(pGrafo g, int *visitado, int v, int t){
    int w;
    if(v == t){
        return 1;
    }
    visitado[v] = 1;
    for(w = 0; w < g->n; w++){
        if(g->adjacencia[v][w]->v && !visitado[w]){
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

//Criar caminho entre todos os pontos
void buscaEmProfundidade(pGrafo g, int *pai, int p, int v){
    pai[v] = p;
    for(int u = 0; u < g->n; u++){
        if(g->adjacencia[u][v]->v){
            if(pai[u] == -1){
                buscaEmProfundidade(g, pai, v, u);
            }
        }
    }
}

int* encontrarCaminhos(pGrafo g, int s){
    int i, *pai = (int*) malloc(g->n * sizeof(int));
    for(i = 0; i < g->n; i++){
        pai[i] = -1;
    }
    buscaEmProfundidade(g, pai, s, s);
    return pai;
}

//Criar caminho entre todos os pontos utilizando Pilha
PILHA* criarPilha(){
    PILHA* p = (PILHA*) malloc(sizeof(PILHA));
    p->topo = NULL;
    return p;
}

void destruirPilha(PILHA* pilha){
    free(pilha);
}

void empilhar(PILHA* pilha, int s){
    NOPILHA* novoNo = (NOPILHA*) malloc(sizeof(NOPILHA));
    novoNo->valor = s;
    if(pilha == NULL){
        pilha = criarPilha();
        novoNo->ant = NULL;
        pilha->topo = novoNo;
    }
    else{
        novoNo->ant = pilha->topo;
        pilha->topo = novoNo;
    }
}

int desempilhar(PILHA* pilha){
    if(pilha == NULL){
        return NULL;
    }
    else{
        NOPILHA* aux = pilha->topo;
        pilha->topo = pilha->topo->ant;
        return aux->valor;
        free(aux);
    }
}

int pilhaVazia(PILHA* pilha){
    if(pilha->topo == NULL){
        return 1;
    }
    return 0;
}

int* buscaEmProfundidadePilha(pGrafo g, int s){
    int w, v, *pai = (int*) malloc(g->n * sizeof(int)), *visitado = (int*) malloc(g->n * sizeof(int));
    pPilha p = criarPilha();
    for(v = 0; v < g->n; v++){
        pai[v] = -1;
        visitado[v] = 0;
    }
    empilhar(p, s);
    pai[s] = s;
    while(!pilhaVazia(p)){
        v = desempilhar(p);
        visitado[v] = 1;
        for(w = 0; w < g->n; w++){
            if(g->adjacencia[v][w]->v && !visitado[w]){
                pai[w] = v;
                empilhar(p, w);
            }
        }
    }
    destruirPilha(p);
    free(visitado);
    return pai;
}

void imprimirCaminhoReverso(int v, int *pai){
    printf("%d\t", v);
    if(pai[v] != v){
        imprimirCaminhoReverso(pai[v], pai);
    }
}

void imprimirCaminho(int v, int *pai){
    if(pai[v] != v){
        imprimirCaminho(pai[v], pai);
    }
    printf("%d\t", v);
}

//End Busca em Profundidade
void visitarRec(pGrafo g, int *componentes, int comp, int v){
    componentes[v] = comp;
    for(int u = 0; u < g->n; u++){
        if(g->adjacencia[u][v]->v){
            if(componentes[u] == -1){
                visitarRec(g, componentes, comp, u);
            }
        }
    }
}

int* encontrarComponentes(pGrafo g){
    int s, c = 0, *componentes = (int*) malloc(g->n * sizeof(int));
    for(s = 0; s < g->n; s++){
        componentes[s] = -1;
    }
    for(s = 0; s < g->n; s++){
        if(componentes[s] == -1){
            visitarRec(g, componentes, c, s);
            c++;
        }
    }
    return componentes;
}

//Busca em Largura
FILA* criarFila(){
    FILA* f = (FILA*) malloc(sizeof(FILA));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void destruirFila(FILA* fila){
    free(fila);
}

void enfileirar(FILA* fila, int s){
    NOFILA* novoNo = (NOFILA*) malloc(sizeof(NOFILA));
    novoNo->valor = s;
    novoNo->prox = NULL;

    if(fila == NULL){
        fila = criarFila();
        fila->inicio = novoNo;
        fila->fim = novoNo;
    }
    else{
        fila->fim->prox = novoNo;
    }
}

int desenfileirar(FILA* fila){
    if(fila == NULL){
        return NULL;
    }
    else{
        NOFILA* aux = fila->inicio;
        fila->inicio = fila->inicio->prox;
        return aux->valor;
        free(aux);
    }
}

int filaVazia(FILA* fila){
    if(fila->inicio == NULL){
        return 1;
    }
    return 0;
}

int* buscaEmLargura(pGrafo g, int s){
    int w, v;
    int *pai = (int*) malloc(g->n * sizeof(int));
    int *visitado = (int*) malloc(g->n * sizeof(int));
    pFila f = criarFila();
    for(v = 0; v < g->n; v++){
        pai[v] = -1;
        visitado[v] = 0;
    }
    enfileirar(f, s);
    pai[s] = s;
    visitado[s] = 1;
    while(!filaVazia(f)){
        v = desenfileirar(f);
        for(w = 0; w < g->n; w++){
            if(g->adjacencia[v][w]->v && !visitado[w]){
                visitado[w] = 1;
                pai[w] = v;
                enfileirar(f, w);
            }
        }
    }
    destruirFila(f);
    free(visitado);
    return pai;
}
//End Busca em Largura

//Ordenacao Topologica
void visitarRec2(pGrafo g, int *visitado, int v){
    int u;
    visitado[v] = 1;
    for(u = 0; u < g->n; u++){
        if(g->adjacencia[v][u]->v){
            if(!visitado[u]){
                visitarRec2(g, visitado, u);
            }
        }
    }
    printf("%d ", v);
}

void ordenacaoTopologica(pGrafo g){
    int s, *visitado = (int*) malloc(g->n * sizeof(int));
    for(s = 0; s < g->n; s++){
        visitado[s] = 0;
    }
    for(s = 0; s < g->n; s++){
        if(!visitado[s]){
            visitarRec2(g, visitado, s);
        }
    }
    free(visitado);
    printf("\n");
}
//End Ordenacao Topologica
//Dijkstra
pFp criarFprio(int tamanho){
    pFp fprio = (pFp) malloc(sizeof(FP));
    fprio->v = (ITEM*) malloc(tamanho * sizeof(ITEM));
    fprio->indice = (int*) malloc(tamanho * sizeof(int));
    fprio->n = 0;
    fprio->tamanho = tamanho;
    for(int i = 0; i < tamanho; i++){
        fprio->indice[i] = -1;
    }
    return fprio;
}

void inserirFprio(pFp fprio, int vertice, int prioridade){
    if(fprio->n >= fprio->tamanho){
        return;
    }
    fprio->v[fprio->n].vertice = vertice;
    fprio->v[fprio->n].prioridade = prioridade;
    fprio->indice[vertice] = fprio->n;

    int pos = fprio->n;
    while(pos > 0 && fprio->v[(pos - 1) / 2].prioridade > fprio->v[pos].prioridade){
        ITEM temp = fprio->v[pos];
        fprio->v[pos] = fprio->v[(pos - 1) / 2];
        fprio->v[(pos - 1) / 2] = temp;

        fprio->indice[fprio->v[pos].vertice] = pos;
        fprio->indice[fprio->v[(pos - 1) / 2].vertice] = (pos - 1) / 2;

        pos = (pos - 1) / 2;
    }

    fprio->n++;
}

int extrairMinimo(pFp fprio){
    if(fprio->n == 0){
        return NULL;
    }

    int verticeMinimo = fprio->v[0].vertice;
    fprio->indice[verticeMinimo] = -1;

    fprio->n--;

    fprio->v[0] = fprio->v[fprio->n];
    fprio->indice[fprio->v[0].vertice] = 0;

    int pos = 0;
    while(1){
        int esquerda = 2 * pos + 1;
        int direita = 2 * pos + 2;
        int menor = pos;

        if(esquerda < fprio->n && fprio->v[esquerda].prioridade < fprio->v[menor].prioridade){
            menor = esquerda;
        }
        if(direita < fprio->n && fprio->v[direita].prioridade < fprio->v[menor].prioridade){
            menor = direita;
        }

        if(menor == pos){
            break;
        }

        ITEM temp = fprio->v[pos];
        fprio->v[pos] = fprio->v[menor];
        fprio->v[menor] = temp;

        fprio->indice[fprio->v[pos].vertice] = pos;
        fprio->indice[fprio->v[menor].vertice] = menor;

        pos = menor;
    }
    return verticeMinimo;
}

int prioridade(pFp fprio, int vertice){
    int pos = fprio->indice[vertice];
    if(pos == -1){
        return NULL;
    }
    return fprio->v[pos].prioridade;
}

void diminuirPrioridade(pFp fprio, int vertice, int novaPrioridade){
    int pos = fprio->indice[vertice];
    if(pos = -1){
        return;
    }
    if(novaPrioridade < fprio->v[pos].prioridade){
        fprio->v[pos].prioridade = novaPrioridade;

        while(pos > 0 && fprio->v[(pos - 1) / 2].prioridade > fprio->v[pos].prioridade){
            ITEM temp = fprio->v[pos];
            fprio->v[pos] = fprio->v[(pos - 1) / 2];
            fprio->v[(pos - 1) / 2] = temp;

            fprio->indice[fprio->v[pos].vertice] = pos;
            fprio->indice[fprio->v[(pos - 1) / 2].vertice] = (pos - 1) / 2;

            pos = (pos - 1) / 2;
        }
    }
}

int vazia(pFp fprio){
    if(fprio->n == 0){
        return 1;
    }
    return 0;
}

int* dijkstra(pGrafo g, int s){
    int v, u, *pai = (int*) malloc(g->n * sizeof(int));
    pFp h = criarFprio(g->n);
    for(v = 0; v < g->n; v++){
        pai[v] = -1;
        inserirFprio(h, v, INT_MAX);
    }
    pai[s] = s;
    diminuirPrioridade(h, s, 0);
    while(!vazia(h)){
        v = extrairMinimo(h);
        if(prioridade(h, v) != INT_MAX){
            for(u = 0; u < g->n; u++){
                if(g->adjacencia[u][v]->v){
                    pNoGrafo t = g->adjacencia[u][v];
                    if(prioridade(h, v) + t->peso < prioridade(h, t->v)){
                        diminuirPrioridade(h, t->v, prioridade(h, v) + t->peso);
                        pai[t->v] = v;
                    }
                }
                
            }
        }
    }
    free(h);
    return pai;
}
//End Dijkstra
//Arvore Geradora Minima
int* prim(pGrafo g, int s){
    int v, u, *pai = (int*) malloc(g->n * sizeof(int));
    pFp h = criarFprio(g->n);
    for(v = 0; v < g->n; v++){
        pai[v] = -1;
        inserirFprio(h, v, INT_MAX);
    }
    pai[s] = s;
    diminuirPrioridade(h, s, 0);
    while(!vazia(h)){
        v = extrairMinimo(h);
        for(u = 0; u < g->n; u++){
            if(g->adjacencia[u][v]->v){
                pNoGrafo t = g->adjacencia[u][v];
                if(t->peso < prioridade(h, t->v)){
                    diminuirPrioridade(h, t->v, t->peso);
                    pai[t->v] = v;
                }
            }
                
        }
    }
    free(h);
    return pai;
}
//End Arvore Gerado Minima