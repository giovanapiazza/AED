#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotyfon.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void carregarMusicas(const char *nomeArquivo, Lista *lista) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[512];
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';
        Musica m;
        char *token = strtok(linha, ";");
        if (!token) continue;
        strncpy(m.artista, token, sizeof(m.artista) - 1);

        token = strtok(NULL, ";");
        if (!token) continue;
        m.codigo = atoi(token);

        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(m.titulo, token, sizeof(m.titulo) - 1);

        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(m.letra, token, sizeof(m.letra) - 1);

        token = strtok(NULL, ";");
        if (!token) continue;
        m.execucoes = atoi(token);

        inserirMusicaFim(lista, m);
    }
    fclose(arquivo);
}

void imprimirMusica(const Musica *m) {
    printf("\n--- MUSICA ---\n");
    printf("Titulo: %s\n", m->titulo);
    printf("Artista: %s\n", m->artista);
    printf("Codigo: %d\n", m->codigo);
    printf("Letra: %s\n", m->letra);
    printf("Execucoes: %d\n", m->execucoes);
}

//---------------------------------------- PILHA ----------------------------------------//

void criarPilha(Pilha *p) {
    p->topo = NULL;
    p->tamanho = 0;
}

void push(Pilha *p, Musica m) {
    NodoPilha *novo = malloc(sizeof(NodoPilha));
    if (!novo) return;
    novo->musica = m;
    novo->prox = p->topo;
    p->topo = novo;
    p->tamanho++;
}

void imprimirPilha(Pilha *p) {
    NodoPilha *aux = p->topo;
    while (aux != NULL) {
        imprimirMusica(&aux->musica);
        aux = aux->prox;
    }
}

void liberarPilha(Pilha *p) {
    NodoPilha *aux;
    while (p->topo) {
        aux = p->topo;
        p->topo = aux->prox;
        free(aux);
    }
    p->tamanho = 0;
}

int pilhaVazia(Pilha *p) {
    return (p->topo == NULL);
}

//---------------------------------------- FILA ----------------------------------------//

void enqueue(Fila *f, Musica m) {
    NodoFila *novo = malloc(sizeof(NodoFila));
    if (!novo) return;
    novo->musica = m;
    novo->prox = NULL;
    if (f->fim) f->fim->prox = novo;
    else f->inicio = novo;
    f->fim = novo;
    f->tamanho++;
}

void imprimirFila(Fila *f) {
    NodoFila *aux = f->inicio;
    while (aux) {
        imprimirMusica(&aux->musica);
        aux = aux->prox;
    }
}
void inicializarLista(Lista *lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
}

void inserirMusicaFim(Lista *lista, Musica m) {
    Nodo *novo = malloc(sizeof(Nodo));
    if (!novo) return;
    novo->musica = m;
    novo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        Nodo *aux = lista->inicio;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    lista->tamanho++;
}

void liberarLista(Lista *lista) {
    Nodo *aux;
    while (lista->inicio != NULL) {
        aux = lista->inicio;
        lista->inicio = aux->prox;
        free(aux);
    }
    lista->tamanho = 0;
}
void liberarFila(Fila *f) {
    NodoFila *aux;
    while (f->inicio) {
        aux = f->inicio;
        f->inicio = aux->prox;
        free(aux);
    }
    f->fim = NULL;
    f->tamanho = 0;
}
int filaVazia(Fila *f) {
    return f->inicio == NULL;
}

