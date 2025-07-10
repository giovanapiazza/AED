#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spot.h"

nt main() {
    Lista listaMusicas;
    Fila playlistFila;
    Pilha playlistPilha;
    char nomeArquivo[256] = "";
    int carregouArquivo = 0;
    int opcao;

    inicializarLista(&listaMusicas);
    criarFila(&playlistFila);
    criarPilha(&playlistPilha);

    do {
        printf("\nMenu:\n");
        printf("1- Carregar arquivo de musicas\n");
        printf("2- Criar nova playlist\n");
        printf("3- Inserir musica na playlist\n");
        printf("4- Imprimir\n");
        printf("5- Backup\n");
        printf("6- Relatorio\n");
        printf("7- Executar\n");
        printf("0- Sair\nEscolha: ");

        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n');
            continue;
        }
        getchar();

        switch (opcao) {
            case 1:
                importacao(&listaMusicas, &playlistFila, &playlistPilha, &carregouArquivo, nomeArquivo);
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

            case 5: {
                if (playlistFila.inicio == NULL) {
                    printf("Insira na playlist antes de salvar um backup!\n");
                    break;
                }
                backup(nomeArquivo, &listaMusicas, &playlistFila, carregouArquivo);
                break;
            }

            case 6:{
                if (playlistFila.inicio == NULL) {
                    printf("Insira na playlist antes de salvar o relatorio!\n");
                    break;
                }
                char nomeRelatorio[100];
                printf("Digite o nome do arquivo para salvar o relatorio (ex: relatorio.txt): ");
                fgets(nomeRelatorio, sizeof(nomeRelatorio), stdin);
                nomeRelatorio[strcspn(nomeRelatorio, "\n")] = 0;

                salvarRelatorio(nomeRelatorio, &playlistFila, &listaMusicas, nomeArquivo);
                break;
            }

            case 7:
                if (filaVazia(&playlistFila)) {
                    printf("Playlist vazia. Insira musicas antes de executar.\n");
                } else {
                    executarPlaylist(&playlistFila, &playlistPilha);
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
