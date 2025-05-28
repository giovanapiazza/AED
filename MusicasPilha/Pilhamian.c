#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilha.h"


int main() {
    int op;
    struct desc_pilha *pilha = NULL;
    struct desc_pilha *biblioteca = NULL;


    do {
        printf("\n---------- Menu ----------\n");
        printf("0 - Adicionar arquivo\n");
        printf("1 - Criar playlist de músicas\n");
        printf("2 - Inserir nova música\n");
        printf("3 - Remover o topo\n");
        printf("4 - Ver o topo\n");
        printf("5 - Verificar se existe uma lista\n");
        printf("6 - Imprimir a pilha\n");
        printf("7 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        getchar(); 

        switch (op) {
            case 0:
                char nomeArquivo[100];
                printf("Nome do arquivo de músicas: ");
                fgets(nomeArquivo, sizeof(nomeArquivo), stdin);
                nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';

                FILE *fp = fopen(nomeArquivo, "r");
                if (!fp) {
                    printf("Erro ao abrir o arquivo.\n");
                    break;
                }

                if (biblioteca != NULL) {
                    // limpa biblioteca anterior
                    while (biblioteca->topo != NULL) {
                        struct nodo_pilha *rem = remover(biblioteca);
                        free(rem->info);
                        free(rem);
                    }
                    free(biblioteca);
                }

                biblioteca = criaDescPilha();
                char linha[1024];
                while (fgets(linha, sizeof(linha), fp)) {
                    struct musica *m = malloc(sizeof(struct musica));
                    sscanf(linha, "%[^;];%[^;];%[^;];%d;%d", m->titulo, m->artista, m->letra, &m->codigo, &m->execucoes);
                    struct nodo_pilha *n = criaNodoPilha(m);
                    inserir(biblioteca, n);
                }
                fclose(fp);
                printf("Arquivo carregado e biblioteca atualizada!\n");
                break;
            case 1:
                if (biblioteca == NULL || biblioteca->topo == NULL) {
                    printf("Biblioteca vazia! Adicione um arquivo primeiro.\n");
                    break;
                }

                if (pilha != NULL) {
                    printf("A playlist já existe. Deseja sobrescrevê-la? (s/n): ");
                    char resp;
                    scanf(" %c", &resp);
                    getchar();
                    if (resp != 's' && resp != 'S') {
                        break;
                    }
                    // limpar a pilha anterior
                    while (pilha->topo != NULL) {
                        struct nodo_pilha *rem = remover(pilha);
                        free(rem->info);
                        free(rem);
                    }
                    free(pilha);

                pilha = criaDescPilha();
                printf("\nMúsicas disponíveis na biblioteca:\n");
                imprimir(biblioteca);

                char tituloEscolhido[256];
                do {
                    printf("\nDigite o título da música para adicionar à playlist: ");
                    fgets(tituloEscolhido, sizeof(tituloEscolhido), stdin);
                    tituloEscolhido[strcspn(tituloEscolhido, "\n")] = '\0';

                    // buscar na biblioteca
                    struct nodo_pilha *aux = biblioteca->topo;
                    int encontrada = 0;
                    while (aux != NULL) {
                        if (strcmp(aux->info->titulo, tituloEscolhido) == 0) {
                            // copiar música para playlist
                            struct musica *copia = malloc(sizeof(struct musica));
                            *copia = *(aux->info);  // cópia de conteúdo
                            struct nodo_pilha *novoNodo = criaNodoPilha(copia);
                            inserir(pilha, novoNodo);
                            printf("Música '%s' adicionada à playlist.\n", copia->titulo);
                            encontrada = 1;
                            break;
                        }
                        aux = aux->prox;
                    }
                    if (!encontrada) {
                        printf("Música não encontrada na biblioteca!\n");
                    }

                    printf("Deseja adicionar mais uma música? (s/n): ");
                    char op;
                    scanf(" %c", &op);
                    getchar();
                    if (op != 's' && op != 'S') {
                        break;
                    }
                } while (1);
                break;
            }
            case 3:
                if (pilha == NULL || pilha->topo == NULL) {
                    printf("Pilha vazia ou inexistente.\n");
                    break;
                }
                struct nodo_pilha *rem = remover(pilha);
                if (rem) {
                    printf("Música '%s' removida do topo.\n", rem->info->titulo);
                    free(rem->info);
                    free(rem);
                }
                break;

            case 4:
                if (pilha == NULL || pilha->topo == NULL) {
                    printf("Pilha vazia ou inexistente.\n");
                } else {
                    struct nodo_pilha *top = topo(pilha);
                    printf("Topo: %s (%s)\n", top->info->titulo, top->info->artista);
                }
                break;

            case 5:
                if (procurarLista(pilha))
                    printf("Sim, existe uma lista com elementos.\n");
                else
                    printf("Não existe uma lista com elementos.\n");
                break;

            case 6:
                imprimir(pilha);
                break;

            case 7:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida, tente novamente!\n");
                break;
        }
    } while (op != 7);
  
    return 0;
}
