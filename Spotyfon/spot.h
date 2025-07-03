#ifndef SPOTYFON_H
#define SPOTYFON_H

typedef struct {
    char artista[256];
    int codigo;
    char titulo[256];
    char letra[256];
    int execucoes;
} Musica;

// Lista encadeada
typedef struct nodo {
    Musica musica;
    struct nodo *prox;
} Nodo;

typedef struct {
    Nodo *inicio;
    int tamanho;
} Lista;

void inicializarLista(Lista *lista);
void liberarLista(Lista *lista);
void carregarMusicas(const char *nomeArquivo, Lista *lista);
void imprimirMusica(const Musica *m);
int buscarMusicaLista(Lista *lista, Musica *resultado, int criterio, const char *valorStr, int valorInt);

// Pilha
typedef struct nodo_pilha {
    Musica musica;
    struct nodo_pilha *prox;
} NodoPilha;

typedef struct {
    NodoPilha *topo;
    int tamanho;
} Pilha;

void criarPilha(Pilha *p);
void push(Pilha *p, Musica m);
void imprimirPilha(Pilha *p);
void liberarPilha(Pilha *p);
int pilhaVazia(Pilha *p);

// Fila
typedef struct nodo_fila {
    Musica musica;
    struct nodo_fila *prox;
} NodoFila;

typedef struct {
    NodoFila *inicio, *fim;
    int tamanho;
} Fila;

void criarFila(Fila *f);
void enqueue(Fila *f, Musica m);
void imprimirFila(Fila *f);
void liberarFila(Fila *f);
int filaVazia(Fila *f);

// Operacoes principais
void buscarEInserirMusica(Lista *lista, Fila *fila, Pilha *pilha);
void salvarBackup(Fila *fila, const char *nomeback);
void imprimirTudo(Lista *lista, Fila *fila, Pilha *pilha);
void salvarRelatorio(const char *nomeRelatorio, Fila *fila, Lista *lista);
void carregarBackup(const char *nomeRelatorio, Fila *fila, Pilha *pilha);
void importacao(Lista *lista, Fila *fila, Pilha *pilha, int *carregouArquivo);
void criarPlaylist(Fila *fila, Pilha *pilha);

#endif
