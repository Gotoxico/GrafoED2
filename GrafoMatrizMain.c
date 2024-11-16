#include <stdio.h>
#include <stdlib.h>
#include "GrafoMatriz.h"

int main() {
    int n = 6;  // Quantidade de vertices no grafo
    pGrafo g = criarGrafo(n);

    // Adicionando arestas com pesos
    inserirAresta(g, 0, 1, 2);
    inserirAresta(g, 0, 2, 4);
    inserirAresta(g, 1, 2, 1);
    inserirAresta(g, 1, 3, 7);
    inserirAresta(g, 2, 4, 3);
    inserirAresta(g, 3, 5, 1);
    inserirAresta(g, 4, 5, 5);

    // Imprimir as arestas do grafo
    printf("Arestas do grafo:\n");
    imprimirArestas(g);

    // Testando busca em largura
    printf("\nResultado da Busca em Largura a partir do vértice 0:\n");
    int* paisBFS = buscaEmLargura(g, 0);
    imprimirCaminho(5, paisBFS);  // Imprime caminho do vértice 0 ao 5
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("Pai do vértice %d: %d\n", i, paisBFS[i]);
    }
    free(paisBFS);

    // Testando busca em profundidade
    printf("\nResultado da Busca em Profundidade a partir do vértice 0:\n");
    int* paisDFS = encontrarCaminhos(g, 0);
    imprimirCaminho(5, paisDFS);  // Imprime caminho do vértice 0 ao 5
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("Pai do vértice %d: %d\n", i, paisDFS[i]);
    }
    free(paisDFS);

    // Testando o algoritmo de Dijkstra
    int* distDijkstra = dijkstra(g, 0);
    printf("\nResultado do algoritmo de Dijkstra a partir do vértice 0:\n");
    for (int i = 0; i < n; i++) {
        printf("Distância mínima até o vértice %d: %d\n", i, distDijkstra[i]);
    }
    free(distDijkstra);

    // Testando o algoritmo de Prim
    int* paiPrim = prim(g, 0);

    for(int i = 0; i < n; i++){
        printf("%d\n", paiPrim[i]);
    }

    printf("\nResultado do algoritmo de Prim a partir do vértice 0:\n");
    for (int i = 1; i < n; i++) {
        if (paiPrim[i] != -1) {
            printf("Aresta: (%d, %d)\n", paiPrim[i], i);
        }
    }
    free(paiPrim);

    // Liberar memória
    destruirGrafo(g);

    return 0;
}



