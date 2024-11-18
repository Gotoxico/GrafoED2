#include <stdio.h>
#include <stdlib.h>
#include "GrafoLista.h"
#include <limits.h>

/// @brief Função para criar um grafo
/// @param n Inteiro que representa o tamanho do grafo
/// @return pGrafo Ponteiro para o grafo criado
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

/// @brief Função para liberar uma lista
/// @param lista Ponteiro para a lista a ser liberada
void liberarLista(pNo lista){
    if(lista != NULL){
        liberarLista(lista->prox);
        free(lista);
    }
}

/// @brief Função para destruir um grafo
/// @param g Ponteiro para o grafo a ser destruído
void destruirGrafo(pGrafo g){
    int i;
    for(i = 0; i < g->n; i++){
        liberarLista(g->adjacencia[i]);
    }
    free(g->adjacencia);
    free(g);
}

/// @brief Função para inserir um nó na lista
/// @param lista Ponteiro para a lista
/// @param v Inteiro que representa o vértice
/// @param peso Inteiro que representa o peso
/// @return pNo Ponteiro para o nó inserido
pNo inserirNaLista(pNo lista, int v, int peso){
    pNo novo = (pNo) malloc(sizeof(NO));
    novo->v = v;
    novo->peso = peso;
    novo->prox = lista;
    return novo;
}

/// @brief Função para inserir uma aresta no grafo
/// @param g Ponteiro para o grafo
/// @param u Inteiro que representa o primeiro vértice
/// @param v Inteiro que representa o segundo vértice
/// @param peso Inteiro que representa o peso da aresta
void inserirAresta(pGrafo g, int u, int v, int peso){
    g->adjacencia[v] = inserirNaLista(g->adjacencia[v], u, peso);
    g->adjacencia[u] = inserirNaLista(g->adjacencia[u], v, peso);
}

/// @brief Função para remover um nó da lista
/// @param lista Ponteiro para a lista
/// @param v Inteiro que representa o vértice
/// @return pNo Ponteiro para o nó removido
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

/// @brief Função para remover uma aresta do grafo
/// @param g Ponteiro para o grafo
/// @param u Inteiro que representa o primeiro vértice
/// @param v Inteiro que representa o segundo vértice
void removerAresta(pGrafo g, int u, int v){
    g->adjacencia[v] = removerDaLista(g->adjacencia[v], u);
    g->adjacencia[u] = removerDaLista(g->adjacencia[u], v);
}

/// @brief Função para verificar se uma aresta existe no grafo
/// @param g Ponteiro para o grafo
/// @param u Inteiro que representa o primeiro vértice
/// @param v Inteiro que representa o segundo vértice
/// @return int 1 se a aresta existe, 0 caso contrário
int verificarAresta(pGrafo g, int u, int v){
    pNo t;
    for(t = g->adjacencia[u]; t != NULL; t = t->prox){
        if(t->v == v){
            return 1;
        }
    }
    return 0;
}

/// @brief Função para ler um grafo
/// @return pGrafo Ponteiro para o grafo lido
pGrafo lerGrafo(){
    int n, m, i, u, v, p;
    pGrafo g;
    printf("Digite Tamanho Grafo: \n");
    scanf("%d", &n);
    printf("Digite Quantidade de Aresta: \n");
    scanf("%d", &m);
    g = criarGrafo(n);
    for(i = 0; i < m; i++){
        printf("Digite Vertice 1: \n");
        scanf("%d", &u);
        printf("Digite Vertice 2: \n");
        scanf("%d", &v);
        printf("Digite Peso Aresta: \n");
        scanf("%d", &p);
        inserirAresta(g, u, v, p);
    }
    return g;
}

/// @brief Função para imprimir as arestas do grafo
/// @param g Ponteiro para o grafo
void imprimirArestas(pGrafo g){
    int u;
    for(u = 0; u < g->n; u++){
        pNo t = g->adjacencia[u];
        while(t != NULL){
            printf("{%d,%d} %d ", u, t->v, t->peso);
            t = t->prox;
        }
    }
}

/// @brief Função para calcular o grau de um vértice
/// @param g Ponteiro para o grafo
/// @param u Inteiro que representa o vértice
/// @return int Grau do vértice
int grau(pGrafo g, int u){
    int grau = 0;
    while(g->adjacencia[u] != NULL){
        grau++;
        g->adjacencia[u] = g->adjacencia[u]->prox;
    }
    return grau;
}

