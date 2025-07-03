#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"

// ---------------- GRAFO ----------------
Grafo *inicializaGrafo(int tamanho) {
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->max_vertices = tamanho;
    grafo->max_arestas = 0;
    grafo->nodos = NULL;

    for (int i = 0; i < tamanho; i++) {
        Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
        novo->chave = i + 1;
        novo->adjacencias = NULL;
        novo->prox = NULL;

        if (grafo->nodos == NULL) {
            grafo->nodos = novo;
        } else {
            Nodo *temp = grafo->nodos;
            while (temp->prox != NULL)
                temp = temp->prox;
            temp->prox = novo;
        }
    }

    return grafo;
}

Nodo *buscaVertice(Grafo *grafo, int chave) {
    Nodo *atual = grafo->nodos;
    while (atual != NULL) {
        if (atual->chave == chave)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

Grafo *insereAresta(Grafo *grafo, int saida, int chegada, int peso) {
    Nodo *nodo = buscaVertice(grafo, saida);
    if (nodo == NULL) return grafo;

    Aresta *nova = (Aresta *)malloc(sizeof(Aresta));
    nova->partida = saida;
    nova->chegada = chegada;
    nova->peso = peso;
    nova->prox = NULL;

    if (nodo->adjacencias == NULL)
        nodo->adjacencias = nova;
    else {
        Aresta *temp = nodo->adjacencias;
        while (temp->prox != NULL)
            temp = temp->prox;
        temp->prox = nova;
    }

    grafo->max_arestas++;
    return grafo;
}

Grafo *parser(char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        return NULL;
    }

    int total;
    fscanf(file, "%d", &total);
    Grafo *grafo = inicializaGrafo(total);

    char linha[500];
    char caractere;
    int n = 0;

    while ((caractere = fgetc(file)) != EOF) {
        if (caractere != '\n') {
            linha[n++] = caractere;
        } else {
            linha[n] = '\0';
            if (n > 0) {
                int partida = atoi(strtok(linha, " "));
                int chegada = atoi(strtok(NULL, " "));
                int peso = atoi(strtok(NULL, " "));
                grafo = insereAresta(grafo, partida, chegada, peso);
            }
            n = 0;
        }
    }

    fclose(file);
    return grafo;
}

void imprimeGrafo(Grafo *grafo) {
    printf("Grafos em lista\n");
    Nodo *nodo = grafo->nodos;
    while (nodo != NULL) {
        printf("Nodo %d - ", nodo->chave);
        Aresta *adj = nodo->adjacencias;
        while (adj != NULL) {
            printf("[ ->%d (peso %d) ] ", adj->chegada, adj->peso);
            adj = adj->prox;
        }
        nodo = nodo->prox;
    }
}

// ---------------- FILA ----------------
Fila *criaFila() {
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

NodoFila *criaNodoFila(Aresta *a) {
    NodoFila *novo = (NodoFila *)malloc(sizeof(NodoFila));
    novo->arestaFila = a;
    novo->prox = NULL;
    return novo;
}

void enqueue(Fila *fila, NodoFila *nodo) {
    if (fila->fim == NULL) {
        fila->inicio = nodo;
        fila->fim = nodo;
    } else {
        fila->fim->prox = nodo;
        fila->fim = nodo;
    }
    fila->tamanho++;
}

void showFila(Fila *fila) {
    NodoFila *atual = fila->inicio;
    printf("Fila de arestas\n");
    while (atual != NULL) {
        printf("[ %d -> %d (peso %d) ]\n", atual->arestaFila->partida, atual->arestaFila->chegada, atual->arestaFila->peso);
        atual = atual->prox;
    }
    printf("Tamanho da fila: %d\n", fila->tamanho);
}

