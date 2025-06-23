#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct arv {
    struct arv *esq, *dir;
    int dado, rotacao;
} Arv;

typedef struct desc_avl {
    struct arv *raiz;
    int altura;
} descritorAvl;

descritorAvl *Cria();
Arv *Balanceamento(Arv *no);
void Insere(Arv **no, int valor);
void Imprime_preorder(Arv *no);
void Imprime_inorder(Arv *no);
Arv* Remove(Arv* no, int valor);

#endif
