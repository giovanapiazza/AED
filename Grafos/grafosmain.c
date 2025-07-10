#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"

int main() {
    int opcao, chave_busca;
    Grafo *grafo = NULL;
    Pilha *minhaPilha = NULL;
    char nomeArquivo[100];

    do {
        printf("\n--------------MENU--------------\n");
        printf("1 - Carregar grafo (lista)\n");
        printf("2 - Buscar vertice\n");
        printf("3 - Imprimir grafo\n");
        printf("4 - Empilhar arestas de um vertice\n");
        printf("0 - Sair\n");
        printf("\nEscolha sua opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer do scanf

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
                Nodo *encontrado = buscaVertice(grafo, chave_busca);
                if (encontrado) {
                    printf("Vertice encontrado: %d\n", encontrado->chave);
                    if (encontrado->adjacencias == NULL) {
                        printf("Nao ha arestas partindo desse vertice.\n");
                    } else {
                        printf("Arestas partindo do vertice %d:\n", encontrado->chave);
                        Aresta *a = encontrado->adjacencias;
                        while (a != NULL) {
                            printf("- %d -> %d (peso %d)\n", a->partida, a->chegada, a->peso);
                            a = a->prox;
                        }
                    }
                } else {
                    printf("Vertice nao encontrado.\n");
                }
                break;

            case 3:
                if (grafo)
                    imprimeGrafoDe(grafo->nodos);
                else
                    printf("Grafo nao carregado!\n");
                break;
                
            case 4:
                if (!grafo) {
                    printf("Grafo nao carregado!\n");
                    break;
                }

                printf("Digite a chave do vertice de inicio: ");
                int inicio;
                scanf("%d", &inicio);

                int *visitado = calloc(grafo->max_vertices + 1, sizeof(int));
                Pilha *pilha = criaPilha();

                Nodo *verticeInicio = buscaVertice(grafo, inicio);
                if (verticeInicio == NULL) {
                    printf("Vertice nao encontrado!\n");
                    break;
                }

                printf("Iniciando busca em profundidade a partir do vertice %d:\n", inicio);
                push(pilha, criaNodoPilha((Aresta *)verticeInicio)); // convertendo para usar a mesma estrutura

                while (pilha->topo != NULL) {
                    NodoPilha *nodoP = pop(pilha);
                    Nodo *atual = (Nodo *)nodoP->arestaPilha;

                    if (!visitado[atual->chave]) {
                        visitado[atual->chave] = 1;
                        printf("Visitando vertice: %d\n", atual->chave);

                        Aresta *a = atual->adjacencias;
                        while (a != NULL) {
                            Nodo *vizinho = buscaVertice(grafo, a->chegada);
                            if (!visitado[vizinho->chave]) {
                                printf("  Indo para %d (peso %d)\n", vizinho->chave, a->peso);
                                push(pilha, criaNodoPilha((Aresta *)vizinho));
                            }
                            a = a->prox;
                        }
                    }

                    free(nodoP);
                }

                free(pilha);
                free(visitado);
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
