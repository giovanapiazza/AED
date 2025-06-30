#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotyfon.h"

int main() {
    Fila *playlistFila = criarFila();
    Pilha *playlistPilha = criarPilha();
    char nomeArquivo[100];

    if (!playlistFila || !playlistPilha) {
        printf("Erro ao criar playlist.\n");
        return 1;
    }

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1- Carregar arquivo de músicas\n");
        printf("2- Criar nova playlist\n");
        printf("3- Inserir música na playlist\n");
        printf("4- Imprimir uma música\n");
        printf("5- Imprimir relatório\n");
        printf("6- Imprimir playlist (Back-up)\n");
        printf("0- Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo: ");
                if (fgets(nomeArquivo, sizeof(nomeArquivo), stdin)) {
                    nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0'; // remove \n
                }
                carregar(nomeArquivo, playlistFila);
                break;

            case 2: {
                char confirma;
                if (playlistPilha->tamanho > 0 || playlistFila->tamanho > 0) {
                    printf("Ao fazer isso você irá sobrescrever uma playlist anterior.\nTem certeza disso? (s/n): ");
                    scanf(" %c", &confirma);
                    getchar();
                    if (confirma == 's' || confirma == 'S') {
                        freeFila(playlistFila);
                        freePilha(playlistPilha);
                        playlistFila = criarFila();
                        playlistPilha = criarPilha();
                        printf("Nova playlist criada com sucesso!\n");
                    } else if (confirma == N || confirma == n) {
                        printf("Operação cancelada.\n");
                    } else {
                        printf("Opção invalida");
                } else {
                    printf("Playlist criada com sucesso!\n");
                }
                break;
            }

            case 3:
                if (!playlistPilha) {
                    printf("Crie uma playlist antes.\n");
                } else {
                    inserirMusicaNaPlaylist(playlistFila, playlistPilha, nomeArquivo);
                }
                break;

            case 4:
                if (!playlistPilha) {
                    printf("Crie uma playlist antes.\n");
                } else {
                    imprimirMusica(); // implementar
                }
                break;

            case 5:
                if (!playlistPilha) {
                    printf("Crie uma playlist antes.\n");
                } else {
                    imprimirRelatorio(playlistPilha); // implementar
                }
                break;

            case 6:
                if (!playlistPilha) {
                    printf("Crie uma playlist antes.\n");
                } else {
                    mostra(playlistPilha, playlistFila); // 
                }
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    freePilha(playlistPilha);
    freeFila(playlistFila);
    return 0;
}