//---------------------------------------- BUSCA ----------------------------------------//
int buscarMusicaLista(Lista *lista, Musica *resultado, int criterio, const char *valorStr, int valorInt) {
    Nodo *atual = lista->inicio;

    if (criterio == 2) {  // Caso artista
        if (valorStr == NULL) return 0;

        // Imprime todas as músicas do artista
        int encontrouAlguma = 0;
        printf("Musicas do artista \"%s\":\n", valorStr);
        while (atual) {
            if (strcasecmp(atual->musica.artista, valorStr) == 0) {
                printf("Codigo: %d | Titulo: %s\n", atual->musica.codigo, atual->musica.titulo);
                encontrouAlguma = 1;
            }
            atual = atual->prox;
        }
        if (!encontrouAlguma) {
            printf("Nenhuma musica encontrada desse artista.\n");
            return 0;
        }

        // Pergunta qual código o usuário quer
        printf("Digite o codigo da musica que deseja escolher: ");
        if (scanf("%d", &valorInt) != 1) {
            while(getchar() != '\n');
            printf("Codigo invalido.\n");
            return 0;
        }
        getchar(); // limpa \n

        // Agora busca pela música pelo código
        atual = lista->inicio;
        while (atual) {
            if (atual->musica.codigo == valorInt) {
                *resultado = atual->musica;
                return 1;
            }
            atual = atual->prox;
        }
        printf("Codigo nao encontrado.\n");
        return 0;
    } 
    else {  // Caso código ou título, busca normal
        while (atual) {
            int encontrou = 0;
            switch (criterio) {
                case 1:
                    if (atual->musica.codigo == valorInt) encontrou = 1;
                    break;
                case 3:
                    if (valorStr && strcasecmp(atual->musica.titulo, valorStr) == 0) encontrou = 1;
                    break;
                default:
                    return 0;
            }
            if (encontrou) {
                *resultado = atual->musica;
                return 1;
            }
            atual = atual->prox;
        }
    }
    return 0;
}


void buscarEInserirMusica(Lista *lista, Fila *fila, Pilha *pilha) {
    int criterio;
    char valorStr[256];
    int valorInt;
    Musica resultado;

    printf("Buscar musica para inserir na playlist:\n");
    printf("0 - Cancelar\n");
    printf("1 - Codigo\n");
    printf("2 - Artista\n");
    printf("3 - Titulo\n");
    printf("Escolha: ");
    if (scanf("%d", &criterio) != 1) return;
    getchar();

    int achou = 0;

    switch (criterio) {
        case 0:
            printf("Operacao cancelada.\n");
            return;

        case 1:
            printf("Digite o codigo: ");
            if (scanf("%d", &valorInt) != 1) {
                while (getchar() != '\n');
                printf("Codigo invalido.\n");
                return;
            }
            getchar();
            achou = buscarMusicaLista(lista, &resultado, 1, NULL, valorInt);
            break;

        case 2: {
            printf("Digite o nome do artista: ");
            if (!fgets(valorStr, sizeof(valorStr), stdin)) {
                printf("Erro na leitura.\n");
                return;
            }
            valorStr[strcspn(valorStr, "\n")] = 0;

            // Mostrar todas as músicas do artista
            Nodo *p = lista->inicio;
            int encontrouAlguma = 0;

            printf("\nMusicas do artista \"%s\":\n", valorStr);
            while (p != NULL) {
                if (strcasecmp(p->musica.artista, valorStr) == 0) {
                    printf("Codigo: %d | Titulo: %s\n", p->musica.codigo, p->musica.titulo);
                    encontrouAlguma = 1;
                }
                p = p->prox;
            }

            if (!encontrouAlguma) {
                printf("Nenhuma musica encontrada desse artista.\n");
                return;
            }

            printf("Digite o codigo da musica que deseja inserir na playlist: ");
            if (scanf("%d", &valorInt) != 1) {
                while (getchar() != '\n');
                printf("Codigo invalido.\n");
                return;
            }
            getchar();

            achou = buscarMusicaLista(lista, &resultado, 1, NULL, valorInt);
            break;
        }

        case 3:
            printf("Digite o titulo: ");
            if (!fgets(valorStr, sizeof(valorStr), stdin)) {
                printf("Erro na leitura.\n");
                return;
            }
            valorStr[strcspn(valorStr, "\n")] = 0;
            achou = buscarMusicaLista(lista, &resultado, 3, valorStr, 0);
            break;

        default:
            printf("Criterio invalido.\n");
            return;
    }

    if (achou) {
        enqueue(fila, resultado);
        push(pilha, resultado);
        printf("Musica inserida na playlist com sucesso!\n");
    } else {
        printf("Musica nao encontrada.\n");
    }
}



