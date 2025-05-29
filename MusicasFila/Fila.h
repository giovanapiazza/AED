#ifndef QUEUE_H
#define QUEUE_H

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
    struct nodo_queue *prox;   // Ponteiro para o próximo nodo
    struct musica *info;       // Ponteiro para a música armazenada
};

// Descritor da fila (mantém ponteiros para início e fim)
struct desc_queue {
    struct nodo_queue *head;   // Início da fila
    struct nodo_queue *tail;   // Fim da fila
    int tamanho;               // Tamanho atual da fila
};

// Funções da TAD de fila
struct desc_queue *CreateQueue();                  // Cria uma fila vazia
void DELETE(struct desc_queue *q);                 // Libera toda a memória da fila
int EMPTY(struct desc_queue *q);                   // Verifica se a fila está vazia
void ENQUEUE(struct desc_queue *q, struct musica *m); // Insere música no fim da fila
struct musica *DEQUEUE(struct desc_queue *q);      // Remove música do início da fila
int LENGTH(struct desc_queue *q);                  // Retorna o número de músicas na fila
void ShowQueue(struct desc_queue *q);              // Mostra todas as músicas da fila
struct musica *criarMusica();                      // Cria e retorna uma nova música

#endif

