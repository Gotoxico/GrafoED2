#include <stdio.h>
#include <stdlib.h>
#include "GrafoLista.h"

int main() {
    int n = 6; // Número de vértices
    pGrafo g = criarGrafo(n);

    printf("\n=====================================================================\n");
    printf("|TESTE 1 DE GRAFO COM LISTA DE ADJACENCIA - GRAFOS NAO DIRECIONADOS|\n");
    printf("=====================================================================\n\n");

    printf("Grafo com %d vértices criado.\n\n", n);

    system("pause");
    system("cls");

    printf("\n==================================\n" );
    printf("|INSERCAO DE ARESTAS NO GRAFO     |\n");
    printf("===================================\n\n");

    // Adicionando arestas com pesos
    printf("Inserindo aresta (0, 1) com peso 2\n");
    inserirAresta(g, 0, 1, 2);
    printf("Inserindo aresta (0, 2) com peso 4\n");
    inserirAresta(g, 0, 2, 4);
    printf("Inserindo aresta (1, 2) com peso 1\n");
    inserirAresta(g, 1, 2, 1);
    printf("Inserindo aresta (1, 3) com peso 7\n");
    inserirAresta(g, 1, 3, 7);
    printf("Inserindo aresta (2, 4) com peso 3\n");
    inserirAresta(g, 2, 4, 3);
    printf("Inserindo aresta (3, 5) com peso 1\n");
    inserirAresta(g, 3, 5, 1);
    printf("Inserindo aresta (4, 5) com peso 5\n");
    inserirAresta(g, 4, 5, 5);

    // Imprimir as arestas do grafo
    printf("Arestas do grafo:\n");
    imprimirArestas(g);

    system("pause");
    system("cls");

    //Busca em Largura
    printf("\n==================================\n" );
    printf("|BUSCA EM LARGURA                 |\n");
    printf("===================================\n\n");
    
    // Testando busca em largura
    printf("\nResultado da Busca em Largura a partir do vértice 0:\n");
    int* paiBFS = buscaEmLargura(g, 0);
    
    printf("Caminho do vértice 0 ao 5: ");
    imprimirCaminho(5, paiBFS);  // Imprime caminho do vértice 0 ao 5
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("Pai do vértice %d: %d\n", i, paiBFS[i]);
    }
    free(paiBFS);

    system("pause");
    system("cls");

    
    //Busca em Profundidade
    printf("\n==================================\n" );
    printf("|BUSCA EM PROFUNDIDADE            |\n");
    printf("===================================\n\n");
    
    // Testando busca em profundidade
    printf("\nResultado da Busca em Profundidade a partir do vértice 0:\n");
    int* paiDFS = encontrarCaminhos(g, 0);

    printf("Caminho do vértice 0 ao 5: ");
    imprimirCaminho(5, paiDFS);  // Imprime caminho do vértice 0 ao 5
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("Pai do vértice %d: %d\n", i, paiDFS[i]);
    }
    free(paiDFS);

    system("pause");
    system("cls");

     //Dijkstra
    printf("\n==================================\n" );
    printf("|ALGORITMO DE DIJKSTRA            |\n");
    printf("===================================\n\n");

    // Testando o algoritmo de Dijkstra
    int* distDijkstra = dijkstra(g, 0);
    printf("\nResultado do algoritmo de Dijkstra a partir do vértice 0:\n");
    for (int i = 0; i < n; i++) {
        printf("Distância mínima até o vértice %d: %d\n", i, distDijkstra[i]);
    }
    free(distDijkstra);

    system("pause");
    system("cls");

    //Prim
    printf("\n==================================\n" );
    printf("|ALGORITMO DE PRIM                |\n");
    printf("===================================\n\n");
    
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

    // Liberando a memória
    destruirGrafo(g);

    system("pause");
    system("cls");


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

     printf("\n=====================================================================\n");
    printf("|TESTE 2 DE GRAFO COM MATRIZ DE ADJACENCIA - GRAFOS DIRECIONADOS    |\n");
    printf("=====================================================================\n\n");

    // Criar grafo direcionado
    pGrafo g2 = criarGrafo(n);

    printf("Grafo com %d vértices criado.\n\n", n);

    system("pause");
    system("cls");

    printf("\n==================================\n" );
    printf("|INSERCAO DE ARESTAS NO GRAFO     |\n");
    printf("===================================\n\n");

    printf("Inserindo arestas no grafo...\n\n");
    // Adicionando arestas com peso 2 - todas
    printf("Inserindo aresta (0, 1) com peso 2\n");
    inserirAresta(g2, 0, 1, 2);
    printf("Inserindo aresta (0, 2) com peso 2\n");
    inserirAresta(g2, 0, 2, 2);
    printf("Inserindo aresta (1, 3) com peso 2\n");
    inserirAresta(g2, 1, 3, 2);
    printf("Inserindo aresta (2, 4) com peso 2\n");
    inserirAresta(g2, 2, 4, 2);
    printf("Inserindo aresta (3, 4) com peso 2\n");
    inserirAresta(g2, 3, 4, 2);
    printf("Inserindo aresta (4, 5) com peso 2\n");
    inserirAresta(g2, 4, 5, 2);
    printf("Inserindo aresta (2, 5) com peso 2\n");
    inserirAresta(g2, 2, 5, 2);

    // Imprimir as arestas do grafo
    printf("\nArestas do grafo:\n");
    imprimirArestas(g2);

    system("pause");
    system("cls");

    //Busca em Largura

    printf("\n==================================\n" );
    printf("|BUSCA EM LARGURA                 |\n");
    printf("===================================\n\n");

    // Testando busca em largura

    printf("\nResultado da Busca em Largura a partir do vértice 0:\n");
    int* paisBFS2 = buscaEmLargura(g2, 0);

    printf("Caminho do vértice 0 ao 5: ");
    imprimirCaminho(5, paisBFS2);  // Imprime caminho do vértice 0 ao 5

    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("Pai do vértice %d: %d\n", i, paisBFS2[i]);
    }

    free(paisBFS2);

    system("pause");
    system("cls");

    //Busca em Profundidade

    printf("\n==================================\n" );
    printf("|BUSCA EM PROFUNDIDADE            |\n");
    printf("===================================\n\n");

    // Testando busca em profundidade

    printf("\nResultado da Busca em Profundidade a partir do vértice 0:\n");
    int* paisDFS2 = encontrarCaminhos(g2, 0);

    printf("Caminho do vértice 0 ao 5: ");
    imprimirCaminho(5, paisDFS2);  // Imprime caminho do vértice 0 ao 5

    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("Pai do vértice %d: %d\n", i, paisDFS2[i]);
    }

    free(paisDFS2);

    system("pause");
    system("cls");

    //Dijkstra

    printf("\n==================================\n" );
    printf("|ALGORITMO DE DIJKSTRA            |\n");
    printf("===================================\n\n");

    // Testando o algoritmo de Dijkstra

    int* distDijkstra2 = dijkstra(g2, 0);

    printf("\nResultado do algoritmo de Dijkstra a partir do vértice 0:\n");

    for (int i = 0; i < n; i++) {
        printf("Distância mínima até o vértice %d: %d\n", i, distDijkstra2[i]);
    }

    free(distDijkstra2);

    system("pause");
    system("cls");

    //Prim

    printf("\n==================================\n" );
    printf("|ALGORITMO DE PRIM                |\n");
    printf("===================================\n\n");

    // Testando o algoritmo de Prim

    int* paiPrim2 = prim(g2, 0);

    for(int i = 0; i < n; i++){
        printf("%d\n", paiPrim2[i]);
    }

    printf("\nResultado do algoritmo de Prim a partir do vértice 0:\n");

    for (int i = 1; i < n; i++) {
        if (paiPrim2[i] != -1) {
            printf("Aresta: (%d, %d)\n", paiPrim2[i], i);
        }
    }

    free(paiPrim2);

    system("pause");
    system("cls");

    //Fim e liberar memória

    printf("\n==================================\n" );
    printf("|FIM DO TESTE 2                   |\n");
    printf("===================================\n\n");

    // Liberar memória
    destruirGrafo(g2);


    return 0;
}
