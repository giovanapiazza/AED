#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

descritorAvl *Cria() {
    descritorAvl *avl = (descritorAvl *)malloc(sizeof(descritorAvl));
    avl->altura = 0;
    avl->raiz = NULL;
    return avl;
}

Arv *Balanceamento(Arv *no) {
    Arv *aux = NULL, *aux2 = NULL;
    if (no != NULL) {
        no->esq = Balanceamento(no->esq);
        no->dir = Balanceamento(no->dir);

        if ((no->rotacao == 2) || (no->rotacao == -2)) {
            if ((no->rotacao > 0) && (no->esq->rotacao > 0)) {
                // Rotação Direita
                aux = no->esq;
                no->esq = aux->dir;
                aux->dir = no;
                no->rotacao = 0;
                no = aux;
            }
            else if ((no->rotacao < 0) && (no->dir->rotacao < 0)) {
                // Rotação Esquerda
                aux = no->dir;
                no->dir = aux->esq;
                aux->esq = no;
                no->rotacao = 0;
                no = aux;
            }
            else if ((no->rotacao > 0) && (no->esq->rotacao < 0)) {
                // Rotação Dupla Direita
                aux = no->esq;
                aux2 = aux->dir;
                aux->dir = aux2->esq;
                aux2->esq = aux;
                no->esq = aux2->dir;
                aux2->dir = no;

                if (aux2->rotacao == -1)
                    no->rotacao = 1;
                else
                    no->rotacao = 0;

                if (aux2->rotacao == 1)
                    aux->rotacao = -1;
                else
                    aux->rotacao = 0;

                no = aux2;
            }
            else if ((no->rotacao < 0) && (no->dir->rotacao > 0)) {
                // Rotação Dupla Esquerda
                aux = no->dir;
                aux2 = aux->esq;
                aux->esq = aux2->dir;
                aux2->dir = aux;
                no->dir = aux2->esq;
                aux2->esq = no;

                if (aux2->rotacao == -1)
                    no->rotacao = 1;
                else
                    no->rotacao = 0;

                if (aux2->rotacao == 1)
                    aux->rotacao = -1;
                else
                    aux->rotacao = 0;

                no = aux2;
            }
        }
    }
    return no;
}

void Insere(Arv **no, int valor) {
    if ((*no) == NULL) {
        (*no) = (Arv *)malloc(sizeof(Arv));
        (*no)->dado = valor;
        (*no)->esq = NULL;
        (*no)->dir = NULL;
        (*no)->rotacao = 0;
    }
    else {
        if (valor <= (*no)->dado) {
            (*no)->rotacao++;
            Insere(&(*no)->esq, valor);
        }
        else {
            (*no)->rotacao--;
            Insere(&(*no)->dir, valor);
        }
    }
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

Arv* Remove(Arv* no, int valor) {
    if (no == NULL) {
        return NULL;
    }

    if (valor < no->dado) {
        no->esq = Remove(no->esq, valor);
    } else if (valor > no->dado) {
        no->dir = Remove(no->dir, valor);
    } else {
        if (no->esq == NULL) {
            Arv* temp = no->dir;
            free(no);
            return temp;
        } else if (no->dir == NULL) {
            Arv* temp = no->esq;
            free(no);
            return temp;
        } else {
            Arv* temp = no->dir;
            while (temp->esq != NULL) {
                temp = temp->esq;
            }
            no->dado = temp->dado;
            no->dir = Remove(no->dir, temp->dado);
        }
    }
    return no;
}

