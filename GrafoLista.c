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
//Criar caminho entre todos os pontos
void buscaEmProfundidade(pGrafo g, int *pai, int p, int v){
    pNo t;
    pai[v] = p;
    for(t = g->adjacencia[v]; t != NULL; t = t->prox){
        if(pai[t->v] == -1){
            buscaEmProfundidade(g, pai, v, t->v);
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

//Buscar pra ver se existe caminho entre um ponto e outro
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
    pNo t;
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
        for(t = g->adjacencia[v]; t != NULL; t = t->prox){
            w = g->adjacencia[v]->v;
            if(!visitado[w]){
                pai[w] = v;
                empilhar(p, w);
            }
        }
    }
    destruirPilha(p);
    free(visitado);
    return pai;
}

//End Busca em Profundidade

void visitarRec(pGrafo g, int *componentes, int comp, int v){
    pNo t;
    componentes[v] = comp;
    for(t = g->adjacencia[v]; t != NULL; t = t->prox){
        if(componentes[t->v] == -1){
            visitarRec(g, componentes, comp, t->v);
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
    pNo t;
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
        for(t = g->adjacencia[v]; t != NULL; t = t->prox){
            w = t->v;
            if(!visitado[w]){
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


