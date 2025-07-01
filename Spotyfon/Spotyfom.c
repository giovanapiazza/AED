#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char artista[256];
    int codigo;
    char titulo[256];
    char letra[256];
    int execucoes;
} Musica;

struct nodo_pilha {
    Musica *info;
    struct nodo_pilha *prox;
}; 

struct desc_pilha {
    NodoPilha *topo;
    int tamanho;
};

struct nodo_fila {
    Musica *info;
    struct nodo_fila *prox;
}; 

struct desc_fila {
    NodoFila *head;
    NodoFila *tail;
    int tamanho;
}; 

int carregarMusicas(const char *nomeArquivo, Musica lista[]) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    char linha[512];
    int qtd = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;

        char *token = strtok(linha, ";");
        if (token == NULL) continue;
        strncpy(lista[qtd].artista, token, sizeof(lista[qtd].artista));

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        lista[qtd].codigo = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(lista[qtd].titulo, token, sizeof(lista[qtd].titulo));

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(lista[qtd].letra, token, sizeof(lista[qtd].letra));

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        lista[qtd].execucoes = atoi(token);  

        qtd++;
    }

    fclose(arquivo);
    return qtd;
}

// -----------------------------pilha-------------------------------------------------------------------------
typedef struct nodoPilha {
    Musica *musica;
    struct nodoPilha *prox;
} NodoPilha;

typedef struct descPilha {
    NodoPilha *topo;
    int tamanho;
} DescPilha;

DescPilha *criaDescPilha(void) {
    DescPilha *pilha = (DescPilha *)malloc(sizeof(DescPilha));
    if (pilha == NULL) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

// Cria um nodo da pilha com uma música (passar endereço da música)
NodoPilha *criaNodoPilha(Musica *m) {
    NodoPilha *novo = (NodoPilha *)malloc(sizeof(NodoPilha));
    if (novo == NULL) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    novo->musica = m;
    novo->prox = NULL;
    return novo;
}

// Insere elemento no topo da pilha
void inserirPilha(DescPilha *pilha, NodoPilha *novoElemento) {
    if (!pilha || !novoElemento) return;

    novoElemento->prox = pilha->topo;
    pilha->topo = novoElemento;
    pilha->tamanho++;
}

// Retorna 1 se pilha tem elementos, 0 se vazia
int existePilha(DescPilha *pilha) {
    if (!pilha) return 0;
    return pilha->topo != NULL;
}

// Retorna o tamanho da pilha
int tamanhoPilha(DescPilha *pilha) {
    if (!pilha) return 0;
    return pilha->tamanho;
}

// Imprime o conteúdo da pilha (do topo para baixo)
void imprimirPilha(DescPilha *pilha) {
    if (!pilha) {
        printf("Pilha não existe!\n");
        return;
    }
    NodoPilha *atual = pilha->topo;
    printf("Pilha (topo -> base):\n");
    while (atual) {
        Musica *m = atual->musica;
        printf("Artista: %s | Código: %d | Título: %s | Execuções: %d\n",
               m->artista, m->codigo, m->titulo, m->execucoes);
        atual = atual->prox;
    }
}

// Salva somente os títulos e artistas da pilha em arquivo texto (modo simples)
void salvarPilhaSimples(DescPilha *pilha, const char *nomeArquivo) {
    if (!pilha) return;
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }
    NodoPilha *atual = pilha->topo;
    while (atual) {
        Musica *m = atual->musica;
        fprintf(f, "%s;%s\n", m->artista, m->titulo);
        atual = atual->prox;
    }
    fclose(f);
}

// Exporta a pilha completa com todos os campos em arquivo texto
void exportarPilhaCompleta(DescPilha *pilha, const char *nomeArquivo) {
    if (!pilha) return;
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao abrir o arquivo para exportar!\n");
        return;
    }
    NodoPilha *atual = pilha->topo;
    while (atual) {
        Musica *m = atual->musica;
        // Salvando no formato com ';' entre campos, igual seu arquivo original
        fprintf(f, "%s;%d;%s;%s;%d\n",
                m->artista, m->codigo, m->titulo, m->letra, m->execucoes);
        atual = atual->prox;
    }
    fclose(f);
}

