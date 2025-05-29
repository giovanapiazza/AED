#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

int main() {
    struct desc_queue *fila = CreateQueue(); // Cria a fila de músicas
    int op;

    do {
        // Menu principal
        printf("\n--- MENU ---\n");
        printf("1 - ENQUEUE (inserir música)\n");
        printf("2 - DEQUEUE (remover da frente)\n");
        printf("3 - EMPTY (verificar se fila está vazia)\n");
        printf("4 - LENGTH (quantidade de músicas)\n");
        printf("5 - ShowQueue (exibir músicas)\n");
        printf("6 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar(); // Limpa o buffer

        switch (op) {
            case 1: {
                struct musica *m = criarMusica();
                ENQUEUE(fila, m);
                printf("Música adicionada à fila!\n");
                break;
            }
            case 2: {
                struct musica *removida = DEQUEUE(fila);
                if (removida) {
                    printf("Removida: %s\n", removida->titulo);
                    free(removida); // Libera a memória da música
                } else {
                    printf("Fila vazia.\n");
                }
                break;
            }
            case 3:
                if (EMPTY(fila))
                    printf("A fila está vazia.\n");
                else
                    printf("A fila tem elementos.\n");
                break;
            case 4:
                printf("Tamanho da fila: %d\n", LENGTH(fila));
                break;
            case 5:
                ShowQueue(fila);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (op != 6);

    DELETE(fila); // Libera toda a memória da fila
    return 0;
}

