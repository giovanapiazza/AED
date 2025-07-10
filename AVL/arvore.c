#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(Arv *no) {
    if (no == NULL) return -1;
    return no->altura;
}

descritorAvl *Cria() {
    descritorAvl *avl = (descritorAvl *)malloc(sizeof(descritorAvl));
    avl->raiz = NULL;
    return avl;
}

// Rotação simples para a direita
Arv *rotacaoDireita(Arv *y) {
    Arv *x = y->esq;
    Arv *T2 = x->dir;


    x->dir = y;
    y->esq = T2;


    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x; 
}


Arv *rotacaoEsquerda(Arv *x) {
    Arv *y = x->dir;
    Arv *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y; 
}

// Calcula o fator de balanceamento do nó
int fatorBalanceamento(Arv *no) {
    if (no == NULL) return 0;
    return altura(no->esq) - altura(no->dir);
}

// Insere  e balanceamento
Arv *Insere(Arv *no, int valor) {

    if (no == NULL) {
        Arv *novo = (Arv *)malloc(sizeof(Arv));
        novo->dado = valor;
        novo->esq = novo->dir = NULL;
        novo->altura = 0;
        return novo;
    }


    if (valor < no->dado)
        no->esq = Insere(no->esq, valor);
    else if (valor > no->dado)
        no->dir = Insere(no->dir, valor);
    else
        return no; 

    no->altura = max(altura(no->esq), altura(no->dir)) + 1;

    int fb = fatorBalanceamento(no);

    //SD
    if (fb > 1 && valor < no->esq->dado)
        return rotacaoDireita(no);

    //SD
    if (fb < -1 && valor > no->dir->dado)
        return rotacaoEsquerda(no);

    //DD
    if (fb > 1 && valor > no->esq->dado) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }

    // DE
    if (fb < -1 && valor < no->dir->dado) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no; 
}

// nó com menor valor 
Arv* minValor(Arv* no) {
    Arv* atual = no;
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}


Arv* Remove(Arv* raiz, int valor) {
    if (raiz == NULL)
        return raiz;

    // Percorre a árvore
    if (valor < raiz->dado)
        raiz->esq = Remove(raiz->esq, valor);
    else if (valor > raiz->dado)
        raiz->dir = Remove(raiz->dir, valor);
    else {
        // Nó com apenas um filho ou nenhum
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            Arv* temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else
                *raiz = *temp;

            free(temp);
        } else {
            Arv* temp = minValor(raiz->dir);
            raiz->dado = temp->dado;
            raiz->dir = Remove(raiz->dir, temp->dado);
        }
    }

    if (raiz == NULL)
        return raiz;

    // Atualiza altura e realiza balanceamento
    raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    int fb = fatorBalanceamento(raiz);
    // rotação quando remove
    if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0)
        return rotacaoDireita(raiz);

    if (fb > 1 && fatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);

    if (fb < -1 && fatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void Imprime_preorder(Arv *no) {
    if (no != NULL) {
        printf("<%d>", no->dado);
        Imprime_preorder(no->esq);
        Imprime_preorder(no->dir);
    }
}

void Imprime_inorder(Arv *no) {
    if (no != NULL) {
        Imprime_inorder(no->esq);
        printf("<%d>", no->dado);
        Imprime_inorder(no->dir);
    }
}
