#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma música
struct musica {
    char titulo[256];
    char artista[256];
    char letra[256];
    int codigo;
    int execucoes;
};

// Nodo da fila (um elemento da fila)
struct nodo_queue {
    struct nodo_queue *prox;
    struct musica *info;
};

// Descritor da fila (mantém ponteiros para início e fim)
struct desc_queue {
    struct nodo_queue *head;
    struct nodo_queue *tail;
    int tamanho;
};

// Cria e retorna uma fila vazia
struct desc_queue *CreateQueue() {
    struct desc_queue *q = malloc(sizeof(struct desc_queue));
    q->head = q->tail = NULL;
    q->tamanho = 0;
    return q;
}

// Libera toda a memória da fila e de suas músicas
void DELETE(struct desc_queue *q) {
    while (q->head != NULL) {
        struct nodo_queue *remover = q->head;
        struct musica *m = remover->info;
        q->head = remover->prox;
        free(m);
        free(remover);
    }
    free(q);
}

// Verifica se a fila está vazia
int EMPTY(struct desc_queue *q) {
    return (q->head == NULL);
}

// Insere uma nova música no fim da fila
void ENQUEUE(struct desc_queue *q, struct musica *m) {
    struct nodo_queue *novo = malloc(sizeof(struct nodo_queue));
    novo->info = m;
    novo->prox = NULL;

    if (q->tail)
        q->tail->prox = novo;
    else
        q->head = novo;

    q->tail = novo;
    q->tamanho++;
}

// Remove a música do início da fila
struct musica *DEQUEUE(struct desc_queue *q) {
    if (EMPTY(q)) return NULL;

    struct nodo_queue *remover = q->head;
    struct musica *m = remover->info;
    q->head = remover->prox;

    if (q->head == NULL)
        q->tail = NULL;

    free(remover);
    q->tamanho--;
    return m;
}

// Retorna o número de músicas na fila
int LENGTH(struct desc_queue *q) {
    return q->tamanho;
}

// Exibe todas as músicas da fila
void ShowQueue(struct desc_queue *q) {
    if (EMPTY(q)) {
        printf("Fila vazia.\n");
        return;
    }

    struct nodo_queue *aux = q->head;
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

// Cria uma nova música com dados do usuário
struct musica *criarMusica() {
    struct musica *m = malloc(sizeof(struct musica));

    printf("Título: ");
    fgets(m->titulo, 256, stdin);
    m->titulo[strcspn(m->titulo, "\n")] = '\0';

    printf("Artista: ");
    fgets(m->artista, 256, stdin);
    m->artista[strcspn(m->artista, "\n")] = '\0';

    printf("Letra: ");
    fgets(m->letra, 256, stdin);
    m->letra[strcspn(m->letra, "\n")] = '\0';

    printf("Código: ");
    scanf("%d", &m->codigo);

    printf("Execuções: ");
    scanf("%d", &m->execucoes);
    getchar(); // Limpa o '\n'

    return m;
}

int main() {
    struct desc_queue *fila = CreateQueue();
    int op;

    do {
        printf("\n--- MENU ---\n");
        printf("1 - ENQUEUE (inserir música)\n");
        printf("2 - DEQUEUE (remover da frente)\n");
        printf("3 - EMPTY (verificar se fila está vazia)\n");
        printf("4 - LENGTH (quantidade de músicas)\n");
        printf("5 - ShowQueue (exibir músicas)\n");
        printf("6 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar(); // Limpa o buffer

        switch (op) {
            case 1: {
                struct musica *m = criarMusica();
                ENQUEUE(fila, m);
                printf("Música adicionada à fila!\n");
                break;
            }
            case 2: {
                struct musica *removida = DEQUEUE(fila);
                if (removida) {
                    printf("Removida: %s\n", removida->titulo);
                    free(removida);
                } else {
                    printf("Fila vazia.\n");
                }
                break;
            }
            case 3:
                if (EMPTY(fila))
                    printf("A fila está vazia.\n");
                else
                    printf("A fila tem elementos.\n");
                break;
            case 4:
                printf("Tamanho da fila: %d\n", LENGTH(fila));
                break;
            case 5:
                ShowQueue(fila);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (op != 6);

    DELETE(fila);
    return 0;
}
