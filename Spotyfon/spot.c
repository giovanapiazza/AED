#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotyfon.h"

// --- Pilha ---
Pilha *criarPilha() {
    Pilha *p = malloc(sizeof(Pilha));
    if (!p) return NULL;
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

void freePilha(Pilha *p) {
    if (!p) return;
    NodoPilha *aux = p->topo;
    while (aux) {
        NodoPilha *temp = aux;
        aux = aux->prox;
        free(temp->info);
        free(temp);
    }
    free(p);
}

void inserirPilha(Pilha *p, Musica *m) {
    if (!p || !m) return;
    NodoPilha *novo = malloc(sizeof(NodoPilha));
    if (!novo) return;
    novo->info = m;
    novo->prox = p->topo;
    p->topo = novo;
    p->tamanho++;
}


int pilhaVazia(const Pilha *p) {
    return (p == NULL || p->topo == NULL);
}
void mostrarPilha(const Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia.\n");
        return;
    }

    printf("\n--- Músicas na Pilha ---\n");
    NodoPilha *aux = p->topo;
    while (aux) {
        printf("Título: %s\nArtista: %s\n", aux->info->titulo, aux->info->artista);
        aux = aux->prox;
    }
}


// --- Fila ----------------------------------------------------------------------------------------------------------------------
Fila *criarFila() {
    Fila *f = malloc(sizeof(Fila));
    if (!f) return NULL;
    f->inicio = f->fim = NULL;
    f->tamanho = 0;
    return f;
}

void freeFila(Fila *f) {
    if (!f) return;
    NodoFila *aux = f->inicio;
    while (aux) {
        NodoFila *temp = aux;
        aux = aux->prox;
        free(temp->info);
        free(temp);
    }
    free(f);
}

void inserirFila(Fila *f, Musica *m) {
    if (!f || !m) return;
    NodoFila *novo = malloc(sizeof(NodoFila));
    if (!novo) return;
    novo->info = m;
    novo->prox = NULL;

    if (f->fim)
        f->fim->prox = novo;
    else
        f->inicio = novo;

    f->fim = novo;
    f->tamanho++;
}

int filaVazia(const Fila *f) {
    return (f == NULL || f->inicio == NULL);
}

void mostrarFila(const Fila *f) {
    if (filaVazia(f)) {
        printf("Playlist vazia.\n");
        return;
    }
    printf("\n--- Músicas na Playlist ---\n");
    NodoFila *aux = f->inicio;
    while (aux) {
        printf("Título: %s\nArtista: %s\n", aux->info->titulo, aux->info->artista);
        aux = aux->prox;
    }
}



// --- Função auxiliar para ler música do arquivo por critério ---
void imprimirMusica(const Musica *m) {
    if (!m) return;
    printf("\n--- Dados da Música ---\n");
    printf("Título: %s\n", m->titulo);
    printf("Artista: %s\n", m->artista);
    printf("Letra: %s\n", m->letra);
    printf("Código: %d\n", m->codigo);
    printf("Execuções: %d\n", m->execucoes);
}
int lerMusicaDoArquivo(FILE *fp, Musica *temp) {
    char linha[512];
    while (fgets(linha, sizeof(linha), fp)) {
        if (sscanf(linha, "%255[^;];%255[^;];%255[^;];%d;%d",
                   temp->titulo, temp->artista, temp->letra,
                   &temp->codigo, &temp->execucoes) == 5) {
            return 1; // Sucesso
        }
    }
    return 0; // Falha ou fim do arquivo
}

