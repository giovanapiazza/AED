// PROGRAMA UNIFICADO EM PORTUGUÊS: PILHA E FILA DE MÚSICAS COM SWITCH CASE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da música
struct musica {
    char titulo[256];
    char artista[256];
    char letra[256];
    int codigo;
    int execucoes;
};

// --------------------- PILHA ---------------------

struct nodo_pilha {
    struct musica *info;
    struct nodo_pilha *prox;
};

struct desc_pilha {
    struct nodo_pilha *topo;
    int tamanho;
};

struct desc_pilha *criarPilha() {
    struct desc_pilha *pilha = malloc(sizeof(struct desc_pilha));
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

void inserirPilha(struct desc_pilha *pilha, struct musica *m) {
    struct nodo_pilha *novo = malloc(sizeof(struct nodo_pilha));
    novo->info = m;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
}

struct musica *removerPilha(struct desc_pilha *pilha) {
    if (pilha->topo == NULL) return NULL;
    struct nodo_pilha *aux = pilha->topo;
    struct musica *m = aux->info;
    pilha->topo = aux->prox;
    free(aux);
    pilha->tamanho--;
    return m;
}

void mostrarPilha(struct desc_pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Pilha vazia.\n");
        return;
    }
    printf("\n--- Músicas na Pilha ---\n");
    struct nodo_pilha *aux = pilha->topo;
    while (aux) {
        printf("Título: %s\nArtista: %s\nLetra: %s\nCódigo: %d\nExecuções: %d\n-----------------------------\n",
               aux->info->titulo, aux->info->artista, aux->info->letra,
               aux->info->codigo, aux->info->execucoes);
        aux = aux->prox;
    }
}

// --------------------- FILA ---------------------

struct nodo_fila {
    struct musica *info;
    struct nodo_fila *prox;
};

struct desc_fila {
    struct nodo_fila *inicio, *fim;
    int tamanho;
};

struct desc_fila *criarFila() {
    struct desc_fila *fila = malloc(sizeof(struct desc_fila));
    fila->inicio = fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

void inserirFila(struct desc_fila *fila, struct musica *m) {
    struct nodo_fila *novo = malloc(sizeof(struct nodo_fila));
    novo->info = m;
    novo->prox = NULL;
    if (fila->fim)
        fila->fim->prox = novo;
    else
        fila->inicio = novo;
    fila->fim = novo;
    fila->tamanho++;
}

struct musica *removerFila(struct desc_fila *fila) {
    if (fila->inicio == NULL) return NULL;
    struct nodo_fila *remover = fila->inicio;
    struct musica *m = remover->info;
    fila->inicio = remover->prox;
    if (fila->inicio == NULL) fila->fim = NULL;
    free(remover);
    fila->tamanho--;
    return m;
}

void mostrarFila(struct desc_fila *fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia.\n");
        return;
    }
    printf("\n--- Músicas na Fila ---\n");
    struct nodo_fila *aux = fila->inicio;
    while (aux) {
        printf("Título: %s\nArtista: %s\nLetra: %s\nCódigo: %d\nExecuções: %d\n-----------------------------\n",
               aux->info->titulo, aux->info->artista, aux->info->letra,
               aux->info->codigo, aux->info->execucoes);
        aux = aux->prox;
    }
}

// --------------------- CRIA MÚSICA ---------------------

struct musica *criarMusica() {
    struct musica *m = malloc(sizeof(struct musica));
    printf("Título: "); fgets(m->titulo, 256, stdin); m->titulo[strcspn(m->titulo, "\n")] = '\0';
    printf("Artista: "); fgets(m->artista, 256, stdin); m->artista[strcspn(m->artista, "\n")] = '\0';
    printf("Letra: "); fgets(m->letra, 256, stdin); m->letra[strcspn(m->letra, "\n")] = '\0';
    printf("Código: "); scanf("%d", &m->codigo);
    printf("Execuções: "); scanf("%d", &m->execucoes);
    getchar();
    return m;
}

// --------------------- PROGRAMA PRINCIPAL ---------------------

int main() {
    struct desc_pilha *pilha = criarPilha();
    struct desc_fila *fila = criarFila();
    int op;

    do {
        printf("\n--- MENU ---\n");
        printf("1 - Inserir na pilha\n");
        printf("2 - Remover da pilha\n");
        printf("3 - Mostrar pilha\n");
        printf("4 - Inserir na fila\n");
        printf("5 - Remover da fila\n");
        printf("6 - Mostrar fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op); getchar();

        switch(op) {
            case 1:
                inserirPilha(pilha, criarMusica());
                break;
            case 2: {
                struct musica *m = removerPilha(pilha);
                if (m) { printf("Removida: %s\n", m->titulo); free(m); }
                else printf("Pilha vazia.\n");
                break;
            }
            case 3:
                mostrarPilha(pilha);
                break;
            case 4:
                inserirFila(fila, criarMusica());
                break;
            case 5: {
                struct musica *m = removerFila(fila);
                if (m) { printf("Removida: %s\n", m->titulo); free(m); }
                else printf("Fila vazia.\n");
                break;
            }
            case 6:
                mostrarFila(fila);
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (op != 0);

    return 0;
}
