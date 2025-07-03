#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"
int main() {
    int opcao, chave_busca;
    Grafo *grafo = NULL;
    Fila *minhaFila = NULL;
    char nomeArquivo[100];

    do {
        printf("\n--------------MENU--------------\n");
        printf("1 - Carregar grafo (lista)\n");
        printf("2 - Buscar vertice\n");
        printf("3 - Imprimir grafo\n");
        printf("4 - Enfileirar arestas\n");
        printf("0 - Sair\n");
        printf("\nEscolha sua opcao:\n");
        scanf("%d", &opcao);
        setbuf(stdin, NULL);

        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo: ");
                fgets(nomeArquivo, sizeof(nomeArquivo), stdin);
                nomeArquivo[strcspn(nomeArquivo, "\n")] = 0;

                grafo = parser(nomeArquivo);
                if (grafo)
                    printf("Grafo carregado com sucesso!\n");
                break;

            case 2:
                if (!grafo) {
                    printf("Grafo nao carregado!\n");
                    break;
                }
                printf("Digite a chave do vertice: ");
                scanf("%d", &chave_busca);
                if (buscaVertice(grafo, chave_busca))
                    printf("Vertice encontrado!\n");
                else
                    printf("Vertice nao encontrado.\n");
                break;

            case 3:
                if (grafo)
                    imprimeGrafo(grafo);
                else
                    printf("Grafo nao carregado!\n");
                break;

            case 4:
                if (!grafo) {
                    printf("Grafo nao carregado!\n");
                    break;
                }

                minhaFila = criaFila();
                Nodo *atual = grafo->nodos;
                while (atual != NULL) {
                    Aresta *a = atual->adjacencias;
                    while (a != NULL) {
                        NodoFila *no = criaNodoFila(a);
                        enqueue(minhaFila, no);
                        a = a->prox;
                    }
                    atual = atual->prox;
                }
                showFila(minhaFila);
                break;

            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