void salvarBackup(Fila *fila, const char *nomeback) {
    FILE *arquivo = fopen(nomeback, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar o backup!\n");
        return;
    }

    NodoFila *atual = fila->inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%s; %d; %s; %s; %d\n", atual->musica.artista, atual->musica.codigo, atual->musica.titulo, atual->musica.letra, atual->musica.execucoes);
        atual = atual->prox;
    }

    fclose(arquivo);
    printf("Backup da playlist salvo com sucesso no arquivo '%s'.\n", nomeback);
}

void imprimirTudo(Lista *lista, Fila *fila, Pilha *pilha) {
    int op;
    do {
        printf("\nMenu de Impressao:\n");
        printf("0 - Cancelar\n");
        printf("1 - Imprimir Playlist como fila\n");
        printf("2 - Imprimir Playlist como pilha\n");
        printf("3 - Imprimir uma musica do acervo\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &op) != 1) {
            while (getchar() != '\n');
            printf("Entrada invalida!\n");
            continue;
        }
        getchar(); // limpa o \n

        int criterio;
        char valorStr[256];
        int valorInt;
        Musica resultado;

        switch (op) {
            case 0:
                printf("Comando cancelado.\n");
                break;

            case 1:
                printf("\nPlaylist (Fila):\n");
                if (filaVazia(fila)) {
                    printf("Playlist vazia.\n");
                } else {
                    imprimirFila(fila);
                }
                break;

            case 2:
                printf("\nPlaylist (Pilha):\n");
                if (pilhaVazia(pilha)) {
                    printf("Playlist vazia.\n");
                } else {
                    imprimirPilha(pilha);
                }
                break;

            case 3:
                printf("Buscar musica para imprimir:\n");
                printf("1 - Codigo\n");
                printf("2 - Artista\n");
                printf("3 - Titulo\n");
                printf("Escolha: ");

                if (scanf("%d", &criterio) != 1) {
                    while (getchar() != '\n');
                    printf("Entrada invalida!\n");
                    break;
                }
                getchar();

                int achou = 0;
                switch (criterio) {
                    case 0:
                    printf("Voltando para o menu\n");
                    break;

                    case 1:
                        printf("Codigo: ");
                        if (scanf("%d", &valorInt) != 1) {
                            while (getchar() != '\n');
                            printf("Entrada invalida!\n");
                            break;
                        }
                        getchar();
                        achou = buscarMusicaLista(lista, &resultado, 1, NULL, valorInt);
                        break;

                    case 2:
                        printf("Artista: ");
                        if (!fgets(valorStr, sizeof(valorStr), stdin)) {
                            printf("Erro de leitura.\n");
                            break;
                        }
                        valorStr[strcspn(valorStr, "\n")] = 0;
                        achou = buscarMusicaLista(lista, &resultado, 2, valorStr, 0);
                        break;

                    case 3:
                        printf("Titulo: ");
                        if (!fgets(valorStr, sizeof(valorStr), stdin)) {
                            printf("Erro de leitura.\n");
                            break;
                        }
                        valorStr[strcspn(valorStr, "\n")] = 0;
                        achou = buscarMusicaLista(lista, &resultado, 3, valorStr, 0);
                        break;

                    default:
                        printf("Criterio invalido.\n");
                        break;
                }

                if (achou) {
                    imprimirMusica(&resultado);
                } else {
                    printf("Musica nao encontrada.\n");
                }
                break;

            default:
                printf("Opcao invalida, tente novamente.\n");
                break;
        }

    } while (op != 0);
}

