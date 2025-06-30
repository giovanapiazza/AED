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
    if (!p) return NULL;
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

void destruirPilha(Pilha *p) {
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

// --- Geral ---
void inserir(Fila *fila, Pilha *pilha, const char *nomeArquivo) {
    int op;
    printf("Deseja buscar a música por:\n");
    printf("1 - Título\n");
    printf("2 - Código\n");
    printf("3 - Artista\n");
    printf("Opção: ");
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
            if (strcasecmp(temp.titulo, titulo) == 0) {
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
            if (strcasecmp(temp.artista, artista) == 0) {
                encontrado = 1;
                break;
            }
        }
    }

    fclose(fp);

    if (encontrado) {
        printf("\nMúsica encontrada:\n");
        imprimirMusica(&temp);

        // Verifica se já está na playlist
        NodoFila *aux = fila->inicio;
        while (aux != NULL) {
            if (strcasecmp(aux->info->titulo, temp.titulo) == 0) {
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
        } else {
            printf("Música não adicionada.\n");
        }
    } else {
        printf("Música não encontrada no arquivo.\n");
    }
}


void carregar(const char *nomeArquivo) {
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

void buscar(Fila *fila, Pilha *pilha) {
    int proc;
    printf("1- Procurar por nome\n");
    printf("2- Procurar por código\n");
    printf("3- Procurar por artista\n");
    scanf("%d", &proc);
    getchar();

    FILE *fp = fopen("musicas.txt", "r");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[512];
    int encontrado = 0;
    Musica temp;

    if (proc == 1) {
        char nome[256];
        printf("Digite o nome da música: ");
        fgets(nome, 256, stdin);
        nome[strcspn(nome, "\n")] = '\0';

        while (fgets(linha, sizeof(linha), fp)) {
            sscanf(linha, "%[^;];%[^;];%[^;];%d;%d",
                   temp.titulo, temp.artista, temp.letra, &temp.codigo, &temp.execucoes);
            if (strcasecmp(temp.titulo, nome) == 0) {
                encontrado = 1;
                break;
            }
        }
    } else if (proc == 2) {
        int codigo;
        printf("Digite o código da música: ");
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
    } else if (proc == 3) {
        char artista[256];
        printf("Digite o nome do artista: ");
        fgets(artista, 256, stdin);
        artista[strcspn(artista, "\n")] = '\0';

        while (fgets(linha, sizeof(linha), fp)) {
            sscanf(linha, "%[^;];%[^;];%[^;];%d;%d",
                   temp.titulo, temp.artista, temp.letra, &temp.codigo, &temp.execucoes);
            if (strcasecmp(temp.artista, artista) == 0) {
                encontrado = 1;
                break;
            }
        }
    }

    fclose(fp);

    if (encontrado) {
        printf("\nMúsica encontrada:\nTítulo: %s\nArtista: %s\nCódigo: %d\nExecuções: %d\n",
               temp.titulo, temp.artista, temp.codigo, temp.execucoes);

        // Verificar se já está na playlist
        int jaExiste = 0;
        NodoFila *aux = fila->inicio;
        while (aux != NULL) {
            if (strcasecmp(aux->info->titulo, temp.titulo) == 0) {
                jaExiste = 1;
                break;
            }
            aux = aux->prox;
        }

        if (!jaExiste) {
            printf("Deseja adicioná-la à playlist? (s/n): ");
            char r;
            scanf(" %c", &r);
            getchar();

            if (r == 's' || r == 'S') {
                Musica *nova = malloc(sizeof(Musica));
                if (nova) {
                    *nova = temp;
                    inserir(fila, pilha, nova);
                    printf("Música adicionada à playlist!\n");
                }
            } else {
                printf("Música não adicionada.\n");
            }
        } else {
            printf("A música já está na playlist.\n");
        }
    } else {
        printf("Música não encontrada.\n");
    }
}
