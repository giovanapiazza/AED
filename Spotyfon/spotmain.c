#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotyfon.h"

int main() {
    Fila *playlistFila = criarFila();
    Pilha *playlistPilha = criarPilha();
    char nomeArquivo[100] = "musicas.txt"; // valor padrão

    if (!playlistFila || !playlistPilha) {
        printf("Erro ao criar playlist.\n");
        return 1;
    }

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1- Carregar arquivo de músicas\n");
        printf("2- Criar nova playlist\n");
        printf("3- Inserir música da biblioteca na playlist\n");
        printf("4- Remover última música adicionada\n");
        printf("5- Buscar por uma música\n");
        printf("6- Imprimir uma música pelo código\n");
        printf("7- Imprimir playlist\n");
        printf("8- Ver última música adicionada\n");
        printf("0- Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                printf("Digite o nome do arquivo (ex: musicas.txt): ");
                fgets(nomeArquivo, sizeof(nomeArquivo), stdin);
                nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';
                carregar(nomeArquivo);
                break;

            case 2:
                destruirFila(playlistFila);
                destruirPilha(playlistPilha);
                playlistFila = criarFila();
                playlistPilha = criarPilha();
                printf("Playlist criada.\n");
                break;

            case 3:
                inserir(playlistFila, playlistPilha, nomeArquivo);
                break;

            case 4: {
                Musica *removida = removerTopoPilha(playlistPilha);
                if (removida) {
                    free(removida);
                    printf("Última música removida da playlist (pilha).\n");
                } else {
                    printf("Playlist vazia.\n");
                }
                break;
            }

            case 5:
                buscar(playlistFila, playlistPilha);
                break;

            case 6: {
                int codigo;
                printf("Digite o código da música: ");
                scanf("%d", &codigo);
                getchar();
                Musica *m = buscarPorCodigo(playlistFila, codigo);
                imprimirMusica(m);
                break;
            }

            case 7:
                mostrarFila(playlistFila);
                break;

            case 8:
                imprimirMusica(topoPilha(playlistPilha));
                break;

            case 0:
                destruirFila(playlistFila);
                destruirPilha(playlistPilha);
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
