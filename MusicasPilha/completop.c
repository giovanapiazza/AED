#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma música
struct musica {
    char titulo[256];
    char artista[256];
    char letra[256];
    int codigo;
    int execucoes;
};

// Nodo da pilha
struct nodo_pilha {
    struct musica *info;
    struct nodo_pilha *prox;
};

// Descritor da pilha
struct desc_pilha {
    struct nodo_pilha *topo;
    int tamanho;
};

// Criação do descritor da pilha
struct desc_pilha *criaDescPilha(void) {
    struct desc_pilha *pilha = malloc(sizeof(struct desc_pilha));
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

// Cria uma música
struct musica *criarMusica() {
    struct musica *m = malloc(sizeof(struct musica));
    if (!m) {
        printf("Erro de alocação!\n");
        exit(1);
    }

    printf("Título: ");
    fgets(m->titulo, sizeof(m->titulo), stdin);
    m->titulo[strcspn(m->titulo, "\n")] = '\0';

    printf("Artista: ");
    fgets(m->artista, sizeof(m->artista), stdin);
    m->artista[strcspn(m->artista, "\n")] = '\0';

    printf("Letra: ");
    fgets(m->letra, sizeof(m->letra), stdin);
    m->letra[strcspn(m->letra, "\n")] = '\0';

    printf("Código: ");
    scanf("%d", &m->codigo);
    printf("Execuções: ");
    scanf("%d", &m->execucoes);
    getchar();
    return m;
}

// Cria nodo da pilha
struct nodo_pilha *criaNodoPilha(struct musica *m) {
    struct nodo_pilha *novo = malloc(sizeof(struct nodo_pilha));
    novo->info = m;
    novo->prox = NULL;
    return novo;
}

// Inserir no topo
void inserir(struct desc_pilha *pilha, struct nodo_pilha *novoElemento) {
    novoElemento->prox = pilha->topo;
    pilha->topo = novoElemento;
    pilha->tamanho++;
}

// Remover do topo
struct nodo_pilha *remover(struct desc_pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Pilha vazia.\n");
        return NULL;
    }
    struct nodo_pilha *aux = pilha->topo;
    pilha->topo = pilha->topo->prox;
    pilha->tamanho--;
    return aux;
}

// Ver o topo
struct nodo_pilha *topo(struct desc_pilha *pilha) {
    return pilha->topo;
}

// Verificar se existe uma lista
int procurarLista(struct desc_pilha *pilha) {
    return pilha != NULL && pilha->topo != NULL;
}

// Ler músicas de um arquivo e mostrar
void lerArquivoMostrarMusicas(const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    char linha[512];
    printf("\nMúsicas disponíveis no arquivo:\n");
    while (fgets(linha, sizeof(linha), fp)) {
        printf("- %s", linha);
    }

    fclose(fp);
}

// Imprimir pilha
void imprimir(struct desc_pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        printf("Pilha vazia.\n");
        return;
    }
    struct nodo_pilha *aux = pilha->topo;
    printf("\n--- Músicas na Pilha ---\n");
    while (aux != NULL) {
        printf("Título: %s\n", aux->info->titulo);
        printf("Artista: %s\n", aux->info->artista);
        printf("Letra: %s\n", aux->info->letra);
        printf("Código: %d\n", aux->info->codigo);
        printf("-----------------------------\n");
        aux = aux->prox;
    }
}

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
            case 0: {
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
            }

            case 1: {
                if (biblioteca == NULL || biblioteca->topo == NULL) {
                    printf("Biblioteca vazia! Adicione um arquivo primeiro.\n");
                    break;
                }

                if (pilha != NULL) {
                    printf("A playlist já existe. Deseja sobrescrevê-la? (s/n): ");
                    char resp;
                    scanf(" %c", &resp);
                    getchar();
                    if (resp != 's' && resp != 'S') break;

                    while (pilha->topo != NULL) {
                        struct nodo_pilha *rem = remover(pilha);
                        free(rem->info);
                        free(rem);
                    }
                    free(pilha);
                }

                pilha = criaDescPilha();
                printf("\nMúsicas disponíveis na biblioteca:\n");
                imprimir(biblioteca);

                char tituloEscolhido[256];
                do {
                    printf("\nDigite o título da música para adicionar à playlist: ");
                    fgets(tituloEscolhido, sizeof(tituloEscolhido), stdin);
                    tituloEscolhido[strcspn(tituloEscolhido, "\n")] = '\0';

                    struct nodo_pilha *aux = biblioteca->topo;
                    int encontrada = 0;
                    while (aux != NULL) {
                        if (strcmp(aux->info->titulo, tituloEscolhido) == 0) {
                            struct musica *copia = malloc(sizeof(struct musica));
                            *copia = *(aux->info);
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
                    if (op != 's' && op != 'S') break;
                } while (1);
                break;
            }

            case 2: {
                if (pilha == NULL) pilha = criaDescPilha();
                struct musica *m = criarMusica();
                struct nodo_pilha *n = criaNodoPilha(m);
                inserir(pilha, n);
                printf("Música inserida!\n");
                break;
            }

            case 3: {
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
            }

            case 4: {
                if (pilha == NULL || pilha->topo == NULL) {
                    printf("Pilha vazia ou inexistente.\n");
                } else {
                    struct nodo_pilha *top = topo(pilha);
                    printf("Topo: %s (%s)\n", top->info->titulo, top->info->artista);
                }
                break;
            }

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

