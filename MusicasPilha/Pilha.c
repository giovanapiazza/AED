#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilha.h"


// Função para criar a descrição da pilha
struct desc_pilha *criaDescPilha(void) {
    struct desc_pilha *pilha = malloc(sizeof(struct desc_pilha));
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

// Função para criar uma música
struct musica *criarMusica() {
    struct musica *m = malloc(sizeof(struct musica));
    if (!m) {
        printf("Erro de alocação!\n");
        exit(1);
    }

    printf("Título: ");
    fgets(m->titulo, sizeof(m->titulo), stdin);
    m->titulo[strcspn(m->titulo, "\n")] = '\0';

    printf("Artista: ");
    fgets(m->artista, sizeof(m->artista), stdin);
    m->artista[strcspn(m->artista, "\n")] = '\0';

    printf("Letra: ");
    fgets(m->letra, sizeof(m->letra), stdin);
    m->letra[strcspn(m->letra, "\n")] = '\0';

    printf("Código: ");
    scanf("%d", &m->codigo);
    printf("Execuções: ");
    scanf("%d", &m->execucoes);
    getchar(); // limpa o buffer
    return m;
}

// Cria nodo da pilha
struct nodo_pilha *criaNodoPilha(struct musica *m) {
    struct nodo_pilha *novo = malloc(sizeof(struct nodo_pilha));
    novo->info = m;
    novo->prox = NULL;
    return novo;
}

// Inserir no topo
void inserir(struct desc_pilha *pilha, struct nodo_pilha *novoElemento) {
    novoElemento->prox = pilha->topo;
    pilha->topo = novoElemento;
    pilha->tamanho++;
}

// Remover do topo
struct nodo_pilha *remover(struct desc_pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Pilha vazia.\n");
        return NULL;
    }
    struct nodo_pilha *aux = pilha->topo;
    pilha->topo = pilha->topo->prox;
    pilha->tamanho--;
    return aux;
}

// Ver topo
struct nodo_pilha *topo(struct desc_pilha *pilha) {
    return pilha->topo;
}

// Verifica se existe uma lista
int procurarLista(struct desc_pilha *pilha) {
    return pilha != NULL && pilha->topo != NULL;
}

void lerArquivoMostrarMusicas(const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    char linha[512];
    printf("\nMúsicas disponíveis no arquivo:\n");
    while (fgets(linha, sizeof(linha), fp)) {
        printf("- %s", linha);
    }

    fclose(fp);
}

// Imprimir pilha
void imprimir(struct desc_pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        printf("Pilha vazia.\n");
        return;
    }
    struct nodo_pilha *aux = pilha->topo;
    printf("\n--- Músicas na Pilha ---\n");
    while (aux != NULL) {
        printf("Título: %s\n", aux->info->titulo);
        printf("Artista: %s\n", aux->info->artista);
        printf("Letra: %s\n", aux->info->letra);
        printf("Código: %d\n", aux->info->codigo);
        printf("-----------------------------\n");
        aux = aux->prox;
    }
}
