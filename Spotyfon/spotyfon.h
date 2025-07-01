#ifndef SPOTYFON_H
#define SPOTYFON_H

// Definição da struct Musica
typedef struct musica {
    char titulo[256];
    char artista[256];
    char letra[256];
    int codigo;
    int execucoes;
} Musica;

// Pilha
struct nodo_pilha {
    Musica *info;
    struct nodo_pilha *prox;
};

struct desc_pilha {
    struct nodo_pilha *topo;
    int tamanho;
};

// Fila
struct nodo_fila {
    Musica *info;
    struct nodo_fila *prox;
};
struct desc_fila {
    struct nodo_fila *head;
    struct nodo_fila *tail;
    int tamanho;
};


// Ffunções da pilha
struct desc_pilha *criaDescPilha(void);
struct nodo_pilha *criaNodoPilha(Musica *m);
void inserirPilha(struct desc_pilha *pilha, struct nodo_pilha *novoElemento);
int existePilha(struct desc_pilha *pilha);
int tamanhoPilha(struct desc_pilha *pilha);
void imprimirPilha(struct desc_pilha *pilha);
void salvarPilhaSimples(struct desc_pilha *pilha, const char *nomeArquivo);
void exportarPilhaCompleta(struct desc_pilha *pilha, const char *nomeArquivo);
void freePilha(struct desc_pilha *pilha);

// Funções da fila
struct desc_fila *Createfila(void);
void liberarFila(struct desc_fila *fila);
void inserirFila(struct desc_fila *fila, Musica *m);
int existeFila(struct desc_fila *fila);
int tamanhoFila(struct desc_fila *fila);
void imprimirFila(struct desc_fila *fila);
void salvarFilaSimples(struct desc_fila *fila, const char *nomeArquivo);
void exportarFilaCompleta(struct desc_fila *fila, const char *nomeArquivo);
void freeFila(struct desc_fila *fila);

// Funções gerais e utilitárias
void carregar(const char *nomeArquivo, struct desc_fila *fila);
void lerArquivo(const char *nomeArquivo);
void imprimir(struct desc_fila *fila, struct desc_pilha *pilha);
void buscarEInserirMusica(const char *nomeArquivo, struct desc_fila *fila, struct desc_pilha *pilha);
void buscarMusica(const char *nomeArquivo, Musica *resultado, struct desc_fila *fila, struct desc_pilha *pilha);
void buscarMusicaPlaylistPorTitulo(const char *titulo, Musica *resultado);
void buscarMusicaPlaylistPorArtista(const char *artista, Musica *resultado);
void buscarMusicaPlaylistPorCodigo(int codigo, Musica *resultado);
int buscarMusicaArquivo(const char *nomeArquivo, Musica *resultado, int criterio, const char *valorStr, int valorInt);
void salvarPlaylistCompleta(struct desc_fila *fila, struct desc_pilha *pilha, const char *nomeArquivoFila, const char *nomeArquivoPilha);
void exportarPlaylistCompleta(struct desc_fila *fila, struct desc_pilha *pilha);

#endif 