/// @brief Função para calcular o vértice mais popular
/// @param g Ponteiro para o grafo
/// @return int Vértice mais popular
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

/// @brief Função para encontrar as arestas de um vértice
/// @param g Ponteiro para o grafo
/// @param u Inteiro que representa o vértice
/// @param v Inteiro que representa o vértice
/// @return int 1 se a aresta existe, 0 caso contrário
int encontrarArestas(pGrafo g, int u, int v){
    while(g->adjacencia[u] != NULL){
        if(g->adjacencia[u]->v == v){
            return 1;
        }
        g->adjacencia[u] = g->adjacencia[u]->prox;
    }
    return 0;
}

/// @brief Função para imprimir as recomendações de um vértice
/// @param g Ponteiro para o grafo
/// @param u Inteiro que representa o vértice
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

/// @brief Função para Busca em Profundidade
/// @param g Ponteiro para o grafo
/// @param pai Vetor de inteiros que representa os pais dos vértices
/// @param p Inteiro que representa o pai do vértice atual
/// @param v Inteiro que representa o vértice atual
void buscaEmProfundidade(pGrafo g, int *pai, int p, int v){
    pNo t;
    pai[v] = p;
    for(t = g->adjacencia[v]; t != NULL; t = t->prox){
        if(pai[t->v] == -1){
            buscaEmProfundidade(g, pai, v, t->v);
        }
    }
}

/// @brief Função para encontrar caminhos
/// @param g Ponteiro para o grafo
/// @param s Inteiro que representa o vértice de origem
/// @return int* Vetor de inteiros que representa os pais dos vértices
int* encontrarCaminhos(pGrafo g, int s){
    int i, *pai = (int*) malloc(g->n * sizeof(int));
    for(i = 0; i < g->n; i++){
        pai[i] = -1;
    }
    buscaEmProfundidade(g, pai, s, s);
    return pai;
}

/// @brief Função para imprimir o caminho reverso
/// @param v Inteiro que representa o vértice
/// @param pai Vetor de inteiros que representa os pais dos vértices
void imprimirCaminhoReverso(int v, int *pai){
    printf("%d\t", v);
    if(pai[v] != v){
        imprimirCaminhoReverso(pai[v], pai);
    }
}

/// @brief Função para imprimir o caminho
/// @param v Inteiro que representa o vértice
/// @param pai Vetor de inteiros que representa os pais dos vértices
void imprimirCaminho(int v, int *pai){
    if(pai[v] != v){
        imprimirCaminho(pai[v], pai);
    }
    printf("%d\t", v);
}

/// @brief Função para visitar recursivamente
/// @param g Ponteiro para o grafo
/// @param visitado Vetor de inteiros que representa os vértices visitados
/// @param v Inteiro que representa o vértice atual
/// @param t Inteiro que representa o vértice alvo
/// @return int 1 se encontrou, 0 caso contrário
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

/// @brief Função para verificar se existe um caminho entre dois vértices
/// @param g Ponteiro para o grafo
/// @param s Inteiro que representa o vértice de origem
/// @param t Inteiro que representa o vértice de destino
/// @return int 1 se encontrou, 0 caso contrário
int existeCaminho(pGrafo g, int s, int t){
    int encontrou, i, *visitado = (int*) malloc(g->n * sizeof(int));
    for(i = 0; i < g->n; i++){
        visitado[i] = 0;
    }
    encontrou = buscaRec(g, visitado, s, t);
    free(visitado);
    return encontrou;
}

/// @brief Função para criar uma pilha
/// @return pPilha Ponteiro para a pilha criada
PILHA* criarPilha(){
    PILHA* p = (PILHA*) malloc(sizeof(PILHA));
    p->topo = NULL;
    return p;
}

/// @brief Função para destruir uma pilha
/// @param pilha Ponteiro para a pilha a ser destruída
void destruirPilha(PILHA* pilha){
    free(pilha);
}

/// @brief Função para empilhar
/// @param pilha Ponteiro para a pilha
/// @param s Inteiro que representa o valor a ser empilhado
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

