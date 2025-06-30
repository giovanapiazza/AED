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

void liberaPilha(Pilha *p) {
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

Musica *removerTopoPilha(Pilha *p) {
    if (!p || p->topo == NULL) return NULL;
    NodoPilha *temp = p->topo;
    Musica *m = temp->info;
    p->topo = temp->prox;
    free(temp);
    p->tamanho--;
    return m;
}

Musica *topoPilha(const Pilha *p) {
    if (!p || p->topo == NULL) return NULL;
    return p->topo->info;
}

int pilhaVazia(const Pilha *p) {
    return (p == NULL || p->topo == NULL);
}

// --- Fila ---
Fila *criarFila() {
    Fila *f = malloc(sizeof(Fila));
    if (!f) return NULL;
    f->inicio = f->fim = NULL;
    f->tamanho = 0;
    return f;
}

void destruirFila(Fila *f) {
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

Musica *removerInicioFila(Fila *f) {
    if (!f || f->inicio == NULL) return NULL;
    NodoFila *temp = f->inicio;
    Musica *m = temp->info;
    f->inicio = temp->prox;
    if (f->inicio == NULL)
        f->fim = NULL;
    free(temp);
    f->tamanho--;
    return m;
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

Musica *buscarPorCodigo(const Fila *f, int codigo) {
    if (!f) return NULL;
    NodoFila *aux = f->inicio;
    while (aux) {
        if (aux->info->codigo == codigo) {
            return aux->info;
        }
        aux = aux->prox;
    }
    return NULL;
}

// --- Função auxiliar para ler música do arquivo por critério ---
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
                case 1: // Título
                    if (strcasecmp(temp.titulo, valorStr) == 0) achou = 1;
                    break;
                case 2: // Código
                    if (temp.codigo == valorInt) achou = 1;
                    break;
                case 3: // Artista
                    if (strcasecmp(temp.artista, valorStr) == 0) achou = 1;
                    break;
            }
            if (achou) {
                *resultado = temp;
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
    printf("Deseja buscar a música por:\n");
    printf("1 - Título\n");
    printf("2 - Código\n");
    printf("3 - Artista\n");
    printf("Opção: ");
    while (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 3) {
        printf("Opção inválida. Digite 1, 2 ou 3: ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n'); // limpa buffer

    char valorStr[256];
    int valorInt = 0;
    Musica musicaEncontrada;

    if (opcao == 1) {
        printf("Digite o título: ");
        fgets(valorStr, sizeof(valorStr), stdin);
        valorStr[strcspn(valorStr, "\n")] = '\0';
    } else if (opcao == 2) {
        printf("Digite o código: ");
        while (scanf("%d", &valorInt) != 1) {
            printf("Entrada inválida. Digite um número para o código: ");
            while(getchar() != '\n');
        }
        while(getchar() != '\n');
    } else {
        printf("Digite o nome do artista: ");
        fgets(valorStr, sizeof(valorStr), stdin);
        valorStr[strcspn(valorStr, "\n")] = '\0';
    }

    if (!buscarMusicaArquivo(nomeArquivo, &musicaEncontrada, opcao, valorStr, valorInt)) {
        printf("Música não encontrada no arquivo.\n");
        return;
    }

    printf("\nMúsica encontrada:\n");
    imprimirMusica(&musicaEncontrada);

    // Verifica se já está na playlist
    NodoFila *aux = fila->inicio;
    while (aux != NULL) {
        if (strcasecmp(aux->info->titulo, musicaEncontrada.titulo) == 0) {
            printf("Essa música já está na playlist.\n");
            return;
        }
        aux = aux->prox;
    }

    char resposta;
    printf("Deseja inserir na playlist? (s/n): ");
    scanf(" %c", &resposta);
    while(getchar() != '\n');

    if (resposta == 's' || resposta == 'S') {
        Musica *nova = malloc(sizeof(Musica));
        if (!nova) {
            printf("Erro ao alocar memória para a música.\n");
            return;
        }
        *nova = musicaEncontrada;
        inserirPilha(pilha, nova);
        inserirFila(fila, nova);
        printf("Música adicionada à playlist com sucesso!\n");
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
