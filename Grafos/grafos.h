#ifndef GRAFOS_H
#define GRAFOS_H
typedef struct aresta {
    int partida, chegada, peso;
    struct aresta *prox;
} Aresta;

typedef struct nodo {
    int chave;
    Aresta *adjacencias;
    struct nodo *prox;
} Nodo;

typedef struct {
    int max_vertices;
    int max_arestas;
    Nodo *nodos;
} Grafo;

typedef struct nodo_fila {
    Aresta *arestaFila;
    struct nodo_fila *prox;
} NodoFila;

typedef struct {
    NodoFila *inicio;
    NodoFila *fim;
    int tamanho;
} Fila;

Grafo *inicializaGrafo(int tamanho);
Grafo *parser(char *nomeArquivo);
Grafo *insereAresta(Grafo *grafo, int saida, int chegada, int peso);
Nodo *buscaVertice(Grafo *grafo, int chave);
void imprimeGrafo(Grafo *grafo);
Fila *criaFila();
NodoFila *criaNodoFila(Aresta *a);
void enqueue(Fila *fila, NodoFila *nodo);
void showFila(Fila *fila);

#endif
