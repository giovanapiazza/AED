#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a estrutura de música
struct musica {
    char titulo[256];
    char artista[256];
    char letra[256];
    int codigo;
    int execucoes;
};

// Define o nodo da pilha
struct nodo_pilha {
    struct musica *info;
    struct nodo_pilha *prox;
};

// Define o descritor da pilha
struct desc_pilha {
    struct nodo_pilha *topo;
    int tamanho;
};

// Protótipos
struct desc_pilha *criaDescPilha();
struct musica *criarMusica();
struct nodo_pilha *criaNodoPilha(struct musica *m);
void inserir(struct desc_pilha *pilha, struct nodo_pilha *novoElemento);
struct nodo_pilha *remover(struct desc_pilha *pilha);
struct nodo_pilha *topo(struct desc_pilha *pilha);
int procurarLista(struct desc_pilha *pilha);
void imprimir(struct desc_pilha *pilha);

#endif
