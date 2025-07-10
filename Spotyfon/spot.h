// spot.h
#ifndef SPOT_H
#define SPOT_H

//---------------- STRUCTS ----------------//
typedef struct {
    char artista[256];
    int codigo;
    char titulo[256];
    char letra[256];
    int execucoes;
} Musica;

typedef struct nodo {
    Musica musica;
    struct nodo *prox;
} Nodo;

typedef struct {
    Nodo *inicio;
    int tamanho;
} Lista;

typedef struct nodo_pilha {
    Musica musica;
    struct nodo_pilha *prox;
} NodoPilha;

typedef struct {
    NodoPilha *topo;
    int tamanho;
} Pilha;

typedef struct nodo_fila {
    Musica musica;
    struct nodo_fila *prox;
} NodoFila;

typedef struct {
    NodoFila *inicio, *fim;
    int tamanho;
} Fila;

//---------------- FUNÇÕES LISTA ----------------//
void inicializarLista(Lista *lista);
void inserirMusicaFim(Lista *lista, Musica m);
void liberarLista(Lista *lista);
void carregarMusicas(const char *nomeArquivo, Lista *lista);
void imprimirMusica(const Musica *m);

//---------------- FUNÇÕES PILHA ----------------//
void criarPilha(Pilha *p);
void push(Pilha *p, Musica m);
void imprimirPilha(Pilha *p);
void liberarPilha(Pilha *p);
int pilhaVazia(Pilha *p);

//---------------- FUNÇÕES FILA ----------------//
void criarFila(Fila *f);
void enqueue(Fila *f, Musica m);
void imprimirFila(Fila *f);
void liberarFila(Fila *f);
int filaVazia(Fila *f);

//---------------- BUSCAS E OPERAÇÕES ----------------//
int buscarMusicaLista(Lista *lista, Musica *resultado, int criterio, const char *valorStr, int valorInt);
void buscarEInserirMusica(Lista *lista, Fila *fila, Pilha *pilha);
void executarPlaylist(Fila *fila, Pilha *pilha);
void salvarPlaylist(Fila *fila, const char *nomeplay);
void imprimirTudo(Lista *lista, Fila *fila, Pilha *pilha);
void salvarBackup(const char *nomeArquivo, Lista *lista);
void carregarBackup(const char *nomeArquivo, Fila *fila, Pilha *pilha);
void importacao(Lista *lista, Fila *fila, Pilha *pilha, int *carregouArquivo, char *nomeArquivo);
void criarPlaylist(Fila *fila, Pilha *pilha);
void salvarRelatorio(const char *nomeRelatorio, Fila *fila, Lista *lista, const char *nomeArquivoAcervo);
void backup(const char *nomeArquivo, Lista *lista, Fila *fila, int carregouArquivo);

#endif
