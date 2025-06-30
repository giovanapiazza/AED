#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotyfon.h"

// --- Musica ---
Musica *criarMusica() {
    Musica *m = malloc(sizeof(Musica));
    if (!m) return NULL;

    printf("Título: "); fgets(m->titulo, 256, stdin); m->titulo[strcspn(m->titulo, "\n")] = '\0';
    printf("Artista: "); fgets(m->artista, 256, stdin); m->artista[strcspn(m->artista, "\n")] = '\0';
    printf("Letra: "); fgets(m->letra, 256, stdin); m->letra[strcspn(m->letra, "\n")] = '\0';
    printf("Código: "); scanf("%d", &m->codigo);
    printf("Execuções: "); scanf("%d", &m->execucoes);
    getchar();

    return m;
}

void imprimirMusica(const Musica *m) {
    if (!m) {
        printf("Música não encontrada.\n");
        return;
    }
    printf("\nTítulo: %s\nArtista: %s\nLetra: %s\nCódigo: %d\nExecuções: %d\n",
           m->titulo, m->artista, m->letra, m->codigo, m->execucoes);
}

// --- Pilha ---
Pilha *criarPilha() {
    Pilha *p = malloc(sizeof(Pilha));
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

void destruirPilha(Pilha *p) {
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
    NodoPilha *novo = malloc(sizeof(NodoPilha));
    novo->info = m;
    novo->prox = p->topo;
    p->topo = novo;
    p->tamanho++;
}

Musica *removerTopoPilha(Pilha *p) {
    if (p->topo == NULL) return NULL;
    NodoPilha *temp = p->topo;
    Musica *m = temp->info;
    p->topo = temp->prox;
    free(temp);
    p->tamanho--;
    return m;
}

Musica *topoPilha(const Pilha *p) {
    if (p->topo == NULL) return NULL;
    return p->topo->info;
}

int pilhaVazia(const Pilha *p) {
    return p->topo == NULL;
}

// --- Fila ---
Fila *criarFila() {
    Fila *f = malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    f->tamanho = 0;
    return f;
}

void destruirFila(Fila *f) {
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
    NodoFila *novo = malloc(sizeof(NodoFila));
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
    if (f->inicio == NULL) return NULL;
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
    return f->inicio == NULL;
}

void mostrarFila(const Fila *f) {
    if (filaVazia(f)) {
        printf("Playlist vazia.\n");
        return;
    }
    printf("\n--- Playlist ---\n");
    NodoFila *aux = f->inicio;
    while (aux) {
        printf("Título: %s | Artista: %s\n", aux->info->titulo, aux->info->artista);
        aux = aux->prox;
    }
}

Musica *buscarPorCodigo(const Fila *f, int codigo) {
    NodoFila *aux = f->inicio;
    while (aux) {
        if (aux->info->codigo == codigo)
            return aux->info;
        aux = aux->prox;
    }
    return NULL;
}

// --- Geral ---
void carregar(const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) {
        printf("Erro ao abrir o arquivo \"%s\"\n", nomeArquivo);
        return;
    }

    printf("\nMúsicas disponíveis no arquivo \"%s\":\n", nomeArquivo);
    char linha[512];
    while (fgets(linha, sizeof(linha), fp)) {
        printf("- %s", linha);
    }
    fclose(fp);
}

void inserir(Fila *fila, Pilha *pilha, const char *nomeArquivo) {
    int op;
    printf("Buscar música por:\n1 - Título\n2 - Código\n3 - Artista\nOpção: ");
    scanf("%d", &op);
    getchar();

    char linha[512];
    Musica temp;
    int encontrado = 0;

    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    if (op == 1) {
        char titulo[256];
        printf("Digite o título: ");
        fgets(titulo, 256, stdin);
        titulo[strcspn(titulo, "\n")] = '\0';

        while (fgets(linha, sizeof(linha), fp)) {
            sscanf(linha, "%[^;];%[^;];%[^;];%d;%d",
                   temp.titulo, temp.artista, temp.letra, &temp.codigo, &temp.execucoes);
            if (strcmp(temp.titulo, titulo) == 0) {
                encontrado = 1;
                break;
            }
        }
    } else if (op == 2) {
        int codigo;
        printf("Digite o código: ");
        scanf("%d", &codigo);
        getchar();

        while (fgets(linha, sizeof(linha), fp)) {
            sscanf(linha, "%[^;];%[^;];%[^;];%d;%d",
                   temp.titulo, temp.artista, temp.letra, &temp.codigo, &temp.execucoes);
            if (temp.codigo == codigo) {
                encontrado = 1;
                break;
            }
        }
    } else if (op == 3) {
        char artista[256];
        printf("Digite o nome do artista: ");
        fgets(artista, 256, stdin);
        artista[strcspn(artista, "\n")] = '\0';

        while (fgets(linha, sizeof(linha), fp)) {
            sscanf(linha, "%[^;];%[^;];%[^;];%d;%d",
                   temp.titulo, temp.artista, temp.letra, &temp.codigo, &temp.execucoes);
            if (strcmp(temp.artista, artista) == 0) {
                encontrado = 1;
                break;
            }
        }
    }

    fclose(fp);

    if (encontrado) {
        imprimirMusica(&temp);

        NodoFila *aux = fila->inicio;
        while (aux) {
            if (strcmp(aux->info->titulo, temp.titulo) == 0) {
                printf("Essa música já está na playlist.\n");
                return;
            }
            aux = aux->prox;
        }

        char r;
        printf("Deseja inserir na playlist? (s/n): ");
        scanf(" %c", &r);
        getchar();

        if (r == 's' || r == 'S') {
            Musica *nova = malloc(sizeof(Musica));
            *nova = temp;
            inserirPilha(pilha, nova);
            inserirFila(fila, nova);
            printf("Música adicionada à playlist com sucesso!\n");
        }
    } else {
        printf("Música não encontrada.\n");
    }
}

void buscar(Fila *fila, Pilha *pilha) {
    printf("Função de busca separada pode ser implementada ou reutilizar a inserir()\n");
}
