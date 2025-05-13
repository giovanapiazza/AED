#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Musicatad.h"

struct nodo_LDE* criaNodo(struct musica *novaMusica) {
    struct nodo_LDE *novo = malloc(sizeof(struct nodo_LDE));
    novo->info = novaMusica;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

struct desc_LDE* criaDescritor(void) {
    struct desc_LDE *desc = malloc(sizeof(struct desc_LDE));
    desc->inicio = NULL;
    desc->fim = NULL;
    desc->tamanho = 0;
    return desc;
}

void insere(struct desc_LDE *lista, struct nodo_LDE *novo, int posicao) {
    if (lista->inicio == NULL || posicao <= 0) {
        novo->prox = lista->inicio;
        if (lista->inicio)
            lista->inicio->ant = novo;
        else
            lista->fim = novo;
        lista->inicio = novo;
    } else if (posicao >= lista->tamanho) {
        novo->ant = lista->fim;
        if (lista->fim)
            lista->fim->prox = novo;
        else
            lista->inicio = novo;
        lista->fim = novo;
    } else {
        struct nodo_LDE *aux = lista->inicio;
        for (int i = 0; i < posicao; i++)
            aux = aux->prox;
        novo->prox = aux;
        novo->ant = aux->ant;
        if (aux->ant)
            aux->ant->prox = novo;
        aux->ant = novo;
    }
    lista->tamanho++;
}

struct nodo_LDE* removeLista(struct desc_LDE *lista, int posicao) {
    if (lista->tamanho == 0 || posicao < 0 || posicao >= lista->tamanho) {
        printf("Posição inválida ou lista vazia!\n");
        return NULL;
    }

    struct nodo_LDE *removido = lista->inicio;
    for (int i = 0; i < posicao; i++)
        removido = removido->prox;

    if (removido->ant)
        removido->ant->prox = removido->prox;
    else
        lista->inicio = removido->prox;

    if (removido->prox)
        removido->prox->ant = removido->ant;
    else
        lista->fim = removido->ant;

    lista->tamanho--;
    printf("Música removida com sucesso!\n");
    return removido;
}

void procurar(struct desc_LDE *lista, char nome[256]) {
    struct nodo_LDE *aux = lista->inicio;
    while (aux != NULL) {
        if (strcasecmp(aux->info->titulo, nome) == 0) {
            printf("Música encontrada!\n");
            printf("Título: %s\n", aux->info->titulo);
            printf("Artista: %s\n", aux->info->artista);
            printf("Letra: %s\n", aux->info->letra);
            printf("Código: %d\n", aux->info->codigo);
            printf("Execuções: %d\n", aux->info->execucoes);
            return;
        }
        aux = aux->prox;
    }
    printf("Música não encontrada.\n");
}

void imprime(struct desc_LDE *lista) {
    struct nodo_LDE *aux = lista->inicio;
    int i = 1;
    while (aux != NULL) {
        printf("\nMúsica %d:\n", i++);
        printf("Título: %s\n", aux->info->titulo);
        printf("Artista: %s\n", aux->info->artista);
        printf("Execuções: %d\n", aux->info->execucoes);
        aux = aux->prox;
    }
}

void criaListaComDados(struct desc_LDE *lista) {
    int qtd;
    printf("Quantas músicas deseja adicionar? ");
    scanf("%d", &qtd);
    setbuf(stdin, NULL);

    for (int i = 0; i < qtd; i++) {
        struct musica *m = malloc(sizeof(struct musica));
        printf("\nMúsica %d:\n", i + 1);

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
        setbuf(stdin, NULL);

        printf("Número de execuções: ");
        scanf("%d", &m->execucoes);
        setbuf(stdin, NULL);

        struct nodo_LDE *nodo = criaNodo(m);
        insere(lista, nodo, lista->tamanho);
    }

    printf("\nLista criada com %d músicas!\n", lista->tamanho);
}