/// @brief Função para desempilhar
/// @param pilha Ponteiro para a pilha
/// @return int Valor desempilhado
int desempilhar(PILHA* pilha){
    if(pilha == NULL){
        return INT_MAX;
    }
    else{
        NOPILHA* aux = pilha->topo;
        pilha->topo = pilha->topo->ant;
        return aux->valor;
        free(aux);
    }
}

/// @brief Função para verificar se a pilha está vazia
/// @param pilha Ponteiro para a pilha
/// @return int 1 se a pilha está vazia, 0 caso contrário
int pilhaVazia(PILHA* pilha){
    if(pilha->topo == NULL){
        return 1;
    }
    return 0;
}

/// @brief Função para Busca em Profundidade utilizando Pilha
/// @param g Ponteiro para o grafo
/// @param s Inteiro que representa o vértice de origem
/// @return int* Vetor de inteiros que representa os pais dos vértices
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

/// @brief Função para visitar recursivamente
/// @param g Ponteiro para o grafo
/// @param componentes Vetor de inteiros que representa os componentes
/// @param comp Inteiro que representa o componente atual
/// @param v Inteiro que representa o vértice atual
void visitarRec(pGrafo g, int *componentes, int comp, int v){
    pNo t;
    componentes[v] = comp;
    for(t = g->adjacencia[v]; t != NULL; t = t->prox){
        if(componentes[t->v] == -1){
            visitarRec(g, componentes, comp, t->v);
        }
    }
}

/// @brief Função para encontrar componentes
/// @param g Ponteiro para o grafo
/// @return int* Vetor de inteiros que representa os componentes
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

/// @brief Função para criar uma fila
/// @return pFila Ponteiro para a fila criada
FILA* criarFila(){
    FILA* f = (FILA*) malloc(sizeof(FILA));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

/// @brief Função para destruir uma fila
/// @param fila Ponteiro para a fila a ser destruída
void destruirFila(FILA* fila){
    NOFILA* atual = fila->inicio;
    while (atual != NULL) {
        NOFILA* aux = atual;
        atual = atual->prox;
        free(aux);
    }
    free(fila);
}

/// @brief Função para enfileirar
/// @param fila Ponteiro para a fila
/// @param s Inteiro que representa o valor a ser enfileirado
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
        if(fila->inicio == NULL){
            fila->inicio = novoNo;
            fila->fim = novoNo;
        }
        else{
            fila->fim->prox = novoNo;
            fila->fim = novoNo;
        }
    }
}

/// @brief Função para desenfileirar
/// @param fila Ponteiro para a fila
/// @return int Valor desenfileirado
int desenfileirar(FILA* fila){
    if(fila->inicio == NULL){
        return INT_MAX;
    }
    else{
        NOFILA* aux = fila->inicio;
        int valor = aux->valor;
        fila->inicio = fila->inicio->prox;
        if(fila->inicio == NULL){
            fila->fim = NULL;
        }
        free(aux);
        return valor;
    }
}

/// @brief Função para verificar se a fila está vazia
/// @param fila Ponteiro para a fila
/// @return int 1 se a fila está vazia, 0 caso contrário
int filaVazia(FILA* fila){
    if(fila->inicio == NULL){
        return 1;
    }
    return 0;
}

/// @brief Função para Busca em Largura utilizando Fila
/// @param g Ponteiro para o grafo
/// @param s Inteiro que representa o vértice de origem
/// @return int* Vetor de inteiros que representa os pais dos vértices
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

/// @brief Função para visitar recursivamente
/// @param g Ponteiro para o grafo
/// @param visitado Vetor de inteiros que representa os vértices visitados
/// @param v Inteiro que representa o vértice atual
void visitarRec2(pGrafo g, int *visitado, int v){
    pNo t;
    visitado[v] = 1;
    for(t = g->adjacencia[v]; t != NULL; t = t->prox){
        if(!visitado[t->v]){
            visitarRec2(g, visitado, t->v);
        }
    }
    printf("%d ", v);
}

/// @brief Função para Ordenação Topológica
/// @param g Ponteiro para o grafo
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

/// @brief Função para criar uma fila de prioridade
/// @param tamanho Inteiro que representa o tamanho da fila de prioridade
/// @return pFp Ponteiro para a fila de prioridade criada
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

