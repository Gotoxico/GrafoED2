#include <stdio.h>
#include <stdlib.h>
#include "GrafoMatriz.h" // Inclui o novo cabeçalho GrafoMatriz

int main() {
    int n = 5; // Exemplo com 5 vértices
    pGrafo g = criarGrafo(n);

    // Adiciona arestas ao grafo (Exemplo de Grafo)
    inserirAresta(g, 0, 1, 10);
    inserirAresta(g, 0, 2, 5);
    inserirAresta(g, 1, 2, 2);
    inserirAresta(g, 1, 3, 1);
    inserirAresta(g, 2, 3, 9);
    inserirAresta(g, 2, 4, 2);
    inserirAresta(g, 3, 4, 4);

    printf("Arestas do Grafo:\n");
    imprimirArestas(g);

    // Busca em Largura a partir do vértice 0
    printf("\nBusca em Largura a partir do vértice 0:\n");
    int* bfs_result = buscaEmLargura(g, 0);
    for (int i = 0; i < n; i++) {
        printf("Vértice %d -> Pai %d\n", i, bfs_result[i]);
    }
    free(bfs_result);

    // Busca em Profundidade a partir do vértice 0
    printf("\nBusca em Profundidade a partir do vértice 0:\n");
    int* dfs_result = encontrarCaminhos(g, 0);
    for (int i = 0; i < n; i++) {
        printf("Vértice %d -> Pai %d\n", i, dfs_result[i]);
    }
    free(dfs_result);

    // Algoritmo de Dijkstra a partir do vértice 0
    printf("\nMenores caminhos a partir do vértice 0 (Dijkstra):\n");
    int* dijkstra_result = dijkstra(g, 0);
    for (int i = 0; i < n; i++) {
        printf("Menor caminho até o vértice %d = %d\n", i, dijkstra_result[i]);
    }
    free(dijkstra_result);

    // Algoritmo de Prim para a Árvore Geradora Mínima a partir do vértice 0
    printf("\nÁrvore Geradora Mínima usando o algoritmo de Prim a partir do vértice 0:\n");
    int* prim_result = prim(g, 0);
    for (int i = 1; i < n; i++) { // Começa de 1, pois 0 é a raiz
        printf("Aresta %d - %d\n", prim_result[i], i);
    }
    free(prim_result);

    // Liberação de memória
    destruirGrafo(g);

    return 0;
}

