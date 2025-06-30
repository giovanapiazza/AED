#ifndef SPOTYFON_H
#define SPOTYFON_H

typedef struct musica {
    char titulo[256];
    char artista[256];
    char letra[256];
    int codigo;
    int execucoes;
} Musica;

typedef struct nodo_pilha {
    Musica *info;
    struct nodo_pilha *prox;
} NodoPilha;

typedef struct {
    NodoPilha *topo;
    int tamanho;
} Pilha;

typedef struct nodo_fila {
    Musica *info;
    struct nodo_fila *prox;
} NodoFila;

typedef struct {
    NodoFila *inicio, *fim;
    int tamanho;
} Fila;

// Funções Musica
Musica *criarMusica();
void imprimirMusica(const Musica *m);

// Pilha
Pilha *criarPilha();
void destruirPilha(Pilha *p);
void inserirPilha(Pilha *p, Musica *m);
Musica *removerTopoPilha(Pilha *p);
Musica *topoPilha(const Pilha *p);
int pilhaVazia(const Pilha *p);

// Fila
Fila *criarFila();
void destruirFila(Fila *f);
void inserirFila(Fila *f, Musica *m);
Musica *removerInicioFila(Fila *f);
int filaVazia(const Fila *f);
void mostrarFila(const Fila *f);
Musica *buscarPorCodigo(const Fila *f, int codigo);

// Funções Gerais
void inserir(Fila *fila, Pilha *pilha, Musica *m);
void carregar(const char *nomeArquivo);
void buscar(Fila *fila, Pilha *pilha);

#endif