// Libera toda a memória da pilha (não libera as músicas, só os nodos e descritor)
void freePilha(DescPilha *pilha) {
    if (!pilha) return;
    NodoPilha *atual = pilha->topo;
    while (atual) {
        NodoPilha *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(pilha);
}

//----------------------------------------------------Fila---------------------------------------------------------------------
typedef struct nodoFila {
    Musica *musica;
    struct nodoFila *prox;
} NodoFila;

typedef struct descFila {
    NodoFila *inicio;
    NodoFila *fim;
    int tamanho;
} DescFila;

// Cria uma fila vazia
DescFila *Createfila(void) {
    DescFila *fila = (DescFila *)malloc(sizeof(DescFila));
    if (!fila) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

// Cria um nodo de fila sem música (vazia)
NodoFila *criaNodoFila(void) {
    NodoFila *novo = (NodoFila *)malloc(sizeof(NodoFila));
    if (!novo) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    novo->musica = NULL;
    novo->prox = NULL;
    return novo;
}

// Insere música no fim da fila
void inserirFila(DescFila *fila, Musica *m) {
    if (!fila || !m) return;
    NodoFila *novo = (NodoFila *)malloc(sizeof(NodoFila));
    if (!novo) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    novo->musica = m;
    novo->prox = NULL;

    if (fila->fim == NULL) {
        // fila vazia
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->tamanho++;
}

// Retorna 1 se fila tem elementos, 0 se vazia
int existeFila(DescFila *fila) {
    if (!fila) return 0;
    return fila->inicio != NULL;
}

// Retorna tamanho da fila
int tamanhoFila(DescFila *fila) {
    if (!fila) return 0;
    return fila->tamanho;
}

// Imprime todos os elementos da fila (do início para o fim)
void imprimirFila(DescFila *fila) {
    if (!fila) {
        printf("Fila não existe!\n");
        return;
    }
    NodoFila *atual = fila->inicio;
    printf("Fila (início -> fim):\n");
    while (atual) {
        Musica *m = atual->musica;
        printf("Artista: %s | Código: %d | Título: %s | Execuções: %d\n",
               m->artista, m->codigo, m->titulo, m->execucoes);
        atual = atual->prox;
    }
}

// Salva somente artista e título no arquivo (modo simples)
void salvarFilaSimples(DescFila *fila, const char *nomeArquivo) {
    if (!fila) return;
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao abrir arquivo para salvar!\n");
        return;
    }
    NodoFila *atual = fila->inicio;
    while (atual) {
        Musica *m = atual->musica;
        fprintf(f, "%s;%s\n", m->artista, m->titulo);
        atual = atual->prox;
    }
    fclose(f);
}

// Exporta todos os dados da fila para arquivo texto
void exportarFilaCompleta(DescFila *fila, const char *nomeArquivo) {
    if (!fila) return;
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao abrir arquivo para exportar!\n");
        return;
    }
    NodoFila *atual = fila->inicio;
    while (atual) {
        Musica *m = atual->musica;
        fprintf(f, "%s;%d;%s;%s;%d\n",
                m->artista, m->codigo, m->titulo, m->letra, m->execucoes);
        atual = atual->prox;
    }
    fclose(f);
}

// Libera toda a memória da fila (não libera as músicas em si)
void freeFila(DescFila *fila) {
    if (!fila) return;
    NodoFila *atual = fila->inicio;
    while (atual) {
        NodoFila *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(fila);
}




//-------------------------------------------------Geral-----------------------------------------------------

void imprimir(DescFila *fila, DescPilha *pilha) {
    printf("====== Conteúdo da Fila ======\n");
    if (existeFila(fila)) {
        imprimirFila(fila);
    } else {
        printf("Fila vazia.\n");
    }

    printf("\n====== Conteúdo da Pilha ======\n");
    if (existePilha(pilha)) {
        imprimirPilha(pilha);
    } else {
        printf("Pilha vazia.\n");
    }
}

// Busca por título na fila
int buscarMusicaPlaylistPorTitulo(DescFila *fila, const char *titulo, Musica *resultado) {
    if (!fila || !titulo || !resultado) return 0;

    NodoFila *atual = fila->inicio;

    while (atual != NULL) {
        if (strcmp(atual->musica->titulo, titulo) == 0) {
            *resultado = *(atual->musica);
            imprimirMusica(resultado);
            return 1;
        }
        atual = atual->prox;
    }

    printf("Música com título \"%s\" não encontrada na playlist.\n", titulo);
    return 0;
}

// Busca por artista na fila
int buscarMusicaPlaylistPorArtista(DescFila *fila, const char *artista, Musica *resultado) {
    if (!fila || !artista || !resultado) return 0;

    NodoFila *atual = fila->inicio;

    while (atual != NULL) {
        if (strcmp(atual->musica->artista, artista) == 0) {
            *resultado = *(atual->musica);
            imprimirMusica(resultado);
            return 1;
        }
        atual = atual->prox;
    }

    printf("Nenhuma música do artista \"%s\" encontrada na playlist.\n", artista);
    return 0;
}

// Busca por código na fila
int buscarMusicaPlaylistPorCodigo(DescFila *fila, int codigo, Musica *resultado) {
    if (!fila || !resultado) return 0;

    NodoFila *atual = fila->inicio;

    while (atual != NULL) {
        if (atual->musica->codigo == codigo) {
            *resultado = *(atual->musica);
            imprimirMusica(resultado);
            return 1;
        }
        atual = atual->prox;
    }

    printf("Música com código %d não encontrada na playlist.\n", codigo);
    return 0;
}


void salvarPlaylistSimples(DescFila *fila, DescPilha *pilha, const char *nomeArquivoFila, const char *nomeArquivoPilha) {
    int opcao;
    char linha[100];

    do {
        printf("\n=== SALVAR PLAYLIST SIMPLES ===\n");
        printf("1 - Salvar playlist da Fila\n");
        printf("2 - Salvar playlist da Pilha\n");
        printf("0 - Cancelar\n");
        printf("Escolha uma opção: ");

        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            printf("Erro na leitura. Tente novamente.\n");
            opcao = -1;
            continue;
        }

        opcao = atoi(linha);

        switch (opcao) {
            case 1:
                if (fila) {
                    salvarFilaSimples(fila, nomeArquivoFila);
                    printf("Playlist simples da fila salva em: %s\n", nomeArquivoFila);
                } else {
                    printf("Fila vazia ou não inicializada.\n");
                }
                break;
            case 2:
                if (pilha) {
                    salvarPilhaSimples(pilha, nomeArquivoPilha);
                    printf("Playlist simples da pilha salva em: %s\n", nomeArquivoPilha);
                } else {
                    printf("Pilha vazia ou não inicializada.\n");
                }
                break;
            case 0:
                printf("Salvamento cancelado.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);
}


void exportarPlaylistCompleta(struct desc_fila *fila, struct desc_pilha *pilha) {
    int opcao;

    do {
        printf("\n=== EXPORTAR PLAYLIST ===\n");
        printf("1 - Exportar como Fila\n");
        printf("2 - Exportar como Pilha\n");
        printf("0 - Cancelar\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            // Caso entrada inválida, limpa buffer e repete
            while (getchar() != '\n');
            printf("Entrada inválida. Tente novamente.\n");
            opcao = -1; // força continuar loop
            continue;
        }
        getchar(); // Limpa o '\n' que sobra após scanf

        switch (opcao) {
            case 1:
                if (fila) {
                    exportarFilaCompleta(fila, "playlist_fila_completa.txt");
                    printf("Playlist da fila exportada para: playlist_fila_completa.txt\n");
                } else {
                    printf("Fila vazia ou não inicializada.\n");
                }
                break;
            case 2:
                if (pilha) {
                    exportarPilhaCompleta(pilha, "playlist_pilha_completa.txt");
                    printf("Playlist da pilha exportada para: playlist_pilha_completa.txt\n");
                } else {
                    printf("Pilha vazia ou não inicializada.\n");
                }
                break;
            case 0:
                printf("Exportação cancelada.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);
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
        // Parse da linha lida no formato correto
        if (sscanf(linha, "%255[^;];%d;%255[^;];%255[^;];%d",
                   temp.artista, &temp.codigo, temp.titulo, temp.letra, &temp.execucoes) == 5) {

            int encontrou = 0;

            switch (criterio) {
                case 1: // Por código
                    if (temp.codigo == valorInt)
                        encontrou = 1;
                    break;

                case 2: // Por artista
                    if (strcasecmp(temp.artista, valorStr) == 0)
                        encontrou = 1;
                    break;

                case 3: // Por título
                    if (strcasecmp(temp.titulo, valorStr) == 0)
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

void buscarMusica(const char *nomeArquivo, Musica *resultado, DescFila *fila, DescPilha *pilha) {
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
        if (scanf("%d", &bus) != 1) {
            while(getchar() != '\n'); // limpa buffer
            printf("Entrada inválida.\n");
            return;
        }
        getchar(); // limpa '\n'
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
            if (scanf("%d", &criterio) != 1) {
                while(getchar() != '\n');
                printf("Entrada inválida.\n");
                return;
            }
            getchar();

            switch (criterio) {
                case 0:
                    printf("Busca cancelada.\n");
                    break;

                case 1:
                    printf("Digite o código da música: ");
                    if (scanf("%d", &valorInt) != 1) {
                        while(getchar() != '\n');
                        printf("Entrada inválida.\n");
                        return;
                    }
                    getchar();
                    buscarMusicaPlaylistPorCodigo(fila, valorInt, resultado);
                    break;

                case 2:
                    printf("Digite o nome do artista: ");
                    if (!fgets(valorStr, sizeof(valorStr), stdin)) {
                        printf("Erro na leitura.\n");
                        return;
                    }
                    valorStr[strcspn(valorStr, "\n")] = 0;
                    buscarMusicaPlaylistPorArtista(fila, valorStr, resultado);
                    break;

                case 3:
                    printf("Digite o título da música: ");
                    if (!fgets(valorStr, sizeof(valorStr), stdin)) {
                        printf("Erro na leitura.\n");
                        return;
                    }
                    valorStr[strcspn(valorStr, "\n")] = 0;
                    buscarMusicaPlaylistPorTitulo(fila, valorStr, resultado);
                    break;

                default:
                    printf("Critério inválido.\n");
                    break;
            }
            break;

        case 2: {
            printf("\nVocê escolheu buscar no arquivo.\n");
            printf("1 - Buscar por código\n");
            printf("2 - Buscar por artista\n");
            printf("3 - Buscar por título\n");
            printf("0 - Sair\n");
            printf("Escolha o critério: ");
            if (scanf("%d", &criterio) != 1) {
                while(getchar() != '\n');
                printf("Entrada inválida.\n");
                return;
            }
            getchar();

            int achou = 0;

            switch (criterio) {
                case 0:
                    printf("Busca cancelada.\n");
                    break;

                case 1:
                    printf("Digite o código da música: ");
                    if (scanf("%d", &valorInt) != 1) {
                        while(getchar() != '\n');
                        printf("Entrada inválida.\n");
                        return;
                    }
                    getchar();
                    achou = buscarMusicaArquivo(nomeArquivo, resultado, 1, NULL, valorInt);
                    break;

                case 2:
                    printf("Digite o nome do artista: ");
                    if (!fgets(valorStr, sizeof(valorStr), stdin)) {
                        printf("Erro na leitura.\n");
                        return;
                    }
                    valorStr[strcspn(valorStr, "\n")] = 0;
                    achou = buscarMusicaArquivo(nomeArquivo, resultado, 2, valorStr, 0);
                    break;

                case 3:
                    printf("Digite o título da música: ");
                    if (!fgets(valorStr, sizeof(valorStr), stdin)) {
                        printf("Erro na leitura.\n");
                        return;
                    }
                    valorStr[strcspn(valorStr, "\n")] = 0;
                    achou = buscarMusicaArquivo(nomeArquivo, resultado, 3, valorStr, 0);
                    break;

                default:
                    printf("Critério inválido.\n");
                    break;
            }

            if (achou) {
                char resp;
                printf("Deseja adicionar essa música na playlist? (s/n): ");
                scanf(" %c", &resp);
                getchar(); // limpar '\n'

                if (resp == 's' || resp == 'S') {
                    // Criar uma cópia da música para inserir
                    Musica *musicaNova = malloc(sizeof(Musica));
                    if (!musicaNova) {
                        printf("Erro de alocação de memória.\n");
                        return;
                    }
                    *musicaNova = *resultado;

                    // Inserir na fila e pilha
                    inserirFila(fila, musicaNova);

                    NodoPilha *novoNodo = criaNodoPilha(musicaNova);
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
            break;
    }
}

void buscarEInserirMusica(const char *nomeArquivo, DescFila *fila, DescPilha *pilha) {
    int criterio;
    char valorStr[256];
    int valorInt;
    Musica resultado;

    printf("Buscar música para inserir:\n");
    printf("1 - Código\n");
    printf("2 - Artista\n");
    printf("3 - Título\n");
    printf("Escolha critério: ");
    if (scanf("%d", &criterio) != 1) {
        while(getchar() != '\n'); // limpa buffer
        printf("Entrada inválida.\n");
        return;
    }
    getchar();  // limpa '\n'

    int achou = 0;
    switch (criterio) {
        case 1:
            printf("Digite o código da música: ");
            if (scanf("%d", &valorInt) != 1) {
                while(getchar() != '\n');
                printf("Entrada inválida.\n");
                return;
            }
            getchar();
            achou = buscarMusicaArquivo(nomeArquivo, &resultado, 1, NULL, valorInt);
            break;

        case 2:
            printf("Digite o nome do artista: ");
            if (!fgets(valorStr, sizeof(valorStr), stdin)) {
                printf("Erro na leitura.\n");
                return;
            }
            valorStr[strcspn(valorStr, "\n")] = 0;
            achou = buscarMusicaArquivo(nomeArquivo, &resultado, 2, valorStr, 0);
            break;

        case 3:
            printf("Digite o título da música: ");
            if (!fgets(valorStr, sizeof(valorStr), stdin)) {
                printf("Erro na leitura.\n");
                return;
            }
            valorStr[strcspn(valorStr, "\n")] = 0;
            achou = buscarMusicaArquivo(nomeArquivo, &resultado, 3, valorStr, 0);
            break;

        default:
            printf("Critério inválido.\n");
            return;
    }

    if (achou) {
        // Criar cópia dinâmica da música para inserir
        Musica *musicaNova = malloc(sizeof(Musica));
        if (!musicaNova) {
            printf("Erro de alocação de memória.\n");
            return;
        }
        *musicaNova = resultado;

        // Inserir na fila e pilha
        inserirFila(fila, musicaNova);

        NodoPilha *novoNodo = criaNodoPilha(musicaNova);
        inserirPilha(pilha, novoNodo);

        printf("Música inserida com sucesso!\n");
    } else {
        printf("Música não encontrada no arquivo.\n");
    }
}






int main() {
    struct desc_fila *minhaFila = Createfila();
    struct desc_pilha *minhaPilha = criaDescPilha();
    char nomeArquivo[100];
    char confirma;
    int op;
    Musica *listaMusicas = malloc(sizeof(Musica) * 100);
    int totalMusicas = 0;

    if (!listaMusicas) {
        printf("Erro de alocação!\n");
        return 1;
    }
    
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
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1:
                printf("Digite o nome do arquivo: ");
                if (fgets(nomeArquivo, sizeof(nomeArquivo), stdin)) {
                    nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';
                }
                totalMusicas = carregarMusicas(nomeArquivo, listaMusicas);
                if (totalMusicas > 0) {
                    printf("Arquivo carregado com sucesso. %d músicas disponíveis.\n", totalMusicas);
                }
                break;
                
            case 2:                 

                // Verifica se já existe conteúdo na playlist
                if (minhaFila != NULL) {
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
                if (minhaFila == NULL) {
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
                if (minhaFila == NULL) {
                    printf("Crie uma playlist antes.\n");
                } else {
                     salvarPlaylistCompleta(minhaFila, minhaPilha, "playlist_fila.txt", "playlist_pilha.txt");
                }
                break;

            case 6:
                if (minhaFila == NULL) {
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

    } while (op != 0);
    free(listaMusicas);
    freePilha(minhaPilha);
    freeFila(minhaFila);
    return 0;
}
