#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotyfon.h"

int main() {
    struct desc_fila *minhaFila = Createfila();
    struct desc_pilha *minhaPilha = criaDescPilha();
    char nomeArquivo[100];
    char confirma;
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
                    nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0'; 
                }
                carregar(nomeArquivo, minhaFila);
                break;

            case 2:                 
                // Verifica se já existe conteúdo na playlist
                if (minhaPilha->tamanho > 0 || minhaFila->tamanho > 0) {
                    printf("Ao fazer isso você irá sobrescrever uma playlist anterior.\nTem certeza disso? (s/n): ");
                    scanf(" %c", &confirma);
                    getchar(); 
                
                    if (confirma == 's' || confirma == 'S') {
                        // Libera memória da playlist anterior
                        freeFila(minhaFila);
                        freePilha(minhaPilha);
                
                        // Cria nova fila e pilha
                        minhaFila = Createfila();
                       minhaPilha = criaDescPilha();
                        printf("Nova playlist criada com sucesso!\n");
                    } else if (confirma == 'n' || confirma == 'N') {
                        printf("Operação cancelada.\n");
                    } else {
                        printf("Opção inválida.\n");
                    }
                } else {
                    // Se a playlist ainda não existe, apenas cria
                    minhaFila = Createfila();
                   minhaPilha = criaDescPilha();
                    printf("Playlist criada com sucesso!\n");
                }

                break;

            case 3:
                if (minhaPilha->tamanho == 0 && minhaFila->tamanho == 0) {
                    printf("Crie uma playlist antes.\n");
                } else {
                    buscarEInserirMusica("musicas.txt", minhaFila, minhaPilha);
                }
                break;

            case 4:
                Musica resultado;
                buscarMusica("musicas.txt", &resultado, minhaFila, minhaPilha);
                break;

            case 5:
                if (minhaPilha->tamanho == 0 && minhaFila->tamanho == 0) {
                    printf("Crie uma playlist antes.\n");
                } else {
                     salvarPlaylistCompleta(minhaFila, minhaPilha, "playlist_fila.txt", "playlist_pilha.txt");
                }
                break;

            case 6:
                if (minhaPilha->tamanho == 0 && minhaFila->tamanho == 0) {
                    printf("Crie uma playlist antes.\n");
                } else {
                    exportarPlaylistCompleta(minhaFila, minhaPilha);
 
                }
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    freePilha(minhaPilha);
    freeFila(minhaFila);
    return 0;
}
