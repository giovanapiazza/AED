#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotyfon.h"

int main() {
    Lista listaMusicas;
    Fila playlistFila;
    Pilha playlistPilha;
    char nomeArquivo[256];
    int carregouArquivo = 0;
    int opcao, op;

    inicializarLista(&listaMusicas);
    criarFila(&playlistFila);
    criarPilha(&playlistPilha);

    do {
        printf("\nMenu:\n");
        printf("1- Carregar arquivo de musicas\n");
        printf("2- Criar nova playlist\n");
        printf("3- Inserir musica na playlist\n");
        printf("4- Imprimir\n");
        printf("5- Relatorio\n");
        printf("6- Backup playlist\n");
        printf("0- Sair\nEscolha: ");

        if (scanf("%d", &opcao) != 1) { while(getchar() != '\n'); continue; }
        getchar();

        switch (opcao) {
            case 1:
                importacao(&listaMusicas, &playlistFila, &playlistPilha, &carregouArquivo);
                break;

            case 2:
                if (playlistFila.inicio != NULL) {
                    criarPlaylist(&playlistFila, &playlistPilha);
                } else {
                    criarFila(&playlistFila);
                    criarPilha(&playlistPilha);
                    printf("Nova playlist criada.\n");
                }
                break;

            case 3:
                if (!carregouArquivo) {
                    printf("Carregue o arquivo antes.\n");
                    break;
                }
                buscarEInserirMusica(&listaMusicas, &playlistFila, &playlistPilha);
                break;

            case 4: 
                if (!carregouArquivo) {
                    printf("Carregue o arquivo antes.\n");
                    break;
                }
                imprimirTudo(&listaMusicas, &playlistFila, &playlistPilha);
                break;

            case 5:
                if (playlistFila.inicio == NULL) {
                    printf("Insira na playlist antes de salvar o relatorio!\n");
                    break;
                }

                char nomeRela[100];
                printf("Digite o nome do arquivo para salvar o relatorio (ex: relatorio.txt): ");
                fgets(nomeRela, sizeof(nomeRela), stdin);
                nomeRela[strcspn(nomeRela, "\n")] = 0;

                salvarRelatorio(nomeRela, &playlistFila, &listaMusicas);
                break;

            case 6:
                if (!carregouArquivo) {
                    printf("Voce deve carregar um arquivo primeiro.\n");
                    break;
                }
                if (playlistFila.inicio == NULL && playlistFila.fim == NULL && playlistFila.tamanho == 0) {
                    printf("A playlist ainda nao foi criada.\n");
                    break;
                }

                if (filaVazia(&playlistFila)) {
                    printf("A playlist esta vazia. Nada a salvar.\n");
                } else {
                    char nomeback[256];
                    printf("Digite o nome do arquivo para backup (ex: backup.txt): ");
                    fgets(nomeback, sizeof(nomeback), stdin);
                    nomeback[strcspn(nomeback, "\n")] = 0;
                    salvarBackup(&playlistFila, nomeback);
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberarLista(&listaMusicas);
    liberarFila(&playlistFila);
    liberarPilha(&playlistPilha);

    return 0;
}