/// @brief Função para inserir um elemento na fila de prioridade
/// @param fprio Ponteiro para a fila de prioridade
/// @param vertice Inteiro que representa o vértice
/// @param prioridade   Inteiro que representa a prioridade
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

/// @brief Função para extrair o mínimo da fila de prioridade
/// @param fprio Ponteiro para a fila de prioridade
/// @return int Vértice mínimo
int extrairMinimo(pFp fprio){
    if(fprio->n == 0){
        return INT_MAX;
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

/// @brief Função para retornar a prioridade de um vértice
/// @param fprio Ponteiro para a fila de prioridade
/// @param vertice Inteiro que representa o vértice
/// @return int Prioridade do vértice
int prioridade(pFp fprio, int vertice){
    int pos = fprio->indice[vertice];
    if(pos == -1){
        return INT_MAX;
    }
    return fprio->v[pos].prioridade;
}

/// @brief Função para diminuir a prioridade de um vértice
/// @param fprio Ponteiro para a fila de prioridade
/// @param vertice Inteiro que representa o vértice
/// @param novaPrioridade Inteiro que representa a nova prioridade
void diminuirPrioridade(pFp fprio, int vertice, int novaPrioridade){
    int pos = fprio->indice[vertice];
    if(pos == -1){
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

/// @brief Função para verificar se a fila de prioridade está vazia
/// @param fprio Ponteiro para a fila de prioridade
/// @return int 1 se a fila de prioridade está vazia, 0 caso contrário
int vazia(pFp fprio){
    if(fprio->n == 0){
        return 1;
    }
    return 0;
}

/// @brief Função para destruir uma fila de prioridade
/// @param fprio Ponteiro para a fila de prioridade
void destruirFprio(pFp fprio) {
    free(fprio->v);
    free(fprio->indice);
    free(fprio);
}


/// @brief Função para calcular a distância de um vértice a todos os outros utilizando Dijkstra
/// @param g Ponteiro para o grafo
/// @param s Inteiro que representa o vértice de origem
/// @return int* Vetor de inteiros que representa as distâncias
int* dijkstra(pGrafo g, int s){
    int v, *pai = (int*) malloc(g->n * sizeof(int)), *distancia = (int*) malloc(g->n * sizeof(int));
    pNo t;
    pFp h = criarFprio(g->n);
    for(v = 0; v < g->n; v++){
        distancia[v] = INT_MAX;
        pai[v] = -1;
        inserirFprio(h, v, INT_MAX);
    }

    distancia[s] = 0;
    pai[s] = s;
    diminuirPrioridade(h, s, 0);

    while(!vazia(h)){
        v = extrairMinimo(h);
        if(distancia[v] != INT_MAX){
            for(t = g->adjacencia[v]; t != NULL; t = t->prox){
                if(distancia[v] + t->peso < distancia[t->v]){
                    distancia[t->v] = distancia[v] + t->peso;
                    diminuirPrioridade(h, t->v, distancia[t->v]);
                    pai[t->v] = v;
                }
            }
        }
    }

    destruirFprio(h);
    return distancia;
}

/// @brief Função para calcular a árvore geradora mínima utilizando Prim 
/// @param g Ponteiro para o grafo
/// @param s Inteiro que representa o vértice de origem
/// @return int* Vetor de inteiros que representa os pais dos vértices
int* prim(pGrafo g, int s){
    int v, *pai = (int*) malloc(g->n * sizeof(int)), *chaves = (int*) malloc(g->n * sizeof(int));
    pNo t;
    pFp h = criarFprio(g->n);
    for(v = 0; v < g->n; v++){
        chaves[v] = INT_MAX;
        pai[v] = -1;
        inserirFprio(h, v, INT_MAX);
    }
    chaves[s] = 0;
    pai[s] = s;
    diminuirPrioridade(h, s, 0);

    while(!vazia(h)){
        v = extrairMinimo(h);
        for(t = g->adjacencia[v]; t != NULL; t = t->prox){
            if(t->peso < chaves[t->v] && prioridade(h, t->v) != -1){
                chaves[t->v] = t->peso;
                pai[t->v] = v;
                diminuirPrioridade(h, t->v, t->peso);
            }
        }
    }
    free(h);
    free(chaves);
    return pai;
}