// --- Busca música no arquivo pelo critério e valor, retorna 1 se encontrado ---
int buscarMusicaArquivo(const char *nomeArquivo, Musica *resultado, int criterio, const char *valorStr, int valorInt) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }

    char linha[512];
    while (fgets(linha, sizeof(linha), fp)) {
        Musica temp;

        if (sscanf(linha, "%255[^;];%255[^;];%255[^;];%d;%d",
                   temp.titulo, temp.artista, temp.letra,
                   &temp.codigo, &temp.execucoes) == 5) {

            int achou = 0;

            switch (criterio) {
                case 1: // título
                    if (strcasecmp(temp.titulo, valorStr) == 0) {
                        achou = 1;
                    }
                    break;
                case 2: // código
                    if (temp.codigo == valorInt) {
                        achou = 1;
                    }
                    break;
                case 3: // artista
                    if (strcasecmp(temp.artista, valorStr) == 0) {
                        achou = 1;
                    }
                    break;
                default:
                    achou = 0;
            }

            if (achou) {
                *resultado = temp;

                // Mostra todos os dados da música encontrada
                imprimirMusica(resultado);

                fclose(fp);
                return 1;
            }
        }
    }

    fclose(fp);
    return 0;
}


// --- Função para inserir música na playlist com busca ---
void inserirMusicaNaPlaylist(Fila *fila, Pilha *pilha, const char *nomeArquivo) {
    int opcao;
    char valorStr[256];
    int valorInt = 0;
    Musica musicaEncontrada;

    printf("Deseja buscar a música por:\n");
    printf("1 - Título\n");
    printf("2 - Código\n");
    printf("3 - Artista\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar(); // Limpa o \n deixado pelo scanf

    switch (opcao) {
        case 1:
            printf("Digite o título: ");
            fgets(valorStr, sizeof(valorStr), stdin);
            valorStr[strcspn(valorStr, "\n")] = '\0';
            break;

        case 2:
            printf("Digite o código: ");
            scanf("%d", &valorInt);
            getchar(); // limpa buffer
            break;

        case 3:
            printf("Digite o nome do artista: ");
            fgets(valorStr, sizeof(valorStr), stdin);
            valorStr[strcspn(valorStr, "\n")] = '\0';
            break;

        default:
            printf("Opção inválida!\n");
            return;
    }

    // Busca no arquivo
    if (!buscarMusicaArquivo(nomeArquivo, &musicaEncontrada, opcao, valorStr, valorInt)) {
        printf("Música não encontrada no arquivo.\n");
        return;
    }

    printf("\n Música encontrada:\n");
    imprimirMusica(&musicaEncontrada);

    // Verifica duplicata na playlist
    NodoFila *aux = fila->inicio;
    while (aux) {
        if (strcasecmp(aux->info->titulo, musicaEncontrada.titulo) == 0) {
            printf("Essa música já está na playlist.\n");
            return;
        }
        aux = aux->prox;
    }

    // Confirmação do usuário
    char resposta;
    printf("Deseja inserir na playlist? (s/n): ");
    scanf(" %c", &resposta);
    getchar();

    if (resposta == 's' || resposta == 'S') {
        Musica *nova = malloc(sizeof(Musica));
        if (!nova) {
            printf("Erro ao alocar memória para a música.\n");
            return;
        }
        *nova = musicaEncontrada;
        inserirPilha(pilha, nova);
        inserirFila(fila, nova);
        printf("✅ Música adicionada à playlist com sucesso!\n");
    } else {
        printf("Música não adicionada.\n");
    }
}


// --- Função para mostrar todas músicas do arquivo ---
void mostrarMusicasArquivo(const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    printf("\nMúsicas disponíveis no arquivo:\n");
    char linha[512];
    while (fgets(linha, sizeof(linha), fp)) {
        printf("- %s", linha);
    }
    fclose(fp);
}


// fuções unidas
void mostra(Pilha *p, Fila *f) {
    char resp;
    printf("Deseja imprimir no modo Fila (s/n): ");
    scanf(" %c", &resp); // espaço antes do %c para ignorar '\n'
    getchar();

    if (resp == 's' || resp == 'S') {
        mostrarFila(f);
    } else {
        mostrarPilha(p);
    }
}

void criarPlaylist(Pilha **p, Fila **f) {
    *p = criarPilha();
    *f = criarFila();

    if (!(*p) || !(*f)) {
        printf("Erro ao criar a playlist.\n");
        if (*p) freePilha(*p);
        if (*f) freeFila(*f);
        *p = NULL;
        *f = NULL;
    } else {
        printf("Playlist criada com sucesso!\n");
    }
}
