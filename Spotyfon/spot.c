#include "spotyfon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------- LISTA ----------------------------------------//
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
void criarFila(Fila *f) {
    f->inicio = f->fim = NULL;
    f->tamanho = 0;
}

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


//---------------------------------------- BUSCA ----------------------------------------//
int buscarMusicaLista(Lista *lista, Musica *resultado, int criterio, const char *valorStr, int valorInt) {
    Nodo *atual = lista->inicio;

    switch (criterio) {
        case 1:  // Buscar por código
            while (atual) {
                if (atual->musica.codigo == valorInt) {
                    *resultado = atual->musica;
                    return 1;
                }
                atual = atual->prox;
            }
            break;

        case 2: { // Buscar por artista
            if (valorStr == NULL) return 0;

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

            printf("Digite o codigo da musica que deseja escolher: ");
            if (scanf("%d", &valorInt) != 1) {
                while (getchar() != '\n');
                printf("Codigo invalido.\n");
                return 0;
            }
            getchar(); // limpar \n

            // Buscar novamente pelo código
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

        case 3:  // Buscar por título
            if (valorStr == NULL) return 0;
            while (atual) {
                if (strcasecmp(atual->musica.titulo, valorStr) == 0) {
                    *resultado = atual->musica;
                    return 1;
                }
                atual = atual->prox;
            }
            break;

        default:
            printf("Criterio invalido.\n");
            return 0;
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

        case 2:
            printf("Digite o nome do artista: ");
            if (!fgets(valorStr, sizeof(valorStr), stdin)) {
                printf("Erro na leitura.\n");
                return;
            }
            valorStr[strcspn(valorStr, "\n")] = 0;
            achou = buscarMusicaLista(lista, &resultado, 2, valorStr, 0);  // Tudo tratado lá dentro
            break;

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
        resultado.execucoes = 0;
        enqueue(fila, resultado);
        push(pilha, resultado);
        printf("Musica inserida na playlist com sucesso!\n");
    } else {
        printf("Musica nao encontrada.\n");
    }
}

void executarPlaylist(Fila *fila, Pilha *pilha) {
    if (filaVazia(fila)) {
        printf("A playlist esta vazia. Nada para executar.\n");
        return;
    }

    NodoFila *auxFila = fila->inicio;
    printf("\n--- Executando Playlist ---\n");
    while (auxFila) {
        auxFila->musica.execucoes++;
        imprimirMusica(&auxFila->musica);
        auxFila = auxFila->prox;
    }

    NodoPilha *auxPilha = pilha->topo;
    while (auxPilha) {
        auxPilha->musica.execucoes++;
        auxPilha = auxPilha->prox;
    }

    printf("--- Playlist executada com sucesso! ---\n");
}


void salvarPlaylist(Fila *fila, const char *nomeplay) {
    FILE *arquivo = fopen(nomeplay, "w");
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
    printf("Backup da playlist salvo com sucesso no arquivo '%s'.\n", nomeplay);
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
                printf("0 - Cancelar\n");
                printf("1 - Codigo\n");
                printf("2 - Artista\n");
                printf("3 - Titulo\n");
                printf("Escolha: ");
                scanf("%d", &criterio);
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

void salvarBackup(const char *nomeArquivo, Lista *lista) {
    FILE *arq = fopen(nomeArquivo, "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo '%s'.\n", nomeArquivo);
        return;
    }

    Nodo *atual = lista->inicio;
    while (atual != NULL) {
        fprintf(arq, "%s;%d;%s;%s;%d\n",
                atual->musica.artista,
                atual->musica.codigo,
                atual->musica.titulo,
                atual->musica.letra,
                atual->musica.execucoes);
        atual = atual->prox;
    }

    fclose(arq);
    printf("Backup do acervo salvo com sucesso em '%s'.\n", nomeArquivo);
}

void carregarBackup(const char *nomebacktorio, Fila *fila, Pilha *pilha) {
    FILE *arquivo = fopen(nomebacktorio, "r");
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

void importacao(Lista *lista, Fila *fila, Pilha *pilha, int *carregouArquivo, char *nomeArquivo) {
    int tipo;
    char nomeArq[100];

    printf("Importar:\n");
    printf("0- Cancelar\n");
    printf("1 - Acervo de musicas\n");
    printf("2 - Backup da playlist\n");
    printf("Escolha: ");
    scanf("%d", &tipo);
    getchar();

    printf("Digite o nome do arquivo: ");
    fgets(nomeArq, sizeof(nomeArq), stdin);
    nomeArq[strcspn(nomeArq, "\n")] = 0;

    strncpy(nomeArquivo, nomeArq, 255);
    nomeArquivo[255] = '\0';

    switch (tipo) {
        case 0:
            printf("Cancelando operacao.\n");
            break;
            
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

void salvarRelatorio(const char *nomeRelatorio, Fila *fila, Lista *lista, const char *nomeArquivoAcervo) {
    FILE *arq = fopen(nomeRelatorio, "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo '%s'.\n", nomeRelatorio);
        return;
    }

    fprintf(arq, "RELATORIO DA PLAYLIST\n");
    fprintf(arq, "Arquivo de Acervo: %s\n", nomeArquivoAcervo);

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

void backup(const char *nomeArquivo, Lista *lista, Fila *fila, int carregouArquivo) {
    int esc;

    do {
        printf("\nForma de backup\n");
        printf("0 - Cancelar\n");
        printf("1 - Backup Geral (acervo)\n");
        printf("2 - Backup da Playlist\n");
        printf("Escolha: ");
        scanf("%d", &esc);
        getchar();

        switch (esc) {
            case 0:
                printf("Operacao cancelada.\n");
                break;

            case 1: {
                char nomeback[100];
                printf("Digite o nome do arquivo para salvar o backup geral (ex: backupgeral.txt): ");
                fgets(nomeback, sizeof(nomeback), stdin);
                nomeback[strcspn(nomeback, "\n")] = 0;

                salvarBackup(nomeback, lista);
                break;
            }

            case 2:
                if (!carregouArquivo) {
                    printf("Voce deve carregar um arquivo primeiro.\n");
                    break;
                }
                if (filaVazia(fila)) {
                    printf("A playlist esta vazia. Nada a salvar.\n");
                } else {
                    char nomeplay[100];
                    printf("Digite o nome do arquivo para backup da playlist (ex: backup.txt): ");
                    fgets(nomeplay, sizeof(nomeplay), stdin);
                    nomeplay[strcspn(nomeplay, "\n")] = 0;

                    salvarPlaylist(fila, nomeplay);
                }
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (esc != 0);
}
