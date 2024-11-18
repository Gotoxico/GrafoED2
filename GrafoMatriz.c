#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "GrafoMatriz.h"

/// @brief Fun��o para criar um grafo
/// @param n Inteiro que representa o tamanho do grafo
/// @return pGrafo Ponteiro para o grafo criado
pGrafo criarGrafo(int n){
    int i, j;
    pGrafo g = (pGrafo) malloc(sizeof(GRAFO));
    g->n = n;
    g->adjacencia = (pNoGrafo**) malloc(n * sizeof(pNoGrafo*));
    for(i = 0; i < n; i++){
        g->adjacencia[i] = (pNoGrafo*) malloc(n * sizeof(pNoGrafo));
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            g->adjacencia[i][j] = (pNoGrafo) malloc(sizeof(NOGRAFO));
            g->adjacencia[i][j]->v = 0;
            g->adjacencia[i][j]->peso = 0;
        }
    }
    return g;
}

/// @brief Fun��o para destruir um grafo
/// @param g Ponteiro para o grafo a ser destru�do
void destruirGrafo(pGrafo g){
    int i, j;
    for(i = 0; i < g->n; i++){
        for(j = 0; j < g->n; j++){
            free(g->adjacencia[i][j]);
        }
        free(g->adjacencia[i]);
    }
    free(g->adjacencia);
    free(g);
}

/// @brief Fun��o para inserir uma aresta no grafo
/// @param g Ponteiro para o grafo
/// @param u Inteiro que representa o primeiro v�rtice
/// @param v Inteiro que representa o segundo v�rtice
/// @param p Inteiro que representa o peso da aresta
void inserirAresta(pGrafo g, int u, int v, int p){
    g->adjacencia[u][v]->v = 1;
    g->adjacencia[v][u]->v = 1;
    g->adjacencia[u][v]->peso = p;
    g->adjacencia[v][u]->peso = p;
}

/// @brief Fun��o para remover uma aresta do grafo
/// @param g Ponteiro para o grafo
/// @param u Inteiro que representa o primeiro v�rtice
/// @param v Inteiro que representa o segundo v�rtice
void removerAresta(pGrafo g, int u, int v){
    g->adjacencia[u][v]->v = 0;
    g->adjacencia[v][u]->v = 0;
    g->adjacencia[u][v]->peso = 0;
    g->adjacencia[v][u]->peso = 0;
}


/// @brief Fun��o para verificar se uma aresta existe no grafo
/// @param g Ponteiro para o grafo
/// @param u Inteiro que representa o primeiro v�rtice
/// @param v Inteiro que representa o segundo v�rtice
/// @return int 1 se a aresta existe, 0 caso contr�rio
int verificarAresta(pGrafo g, int u, int v){
    return g->adjacencia[u][v]->v;
}

/// @brief Fun��o para ler um grafo
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

/// @brief Fun��o para imprimir as arestas do grafo
/// @param g Ponteiro para o grafo
void imprimirArestas(pGrafo g){
    int u, v;
    for(u = 0; u < g->n; u++){
        for(v = u + 1; v < g->n; v++){
            if(g->adjacencia[u][v]->v){
                printf("{%d,%d} %d ", u, v, g->adjacencia[u][v]->peso);
            }
        }
    }
}

/// @brief Fun��o para calcular o grau de um v�rtice
/// @param g Ponteiro para o grafo
/// @param u Inteiro que representa o v�rtice
/// @return int Grau do v�rtice
int grau(pGrafo g, int u){
    int v, grau = 0;
    for(v = 0; v < g->n; v++){
        if(g->adjacencia[u][v]->v){
            grau++;
        }
    }
    return grau;
}

/// @brief Fun��o para calcular o v�rtice mais popular
/// @param g Ponteiro para o grafo
/// @return int V�rtice mais popular
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

/// @brief Fun��o para imprimir as recomenda��es de um v�rtice
/// @param g Ponteiro para o grafo
/// @param u Inteiro que representa o v�rtice
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

/// @brief Fun��o para verificar recursivamente se existe um caminho entre dois v�rtices
/// @param g Ponteiro para o grafo
/// @param visitado Vetor de inteiros que representa os v�rtices visitados
/// @param v Inteiro que representa o v�rtice atual
/// @param t Inteiro que representa o v�rtice alvo
/// @return int 1 se existe caminho, 0 caso contr�rio
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

