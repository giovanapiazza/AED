

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

// PILHA

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

void inserirPilha(struct desc_pilha *pilha, struct musica *m) { \\push
    struct nodo_pilha *novo = malloc(sizeof(struct nodo_pilha));
    novo->info = m;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
}

struct musica *removerPilha(struct desc_pilha *pilha) { \\pop
    if (pilha->topo == NULL) return NULL;
    struct nodo_pilha *aux = pilha->topo;
    struct musica *m = aux->info;
    pilha->topo = aux->prox;
    free(aux);
    pilha->tamanho--;
    return m;
}

void mostrarPilha(struct desc_pilha *pilha) { \\top
    if (pilha->topo == NULL) {
        printf("Pilha vazia.\n");
        return;
    }
    printf("\n--- Músicas na Pilha ---\n");
    struct nodo_pilha *aux = pilha->topo;
    while (aux) {
        printf("Título: %s\nArtista: %s\nLetra: %s\nCódigo: %d\nExecuções: %d\n",
               aux->info->titulo, aux->info->artista, aux->info->letra,
               aux->info->codigo, aux->info->execucoes);
        aux = aux->prox;
    }
}

int pilhaVazia(struct desc_pilha *pilha) { \\empty
    return pilha->topo == NULL;
}

int tamanhoPilha(struct desc_pilha *pilha) {
    return pilha->tamanho;
}

void liberarPilha(struct desc_pilha *pilha) {
    while (pilha->topo != NULL) {
        struct nodo_pilha *atual = pilha->topo;
        pilha->topo = atual->prox;
        free(atual->info);
        free(atual);
    }
    free(pilha);
}

//FILA

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

void inserirFila(struct desc_fila *fila, struct musica *m) { \\enqueue
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

struct musica *removerFila(struct desc_fila *fila) { \\dequeue
    if (fila->inicio == NULL) return NULL;
    struct nodo_fila *remover = fila->inicio;
    struct musica *m = remover->info;
    fila->inicio = remover->prox;
    if (fila->inicio == NULL) fila->fim = NULL;
    free(remover);
    fila->tamanho--;
    return m;
}

int filaVazia(struct desc_fila *fila) {
    return fila->inicio == NULL;
}

int tamanhoFila(struct desc_fila *fila) { \\length
    return fila->tamanho;
}

void liberarFila(struct desc_fila *fila) {
    while (fila->inicio != NULL) {
        struct nodo_fila *atual = fila->inicio;
        fila->inicio = atual->prox;
        free(atual->info);
        free(atual);
    }
    free(fila);
}

void mostrarFila(struct desc_fila *fila) { 
    if (fila->inicio == NULL) {
        printf("Fila vazia.\n");
        return;
    }
    printf("\n--- Músicas na Fila ---\n");
    struct nodo_fila *aux = fila->inicio;
    while (aux) {
        printf("Título: %s\nArtista: %s\nLetra: %s\nCódigo: %d\nExecuções: %d\n",
               aux->info->titulo, aux->info->artista, aux->info->letra,
               aux->info->codigo, aux->info->execucoes);
        aux = aux->prox;
    }
}

// CRIA MÚSICA 

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


int main() {
    struct desc_pilha *pilha = criarPilha();
    struct desc_fila *fila = criarFila();
    int op;

    do {
        printf("\n--- MENU ---\n");
        printf("1 - Inserir música (em ambos)\n");
        printf("2 - Remover música (de ambos)\n");
        printf("3 - Mostrar todas as músicas (pilha e fila)\n");
        printf("4 - Verificar se pilha ou fila estão vazias\n");
        printf("5 - Mostrar tamanhos da pilha e fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op); getchar();

        switch(op) {
            case 1: {
                struct musica *m1 = criarMusica();
                struct musica *m2 = malloc(sizeof(struct musica));
                *m2 = *m1;
                inserirPilha(pilha, m1);
                inserirFila(fila, m2);
                printf("Música inserida na pilha e na fila.\n");
                break;
            }
            case 2: {
                struct musica *mPilha = removerPilha(pilha);
                struct musica *mFila = removerFila(fila);
                if (mPilha) { printf("Removida da pilha: %s\n", mPilha->titulo); free(mPilha); }
                else printf("Pilha vazia.\n");
                if (mFila) { printf("Removida da fila: %s\n", mFila->titulo); free(mFila); }
                else printf("Fila vazia.\n");
                break;
            }
            case 3:
                printf("\n--- PILHA ---\n");
                mostrarPilha(pilha);
                printf("\n--- FILA ---\n");
                mostrarFila(fila);
                break;
            case 4:
                printf("Pilha: %s\n", pilhaVazia(pilha) ? "Vazia" : "Com elementos");
                printf("Fila: %s\n", filaVazia(fila) ? "Vazia" : "Com elementos");
                break;
            case 5:
                printf("Tamanho da pilha: %d\n", tamanhoPilha(pilha));
                printf("Tamanho da fila: %d\n", tamanhoFila(fila));
                break;
            case 0:
                liberarFila(fila);
                liberarPilha(pilha);
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (op != 0);

    return 0;
}
