#ifndef GRAFOS_H
#define GRAFOS_H

typedef struct Aresta {
    int partida;
    int chegada;
    int peso;
    struct Aresta *prox;
} Aresta;

typedef struct Nodo {
    int chave;
    Aresta *adjacencias;
    struct Nodo *prox;
} Nodo;

typedef struct Grafo {
    int max_vertices;
    int max_arestas;
    Nodo *nodos;
} Grafo;

typedef struct NodoPilha {
    Aresta *arestaPilha;
    struct NodoPilha *prox;
} NodoPilha;

typedef struct {
    NodoPilha *topo;
    int tamanho;
} Pilha;

Grafo *inicializaGrafo(int tamanho);
Grafo *insereAresta(Grafo *grafo, int saida, int chegada, int peso);
Nodo *buscaVertice(Grafo *grafo, int chave);
Grafo *parser(char *nomeArquivo);
void imprimeGrafoDe(Nodo *inicio);

Pilha *criaPilha();
NodoPilha *criaNodoPilha(Aresta *a);
void push(Pilha *pilha, NodoPilha *nodo);
NodoPilha *pop(Pilha *pilha);
void showPilha(Pilha *pilha);

#endif
