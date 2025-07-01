#ifndef SPOTYFON_H
#define SPOTYFON_H

#include <stdio.h>

typedef struct {
    char artista[256];
    int codigo;
    char titulo[256];
    char letra[256];
    int execucoes;
} Musica;

// Funções gerais
int carregarMusicas(const char *nomeArquivo, Musica lista[], int max);
void imprimirMusica(Musica *m);

// Pilha
typedef struct nodoPilha {
    Musica *musica;
    struct nodoPilha *prox;
} NodoPilha;

typedef struct {
    NodoPilha *topo;
    int tamanho;
} DescPilha;

DescPilha *criaDescPilha(void);
NodoPilha *criaNodoPilha(Musica *m);
void inserirPilha(DescPilha *pilha, NodoPilha *novoElemento);
int existePilha(DescPilha *pilha);
int tamanhoPilha(DescPilha *pilha);
void imprimirPilha(DescPilha *pilha);
void salvarPilhaSimples(DescPilha *pilha, const char *nomeArquivo);
void exportarPilhaCompleta(DescPilha *pilha, const char *nomeArquivo);
void freePilha(DescPilha *pilha);

// Fila
typedef struct nodoFila {
    Musica *musica;
    struct nodoFila *prox;
} NodoFila;

typedef struct {
    NodoFila *inicio;
    NodoFila *fim;
    int tamanho;
} DescFila;

DescFila *createFila(void);
void inserirFila(DescFila *fila, Musica *m);
int existeFila(DescFila *fila);
int tamanhoFila(DescFila *fila);
void imprimirFila(DescFila *fila);
void salvarFilaSimples(DescFila *fila, const char *nomeArquivo);
void exportarFilaCompleta(DescFila *fila, const char *nomeArquivo);
void freeFila(DescFila *fila);

// Busca
int buscarMusicaArquivo(const char *nomeArquivo, Musica *resultado, int criterio, const char *valorStr, int valorInt);
int buscarMusicaPlaylistPorCodigo(DescFila *fila, int codigo, Musica *resultado);
int buscarMusicaPlaylistPorArtista(DescFila *fila, const char *artista, Musica *resultado);
int buscarMusicaPlaylistPorTitulo(DescFila *fila, const char *titulo, Musica *resultado);
void buscarMusica(const char *nomeArquivo, Musica *resultado, DescFila *fila, DescPilha *pilha);
void buscarEInserirMusica(const char *nomeArquivo, DescFila *fila, DescPilha *pilha);

// Salvar e exportar playlist
void salvarPlaylistSimples(DescFila *fila, DescPilha *pilha, const char *nomeArquivoFila, const char *nomeArquivoPilha);
void exportarPlaylistCompleta(DescFila *fila, DescPilha *pilha);

#endif
