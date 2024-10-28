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
//Busca em Profundidade
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
//Buscar pra ver se existe caminho entre um ponto e outro
int buscaRec(pGrafo g, int *visitado, int v, int t);
int existeCaminho(pGrafo g, int s, int t);
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


#include "GrafoLista.c"
#endif