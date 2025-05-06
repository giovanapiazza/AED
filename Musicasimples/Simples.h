#ifndef MUSICATAD_H
#define MUSICATAD_H

struct musica {
    char titulo[256];
    char artista[256];
    char letra[256];
    int codigo;
    int execucoes;
};

struct nodo_LSE {
    struct musica *info;
    struct nodo_LSE *prox;
};

struct desc_LSE {
    struct nodo_LSE *LSE;
    int tamanho;
};

struct nodo_LSE* criaNodo(struct musica *novaMusica);
struct desc_LSE* criaDescritor(void);
void criaListaComDados(struct desc_LSE *lista);
struct nodo_LSE* removeLista(struct desc_LSE *lista, int posicao);
void imprime(struct desc_LSE *lista);
void procurar(struct desc_LSE *lista, char nome[256]);
void insere(struct desc_LSE *lista, struct nodo_LSE *novo_elemento, int posicao);
void liberaLista(struct desc_LSE *lista);

#endif
