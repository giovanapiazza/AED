#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// colocar o anterior na struct, e no descritor um ponteiro q chama o final, e no auxiliar que aponta pro outro

struct musica {
    char titulo[256];
    char artista[256];
    char letra[256];
    int codigo;
    int execucoes;
};

struct nodo_LDE {
    struct musica *info;
    struct nodo_LDE *prox;
    struct nodo_LDE *ante;
};

struct desc_LDE {
    struct nodo_LDE *LDE;
    int tamanho;
};


struct nodo_LDE* criaNodo(struct musica *novaMusica) {
    struct nodo_LDE *novo = malloc(sizeof(struct nodo_LDE));
    novo->info = novaMusica;
    novo->prox = NULL;
    novo->ante = NULL;
    return novo;
}

struct desc_LDE* criaDescritor(void) {
    struct desc_LDE *novoDesc = malloc(sizeof(struct desc_LDE));
    novoDesc->LDE = NULL;
    novoDesc->tamanho = 0;
    return novoDesc;
}

void insere(struct desc_LDE *lista, struct nodo_LDE *novo_elemento, int posicao) {
    struct nodo_LDE *aux = lista->LDE;
    struct nodo_LDE *anterior = NULL;
    int contador = 0;

    if (lista->LDE == NULL || posicao <= 0) {
        novo_elemento->prox = lista->LDE;
        novo_elemento->ante = NULL;
        if (lista->LDE != NULL)
            lista->LDE->ante = novo_elemento;
        lista->LDE = novo_elemento;
    } else {
        while (aux != NULL && contador < posicao) {
            anterior = aux;
            aux = aux->prox;
            contador++;
        }
        novo_elemento->prox = aux;
        novo_elemento->ante = anterior;
        if (anterior != NULL)
            anterior->prox = novo_elemento;
        if (aux != NULL)
            aux->ante = novo_elemento;
    }

    lista->tamanho++;
}

struct nodo_LDE* removeLista(struct desc_LDE *lista, int posicao) {
    if (lista->tamanho == 0 || posicao < 0 || posicao >= lista->tamanho) {
        printf("Posição inválida ou lista vazia!\n");
        return NULL;
    }

    struct nodo_LDE *removido = lista->LDE;

    for (int i = 0; i < posicao; i++) {
        removido = removido->prox;
    }

    if (removido->ante != NULL)
        removido->ante->prox = removido->prox;
    else
        lista->LDE = removido->prox;

    if (removido->prox != NULL)
        removido->prox->ante = removido->ante;

    lista->tamanho--;
    printf("Música removida com sucesso!\n");
    return removido;
}

void procurar(struct desc_LDE *lista, char nome[256]) {
    struct nodo_LDE *aux = lista->LDE;
    while (aux != NULL) {
        if (strcmp(aux->info->titulo, nome) == 0) {
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
    struct nodo_LDE *aux = lista->LDE;
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
        insere(lista, nodo, lista->tamanho); // insere no final
    }

    printf("\nLista criada com %d músicas!\n", lista->tamanho);
}

void liberaLista(struct desc_LE *lista) {
    struct nodo_LDE *aux = lista->LDE;
    while (aux != NULL) {
        struct nodo_LDE *temp = aux;
        aux = aux->prox;
        free(temp->info);
        free(temp);
    }
    free(lista);
}
