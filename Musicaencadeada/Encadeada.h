#ifndef MUSICATAD_H
#define MUSICATAD_H

struct nodo_LDE* criaNodo(struct musica *novaMusica);
struct desc_LDE* criaDescritor(void);
void criaListaComDados(struct desc_LDE *lista);
struct nodo_LDE* removeLista(struct desc_LDE *lista, int posicao);
void imprime(struct desc_LDE *lista);
void procurar(struct desc_LDE *lista, char nome[256]);
void insere(struct desc_LDE *lista, struct nodo_LDE *novo_elemento, int posicao);
void liberaLista(struct desc_LDE *lista);

#endif
