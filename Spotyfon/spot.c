#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotyfon.h"

// --------------------------Pilha------------------------------
// Função para criar a descrição da pilha
struct desc_pilha *criaDescPilha(void) {
    struct desc_pilha *pilha = malloc(sizeof(struct desc_pilha));
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

// Cria nodo da pilha
struct nodo_pilha *criaNodoPilha(struct musica *m) {
    struct nodo_pilha *novo = malloc(sizeof(struct nodo_pilha));
    novo->info = m;
    novo->prox = NULL;
    return novo;
}

void inserirPilha(struct desc_pilha *pilha, struct nodo_pilha *novoElemento) {
    novoElemento->prox = pilha->topo;
    pilha->topo = novoElemento;
    pilha->tamanho++;
}

// Verifica se existe uma pilha
int existePilha(struct desc_pilha *pilha) {
    return pilha != NULL;
}

int tamanhoPilha(struct desc_pilha *pilha) {
    if (pilha == NULL){
        return -1;  // Retorna -1 se a pilha não existir
    } else {
    return pilha->tamanho;
    }
}

// Imprimir pilha
void imprimirPilha(struct desc_pilha *pilha) {
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

void salvarPilhaSimples(struct desc_pilha *pilha, const char *nomeArquivo) {
    if (!pilha || pilha->tamanho == 0) {
        printf("Pilha vazia ou não existe, nada a salvar.\n");
        return;
    }

    FILE *fp = fopen(nomeArquivo, "w");
    if (!fp) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    // Salva o tamanho da pilha primeiro
    fprintf(fp, "%d\n", pilha->tamanho);

    struct nodo_pilha *aux = pilha->topo;
    while (aux) {
        fprintf(fp, "%s;%d\n", aux->info->titulo, aux->info->codigo);
        aux = aux->prox;
    }

    fclose(fp);
    printf("Pilha salva no arquivo %s com sucesso.\n", nomeArquivo);
}

void exportarPilhaCompleta(struct desc_pilha *pilha, const char *nomeArquivo) {
    if (!pilha || pilha->tamanho == 0) {
        printf("Pilha vazia ou inexistente. Nada a exportar.\n");
        return;
    }

    FILE *fp = fopen(nomeArquivo, "w");
    if (!fp) {
        printf("Erro ao criar o arquivo %s.\n", nomeArquivo);
        return;
    }

    fprintf(fp, "Tamanho: %d\n", pilha->tamanho);

    struct nodo_pilha *aux = pilha->topo;
    while (aux) {
        fprintf(fp, "%s;%s;%s;%d;%d\n",
                aux->info->titulo,
                aux->info->artista,
                aux->info->letra,
                aux->info->codigo,
                aux->info->execucoes);
        aux = aux->prox;
    }

    fclose(fp);
    printf("Pilha exportada com sucesso para %s.\n", nomeArquivo);
}


//------------------------------------------Fila----------------------------------------------------
// Cria e retorna uma fila vazia
struct desc_fila *Createfila() {
    struct desc_fila *fila = malloc(sizeof(struct desc_fila));
    fila->head = fila->tail = NULL;
    fila->tamanho = 0;
    return fila;
}
// Libera toda a memória da fila e de suas músicas
void liberarFila(struct desc_fila *fila) {
    struct nodo_fila *atual = fila->head;
    while (atual != NULL) {
        struct nodo_fila *prox = atual->prox;
        free(atual->info); // libera a música
        free(atual);       // libera o nodo
        atual = prox;
    }
    free(fila);
}



// Insere uma nova música no fim da fila
void inserirFila(struct desc_fila *fila, struct musica *m) {
    struct nodo_fila *novo = malloc(sizeof(struct nodo_fila));
    novo->info = m;
    novo->prox = NULL;

    if (fila->tail) 
        fila->tail->prox = novo; // Liga o último ao novo
    else 
        fila->head = novo;       // Se a fila estava vazia, novo também é o head

    fila->tail = novo;           // Atualiza o tail
    fila->tamanho++;             // Incrementa o tamanho
}


// Verifica se existe uma fila
int existeFila(struct desc_fila *fila) {
    return fila != NULL;
}

int tamanhoFila(struct desc_fila *fila) {
    if (fila == NULL){
        return -1; // Retorna -1 se a fila não existir
    } else {
    return fila->tamanho;
    }
}

// Exibe todas as músicas da fila
void imprimirFila(struct desc_fila *fila) {
    if (EMPTY(fila)) {
        printf("Fila vazia.\n");
        return;
    }

    struct nodo_fila *aux = fila->head;
    printf("\n--- Músicas na Fila ---\n");

    while (aux != NULL) {
        printf("Título: %s\n", aux->info->titulo);
        printf("Artista: %s\n", aux->info->artista);
        printf("Letra: %s\n", aux->info->letra);
        printf("Código: %d\n", aux->info->codigo);
        printf("Execuções: %d\n", aux->info->execucoes);
        printf("-----------------------------\n");
        aux = aux->prox;
    }
}

void salvarFilaSimples(struct desc_fila *fila, const char *nomeArquivo) {
    if (!fila || fila->tamanho == 0) {
        printf("Fila vazia ou não existe, nada a salvar.\n");
        return;
    }

    FILE *fp = fopen(nomeArquivo, "w");
    if (!fp) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    // Salva o tamanho da fila primeiro
    fprintf(fp, "%d\n", fila->tamanho);

    struct nodo_fila *aux = fila->head;
    while (aux) {
        fprintf(fp, "%s;%d\n", aux->info->titulo, aux->info->codigo);
        aux = aux->prox;
    }

    fclose(fp);
    printf("Fila salva no arquivo %s com sucesso.\n", nomeArquivo);
}

void exportarFilaCompleta(struct desc_fila *fila, const char *nomeArquivo) {
    if (!fila || fila->tamanho == 0) {
        printf("Fila vazia ou inexistente. Nada a exportar.\n");
        return;
    }

    FILE *fp = fopen(nomeArquivo, "w");
    if (!fp) {
        printf("Erro ao criar o arquivo %s.\n", nomeArquivo);
        return;
    }

    fprintf(fp, "Tamanho: %d\n", fila->tamanho);

    struct nodo_fila *aux = fila->head;
    while (aux) {
        fprintf(fp, "%s;%s;%s;%d;%d\n",
                aux->info->titulo,
                aux->info->artista,
                aux->info->letra,
                aux->info->codigo,
                aux->info->execucoes);
        aux = aux->prox;
    }

    fclose(fp);
    printf("Fila exportada com sucesso para %s.\n", nomeArquivo);
}


//------------------------------------------ Geral--------------------------------------------------
void lerArquivo(const char *nomeArquivo) {
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

void imprimir(struct desc_fila *fila, struct desc_pilha *pilha) {
    char resp;
    printf("Deseja imprimir em forma de pilha? (s/n): ");
    scanf(" %c", &resp); 

    if (resp == 's' || resp == 'S') {
        imprimirPilha(pilha);
    } else {
        imprimirFila(fila);
    }
}

void buscarEInserirMusica(const char *nomeArquivo, struct desc_fila *fila, struct desc_pilha *pilha) {
    int criterio;
    char valorStr[256];
    int valorInt;
    Musica resultado;

    printf("Buscar música para inserir:\n");
    printf("1 - Código\n");
    printf("2 - Artista\n");
    printf("3 - Título\n");
    printf("Escolha critério: ");
    scanf("%d", &criterio);
    getchar(); 

    int achou = 0;
    switch (criterio) {
        case 1:
            printf("Digite o código da música: ");
            scanf("%d", &valorInt);
            getchar();
            achou = buscarMusicaArquivo(nomeArquivo, &resultado, 1, NULL, valorInt);
            break;

        case 2:
            printf("Digite o nome do artista: ");
            fgets(valorStr, sizeof(valorStr), stdin);
            valorStr[strcspn(valorStr, "\n")] = 0;
            achou = buscarMusicaArquivo(nomeArquivo, &resultado, 2, valorStr, 0);
            break;

        case 3:
            printf("Digite o título da música: ");
            fgets(valorStr, sizeof(valorStr), stdin);
            valorStr[strcspn(valorStr, "\n")] = 0;
            achou = buscarMusicaArquivo(nomeArquivo, &resultado, 3, valorStr, 0);
            break;

        default:
            printf("Critério inválido.\n");
            return;
    }

    if (achou) {
        inserir(fila, pilha, &resultado);
        printf("Música inserida na com sucesso!\n");
    } else {
        printf("Música não encontrada no arquivo.\n");
    }
}


void existe(struct desc_fila *fila, struct desc_pilha *pilha) {
    if (existeFila(fila)) {
        printf("Fila existe.\n");
    } else {
        printf("Fila não existe.\n");
    }

    if (existePilha(pilha)) {
        printf("Pilha existe.\n");
    } else {
        printf("Pilha não existe.\n");
    }
}


void mostrarTamanhos(struct desc_fila *fila, struct desc_pilha *pilha) {
    int tamFila = tamanhoFila(fila);
    int tamPilha = tamanhoPilha(pilha);

    printf("\n===== TAMANHO DAS ESTRUTURAS =====\n");

    if (tamFila >= 0)
        printf("Fila contém %d música(s).\n", tamFila);
    else
        printf("Fila não foi criada.\n");

    if (tamPilha >= 0)
        printf("Pilha contém %d música(s).\n", tamPilha);
    else
        printf("Pilha não foi criada.\n");

    printf("==================================\n");
}
//--------------------------------------------Buscar--------------------------------------------------
void buscarMusicaPlaylistPorTitulo(const char *titulo, Musica *resultado) {
    struct nodo_fila *atual = minhaFila->head;

    while (atual != NULL) {
        if (strcmp(atual->info->titulo, titulo) == 0) {
            *resultado = *(atual->info);
            printf("\nMúsica encontrada!\n");
            printf("Título: %s\n", resultado->titulo);
            printf("Artista: %s\n", resultado->artista);
            printf("Letra: %s\n", resultado->letra);
            printf("Código: %d\n", resultado->codigo);
            printf("Execuções: %d\n", resultado->execucoes);
            return;
        }
        atual = atual->prox;
    }

    printf("Música com título \"%s\" não encontrada na playlist.\n", titulo);
}

void buscarMusicaPlaylistPorArtista(const char *artista, Musica *resultado) {
    struct nodo_fila *atual = minhaFila->head;

    while (atual != NULL) {
        if (strcmp(atual->info->artista, artista) == 0) {
            *resultado = *(atual->info);
            printf("\nMúsica encontrada!\n");
            printf("Título: %s\n", resultado->titulo);
            printf("Artista: %s\n", resultado->artista);
            printf("Letra: %s\n", resultado->letra);
            printf("Código: %d\n", resultado->codigo);
            printf("Execuções: %d\n", resultado->execucoes);
            return;
        }
        atual = atual->prox;
    }

    printf("Nenhuma música do artista \"%s\" encontrada na playlist.\n", artista);
}

void buscarMusicaPlaylistPorCodigo(int codigo, Musica *resultado) {
    struct nodo_fila *atual = minhaFila->head;

    while (atual != NULL) {
        if (atual->info->codigo == codigo) {
            *resultado = *(atual->info);  // copia os dados
            printf("\nMúsica encontrada!\n");
            printf("Título: %s\n", resultado->titulo);
            printf("Artista: %s\n", resultado->artista);
            printf("Letra: %s\n", resultado->letra);
            printf("Código: %d\n", resultado->codigo);
            printf("Execuções: %d\n", resultado->execucoes);
            return;
        }
        atual = atual->prox;
    }

    printf("Música com código %d não encontrada na playlist.\n", codigo);
}

int buscarMusicaArquivo(const char *nomeArquivo, Musica *resultado, int criterio, const char *valorStr, int valorInt) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }

    char linha[512];
    Musica temp;

    while (fgets(linha, sizeof(linha), fp)) {
        // Parse da linha lida
        if (sscanf(linha, "%[^;];%[^;];%[^;];%d;%d", 
                   temp.titulo, temp.artista, temp.letra, &temp.codigo, &temp.execucoes) == 5) {

            int encontrou = 0;

            switch (criterio) {
                case 1: // Por código
                    if (temp.codigo == valorInt)
                        encontrou = 1;
                    break;

                case 2: // Por artista
                    if (strcmp(temp.artista, valorStr) == 0)
                        encontrou = 1;
                    break;

                case 3: // Por título
                    if (strcmp(temp.titulo, valorStr) == 0)
                        encontrou = 1;
                    break;

                default:
                    printf("Critério inválido.\n");
                    fclose(fp);
                    return 0;
            }

            if (encontrou) {
                *resultado = temp;
                printf("\nMúsica encontrada no arquivo!\n");
                printf("Título: %s\n", resultado->titulo);
                printf("Artista: %s\n", resultado->artista);
                printf("Letra: %s\n", resultado->letra);
                printf("Código: %d\n", resultado->codigo);
                printf("Execuções: %d\n", resultado->execucoes);
                fclose(fp);
                return 1;
            }
        }
    }

    printf("Música não encontrada no arquivo.\n");
    fclose(fp);
    return 0;
}


void buscarMusica(const char *nomeArquivo, Musica *resultado, struct desc_fila *fila, struct desc_pilha *pilha) {
    int bus, criterio;
    char valorStr[256];
    int valorInt;

    printf("\n=== BUSCA DE MÚSICAS ===\n");

    // Se a fila não existir ou estiver vazia, pule direto para buscar no arquivo
    if (fila == NULL || fila->tamanho == 0) {
        printf("Playlist vazia ou não criada. Buscando diretamente no arquivo.\n");
        bus = 2;
    } else {
        printf("1 - Buscar na playlist\n");
        printf("2 - Buscar no arquivo\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &bus);
        getchar(); // limpa o '\n'
    }

    switch (bus) {
        case 0:
            printf("Voltando...\n");
            break;

        case 1:
            printf("\nVocê escolheu buscar na playlist.\n");
            printf("1 - Buscar por código\n");
            printf("2 - Buscar por artista\n");
            printf("3 - Buscar por título\n");
            printf("0 - Sair\n");
            printf("Escolha o critério: ");
            scanf("%d", &criterio);
            getchar();

            switch (criterio) {
                case 0:
                    printf("Busca cancelada.\n");
                    break;

                case 1:
                    printf("Digite o código da música: ");
                    scanf("%d", &valorInt);
                    buscarMusicaPlaylistPorCodigo(valorInt, resultado); 
                    break;

                case 2:
                    printf("Digite o nome do artista: ");
                    fgets(valorStr, sizeof(valorStr), stdin);
                    valorStr[strcspn(valorStr, "\n")] = 0; 
                    buscarMusicaPlaylistPorArtista(valorStr, resultado); 
                    break;

                case 3:
                    printf("Digite o título da música: ");
                    fgets(valorStr, sizeof(valorStr), stdin);
                    valorStr[strcspn(valorStr, "\n")] = 0;
                    buscarMusicaPlaylistPorTitulo(valorStr, resultado); 
                    break;

                default:
                    printf("Critério inválido.\n");
            }
            break;

        case 2: {
            printf("\nVocê escolheu buscar no arquivo.\n");
            printf("1 - Buscar por código\n");
            printf("2 - Buscar por artista\n");
            printf("3 - Buscar por título\n");
            printf("0 - Sair\n");
            printf("Escolha o critério: ");
            scanf("%d", &criterio);
            getchar();

            int achou = 0;

            switch (criterio) {
                case 0:
                    printf("Busca cancelada.\n");
                    break;

                case 1:
                    printf("Digite o código da música: ");
                    scanf("%d", &valorInt);
                    achou = buscarMusicaArquivo(nomeArquivo, resultado, 1, NULL, valorInt);
                    break;

                case 2:
                    printf("Digite o nome do artista: ");
                    fgets(valorStr, sizeof(valorStr), stdin);
                    valorStr[strcspn(valorStr, "\n")] = 0;
                    achou = buscarMusicaArquivo(nomeArquivo, resultado, 2, valorStr, 0);
                    break;

                case 3:
                    printf("Digite o título da música: ");
                    fgets(valorStr, sizeof(valorStr), stdin);
                    valorStr[strcspn(valorStr, "\n")] = 0;
                    achou = buscarMusicaArquivo(nomeArquivo, resultado, 3, valorStr, 0);
                    break;

                default:
                    printf("Critério inválido.\n");
                    break;
            }

            // Se achou no arquivo, pergunta se quer inserir na playlist
            if (achou) {
                char resp;
                printf("Deseja adicionar essa música na playlist? (s/n): ");
                scanf(" %c", &resp);
                if (resp == 's' || resp == 'S') {
                    // Cria um nodo para inserir
                    struct nodo_pilha *novoNodo = criaNodoPilha(resultado);
                    inserirFila(fila, resultado);
                    inserirPilha(pilha, novoNodo);
                    printf("Música adicionada à playlist com sucesso!\n");
                } else {
                    printf("Música não adicionada à playlist.\n");
                }
            }

            break;
        }

        default:
            printf("Opção inválida.\n");
    }
}

void salvarPlaylistSimples(struct desc_fila *fila, struct desc_pilha *pilha,const char *nomeArquivoFila, const char *nomeArquivoPilha) { 
    int resp= -1;

    do {
        printf("\nComo quer salvar?\n");
        printf("1 - Salvar como Pilha\n");
        printf("2 - Salvar como Fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &resp);
        getchar(); // limpa o '\n'

        switch (resp) {
            case 0:
                printf("Saindo...\n");
                break;
            case 1:
                salvarPilhaSimples(pilha, nomeArquivoPilha);
                break;
            case 2:
                salvarFilaSimples(fila, nomeArquivoFila);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (resp != 0);
}

void exportarPlaylistCompleta(struct desc_fila *fila, struct desc_pilha *pilha) {
    int opcao;

    do {
        printf("\n=== EXPORTAR PLAYLIST ===\n");
        printf("1 - Exportar como Fila\n");
        printf("2 - Exportar como Pilha\n");
        printf("0 - Cancelar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o '\n'

        switch (opcao) {
            case 1:
                exportarFilaCompleta(fila, "playlist_fila_completa.txt");
                break;
            case 2:
                exportarPilhaCompleta(pilha, "playlist_pilha_completa.txt");
                break;
            case 0:
                printf("Exportação cancelada.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);
}