/// @brief Fun��o para verificar se existe um caminho entre dois v�rtices
/// @param g Ponteiro para o grafo
/// @param s Inteiro que representa o v�rtice de origem
/// @param t Inteiro que representa o v�rtice de destino
/// @return int 1 se existe caminho, 0 caso contr�rio
int existeCaminho(pGrafo g, int s, int t){
    int encontrou, i, *visitado = (int*) malloc(g->n * sizeof(int));
    for(i = 0; i < g->n; i++){
        visitado[i] = 0;
    }
    encontrou = buscaRec(g, visitado, s, t);
    free(visitado);
    return encontrou;
}

/// @brief Fun��o para buscar em profundidade
/// @param g Ponteiro para o grafo
/// @param pai Vetor de inteiros que representa os pais dos v�rtices
/// @param p  Inteiro que representa o pai do v�rtice atual
/// @param v Inteiro que representa o v�rtice atual
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

/// @brief Fun��o para encontrar caminhos
/// @param g Ponteiro para o grafo
/// @param s Inteiro que representa o v�rtice de origem
/// @return int* Vetor de inteiros que representa os pais dos v�rtices
int* encontrarCaminhos(pGrafo g, int s){
    int i, *pai = (int*) malloc(g->n * sizeof(int));
    for(i = 0; i < g->n; i++){
        pai[i] = -1;
    }
    buscaEmProfundidade(g, pai, s, s);
    return pai;
}

/// @brief Fun��o para criar uma pilha
/// @return pPilha Ponteiro para a pilha criada
PILHA* criarPilha(){
    PILHA* p = (PILHA*) malloc(sizeof(PILHA));
    p->topo = NULL;
    return p;
}

/// @brief Fun��o para destruir uma pilha
/// @param pilha Ponteiro para a pilha a ser destru�da
void destruirPilha(PILHA* pilha){
    free(pilha);
}

/// @brief Fun��o para empilhar
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

/// @brief Fun��o para desempilhar
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

/// @brief Fun��o para verificar se a pilha est� vazia
/// @param pilha Ponteiro para a pilha
/// @return int 1 se a pilha est� vazia, 0 caso contr�rio
int pilhaVazia(PILHA* pilha){
    if(pilha->topo == NULL){
        return 1;
    }
    return 0;
}

/// @brief Fun��o para buscar em profundidade utilizando pilha
/// @param g Ponteiro para o grafo
/// @param s Inteiro que representa o v�rtice de origem
/// @return int* Vetor de inteiros que representa os pais dos v�rtices
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

/// @brief Fun��o para imprimir o caminho reverso
/// @param v Inteiro que representa o v�rtice
/// @param pai Vetor de inteiros que representa os pais dos v�rtices
void imprimirCaminhoReverso(int v, int *pai){
    printf("%d\t", v);
    if(pai[v] != v){
        imprimirCaminhoReverso(pai[v], pai);
    }
}

/// @brief Fun��o para imprimir o caminho
/// @param v Inteiro que representa o v�rtice
/// @param pai Vetor de inteiros que representa os pais dos v�rtices
void imprimirCaminho(int v, int *pai){
    if(pai[v] != v){
        imprimirCaminho(pai[v], pai);
    }
    printf("%d\t", v);
}

/// @brief Fun��o para visitar recursivamente
/// @param g Ponteiro para o grafo
/// @param componentes Vetor de inteiros que representa os componentes
/// @param comp Inteiro que representa o componente atual
/// @param v Inteiro que representa o v�rtice atual
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

/// @brief Fun��o para encontrar componentes
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