void salvarRelatorio(const char *nomeRelatorio, Fila *fila, Lista *lista) {
    FILE *arq = fopen(nomeRelatorio, "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo '%s'.\n", nomeRelatorio);
        return;
    }

    fprintf(arq, "RELAORIO DA PLAYLIST\n");
    fprintf(arq, "=====================\n\n");

    NodoFila *atual = fila->inicio;
    int contadorPlaylist = 0;

    while (atual != NULL) {
        fprintf(arq, "Titulo: %s\n", atual->musica.titulo);
        fprintf(arq, "Artista: %s\n", atual->musica.artista);
        fprintf(arq, "Codigo: %d\n", atual->musica.codigo);
        fprintf(arq, "Letra: %s\n", atual->musica.letra);
        fprintf(arq, "Execucoes: %d\n", atual->musica.execucoes);
        fprintf(arq, "---------------------------\n");
        contadorPlaylist++;
        atual = atual->prox;
    }

    fprintf(arq, "\nResumo:\n");
    fprintf(arq, "Total de musicas na playlist: %d\n", contadorPlaylist);
    fprintf(arq, "Total de musicas no acervo original: %d\n", lista->tamanho);

    fclose(arq);
    printf("Relatorio salvo com sucesso em '%s'!\n", nomeRelatorio);
}

void carregarBackup(const char *nomeRelatorio, Fila *fila, Pilha *pilha) {
    FILE *arquivo = fopen(nomeRelatorio, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de backup.\n");
        return;
    }

    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Musica m;
        char artista[256], titulo[256], letra[256];
        int codigo, execucoes;

        // Remove \n no final da linha, se existir
        linha[strcspn(linha, "\n")] = 0;

        // Parse da linha com sscanf
        if (sscanf(linha, " %[^;]; %d; %[^;]; %[^;]; %d", artista, &codigo, titulo, letra, &execucoes) == 5) {
            strncpy(m.artista, artista, sizeof(m.artista));
            m.codigo = codigo;
            strncpy(m.titulo, titulo, sizeof(m.titulo));
            strncpy(m.letra, letra, sizeof(m.letra));
            m.execucoes = execucoes;

            enqueue(fila, m);
            push(pilha, m);
        }
    }

    fclose(arquivo);
    printf("Backup carregado com sucesso e musicas inseridas na playlist!\n");
}

void importacao(Lista *lista, Fila *fila, Pilha *pilha, int *carregouArquivo) {
    int tipo;
    char nomeArq[100];

    printf("Importar:\n");
    printf("1 - Acervo de musicas\n");
    printf("2 - Backup da playlist\n");
    printf("Escolha: ");

    if (scanf("%d", &tipo) != 1) {
        while (getchar() != '\n');
        printf("Entrada invalida!\n");
        return;
    }
    getchar();

    printf("Digite o nome do arquivo: ");
    fgets(nomeArq, sizeof(nomeArq), stdin);
    nomeArq[strcspn(nomeArq, "\n")] = 0;

    switch (tipo) {
        case 1:
            carregarMusicas(nomeArq, lista);
            *carregouArquivo = 1;
            printf("Arquivo do acervo carregado com sucesso!\n");
            break;

        case 2:
            liberarFila(fila);
            liberarPilha(pilha);
            criarFila(fila);
            criarPilha(pilha);
            carregarBackup(nomeArq, fila, pilha);
            *carregouArquivo = 1;
            printf("Backup carregado com sucesso!\n");
            break;

        default:
            printf("Opcao invalida.\n");
            break;
    }
}

void criarPlaylist(Fila *fila, Pilha *pilha) {
    char confirmacao;

    printf("Ao fazer isso, voce ira sobrescrever a playlist anterior.\n");
    printf("Tem certeza que deseja continuar? (s/n): ");
    scanf(" %c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S') {
        liberarFila(fila);
        liberarPilha(pilha);
        criarFila(fila);
        criarPilha(pilha);
        printf("Nova playlist criada com sucesso!\n");
    } else {
        printf("Comando cancelado.\n");
    }
}


