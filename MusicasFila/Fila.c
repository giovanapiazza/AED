#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"

// Cria e retorna uma fila vazia
struct desc_queue *CreateQueue() {
    struct desc_queue *q = malloc(sizeof(struct desc_queue));
    q->head = q->tail = NULL;
    q->tamanho = 0;
    return q;
}

// Libera toda a memória da fila e de suas músicas
void DELETE(struct desc_queue *q) {
    while (!EMPTY(q)) {
        struct musica *m = DEQUEUE(q); // Remove elemento
        free(m);                        // Libera música
    }
    free(q); // Libera descritor
}

// Verifica se a fila está vazia (retorna 1 se sim, 0 se não)
int EMPTY(struct desc_queue *q) {
    return (q->head == NULL);
}

// Insere uma nova música no fim da fila
void ENQUEUE(struct desc_queue *q, struct musica *m) {
    struct nodo_queue *novo = malloc(sizeof(struct nodo_queue));
    novo->info = m;
    novo->prox = NULL;

    if (q->tail) 
        q->tail->prox = novo; // Liga o último ao novo
    else 
        q->head = novo;       // Se a fila estava vazia, novo também é o head

    q->tail = novo;           // Atualiza o tail
    q->tamanho++;             // Incrementa o tamanho
}

// Remove a música do início da fila
struct musica *DEQUEUE(struct desc_queue *q) {
    if (EMPTY(q)) return NULL;

    struct nodo_queue *remover = q->head;
    struct musica *m = remover->info;
    q->head = remover->prox;

    if (q->head == NULL) // Se ficou vazio, atualiza tail
        q->tail = NULL;

    free(remover);       // Libera o nodo removido
    q->tamanho--;        // Decrementa tamanho
    return m;            // Retorna a música removida
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
    getchar(); // Consome o '\n' final

    return m;
}