/// @brief Fun��o para criar uma fila
/// @return pFila Ponteiro para a fila criada
FILA* criarFila(){
    FILA* f = (FILA*) malloc(sizeof(FILA));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

/// @brief Fun��o para destruir uma fila
/// @param fila Ponteiro para a fila a ser destru�da
void destruirFila(FILA* fila){
    NOFILA* atual = fila->inicio;
    while (atual != NULL) {
        NOFILA* aux = atual;
        atual = atual->prox;
        free(aux);
    }
    free(fila);
}

/// @brief Fun��o para enfileirar
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

/// @brief Fun��o para desenfileirar
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

/// @brief Fun��o para verificar se a fila est� vazia
/// @param fila Ponteiro para a fila
/// @return int 1 se a fila est� vazia, 0 caso contr�rio
int filaVazia(FILA* fila){
    if(fila->inicio == NULL){
        return 1;
    }
    return 0;
}

/// @brief Fun��o para buscar em largura
/// @param g Ponteiro para o grafo
/// @param s Inteiro que representa o v�rtice de origem
/// @return int* Vetor de inteiros que representa os pais dos v�rtices
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

/// @brief Fun��o para visitar recursivamente
/// @param g Ponteiro para o grafo
/// @param visitado Vetor de inteiros que representa os v�rtices visitados
/// @param v Inteiro que representa o v�rtice atual
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

/// @brief Fun��o para ordena��o topol�gica
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

/// @brief Fun��o para criar uma fila de prioridade
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

/// @brief Fun��o para inserir um elemento na fila de prioridade
/// @param fprio Ponteiro para a fila de prioridade
/// @param vertice Inteiro que representa o v�rtice
/// @param prioridade Inteiro que representa a prioridade
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

/// @brief Fun��o para extrair o m�nimo da fila de prioridade
/// @param fprio Ponteiro para a fila de prioridade
/// @return int V�rtice m�nimo
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

/// @brief Fun��o para retornar a prioridade de um v�rtice
/// @param fprio Ponteiro para a fila de prioridade
/// @param vertice Inteiro que representa o v�rtice
/// @return int Prioridade do v�rtice
int prioridade(pFp fprio, int vertice){
    int pos = fprio->indice[vertice];
    if(pos == -1){
        return INT_MAX;
    }
    return fprio->v[pos].prioridade;
}

/// @brief Fun��o para diminuir a prioridade de um v�rtice
/// @param fprio Ponteiro para a fila de prioridade
/// @param vertice Inteiro que representa o v�rtice
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

/// @brief Fun��o para verificar se a fila de prioridade est� vazia
/// @param fprio Ponteiro para a fila de prioridade
/// @return int 1 se a fila de prioridade est� vazia, 0 caso contr�rio
int vazia(pFp fprio){
    if(fprio->n == 0){
        return 1;
    }
    return 0;
}

/// @brief Fun��o para destruir a fila de prioridade
/// @param fprio Ponteiro para a fila de prioridade
void destruirFprio(pFp fprio) {
    free(fprio->v);
    free(fprio->indice);
    free(fprio);
}

/// @brief Fun��o para calcular o menor caminho entre dois v�rtices
/// @param g Ponteiro para o grafo
/// @param s Inteiro que representa o v�rtice de origem
/// @return int* Vetor de inteiros que representa as dist�ncias
int* dijkstra(pGrafo g, int s){
    int v, u, *pai = (int*) malloc(g->n * sizeof(int)), *distancia = (int*) malloc(g->n * sizeof(int));
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
            for(u = 0; u < g->n; u++){
                if(g->adjacencia[v][u]->v){
                    pNoGrafo t = g->adjacencia[v][u];
                    if(distancia[v] + t->peso < distancia[u]){
                        distancia[u] = distancia[v] + t->peso;
                        diminuirPrioridade(h, u, distancia[u]);
                        pai[u] = v;
                    }
                }
                
            }
        }
    }
    destruirFprio(h);
    return distancia;
}

/// @brief Fun��o para calcular o menor caminho entre dois v�rtices
/// @param g Ponteiro para o grafo
/// @param s Inteiro que representa o v�rtice de origem
/// @return int* Vetor de inteiros que representa os pais dos v�rtices
int* prim(pGrafo g, int s){
    int v, u, *pai = (int*) malloc(g->n * sizeof(int)), *chaves = (int*) malloc(g->n * sizeof(int));
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
        for(u = 0; u < g->n; u++){
            if(g->adjacencia[v][u]->v){
                pNoGrafo t = g->adjacencia[v][u];
                if(t->peso < chaves[u] && prioridade(h, u) != -1){
                    chaves[u] = t->peso;
                    pai[u] = v;
                    diminuirPrioridade(h, u, t->peso);
                }
            }
        }
    }
    free(h);
    return pai;
}