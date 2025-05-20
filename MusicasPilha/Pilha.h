#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições das estruturas
struct musica {
    char titulo[256];
    char artista[256];
    char letra[256];
    int codigo;
    int execucoes;
};

struct nodo_pilha {
    struct nodo_pilha *prox;
    struct musica *info;
};

struct desc_pilha {
    struct nodo_pilha *topo;
    int tamanho;
};

struct desc_pilha *criaDescPilha(void);
struct musica *criarMusica();
struct nodo_pilha *criaNodoPilha(struct musica *m);
void inserir(struct desc_pilha *pilha, struct nodo_pilha *novoElemento);
struct nodo_pilha *remover(struct desc_pilha *pilha);
struct nodo_pilha *topo(struct desc_pilha *pilha);
int procurarLista(struct desc_pilha *pilha);
void imprimir(struct desc_pilha *pilha);
