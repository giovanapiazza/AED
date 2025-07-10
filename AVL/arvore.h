#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct arv {
    struct arv *esq, *dir;
    int dado;
    int altura;
} Arv;

typedef struct desc_avl {
    struct arv *raiz;
} descritorAvl;

descritorAvl *Cria();
Arv *Insere(Arv *no, int valor);
Arv *Remove(Arv *no, int valor);
void Imprime_preorder(Arv *no);
void Imprime_inorder(Arv *no);

#endif
