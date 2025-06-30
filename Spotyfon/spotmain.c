#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotyfon.h"

int main() {
    Fila *playlistFila = criarFila();
    Pilha *playlistPilha = criarPilha();
    char nomeArquivo[100] = "musicas.txt";

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
        printf("4- Remover musica na playlist\n");
        printf("5- Imprimir uma música\n");
        printf("6- Imprimir playlist (Back-up)\n");
        printf("0- Sair\n");
        printf("Escolha: ");

        switch(opcao) {
            case 1:
                printf("Digite o nome do arquivo: ");
                if (fgets(nomeArquivo, sizeof(nomeArquivo), stdin)) {
                    nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';
                }
                carregar(nomeArquivo);
                break;

            case 2:
                break;

            case 3:
                if (pilha == Null){
                    printf("Crie uma playlist antes\n");
                }else{

                }
                break;

            case 4:
                if (pilha == Null){
                    printf("Crie uma playlist antes\n");
                }else{
                    
                }
                break;

            case 5: 
                if (pilha == Null){
                    printf("Crie uma playlist antes\n");
                }else{
                    
                }
                break;

            case 6:
                if (pilha == Null){
                    printf("Crie uma playlist antes\n");
                }else{
                    
                }
                break;
            
            case 0: 
                printf("Encerando...")
                break;
            
            case 0:
                free(pilha);
                free(fila);
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);
    free(pilha);
    free(fila);
    return 0;
}
