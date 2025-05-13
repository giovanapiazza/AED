#ifndef MUSICATAD_H
#define MUSICATAD_H

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
    struct nodo_LDE *ant;
};

struct desc_LDE {
    struct nodo_LDE *inicio;
    struct nodo_LDE *fim;
    int tamanho;
};

// Funções principais
struct nodo_LDE* criaNodo(struct musica *novaMusica);
struct desc_LDE* criaDescritor(void);
void insere(struct desc_LDE *lista, struct nodo_LDE *novo_elemento, int posicao);
struct nodo_LDE* removeLista(struct desc_LDE *lista, int posicao);
void procurar(struct desc_LDE *lista, char nome[256]);
void imprime(struct desc_LDE *lista);
void criaListaComDados(struct desc_LDE *lista);

#endif
