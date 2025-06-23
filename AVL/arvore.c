#include "avl.h"

descritorAvl *Cria(){
	descritorAvl *avl = (descritorAvl *)malloc(sizeof(descritorAvl));
	avl->altura = 0;
	avl->raiz = NULL;
	return avl;
}


Arv *Balanceamento(Arv *no){
    Arv *aux=NULL,*aux2=NULL;
    if(no!=NULL){
        no->esq = Balanceamento(no->esq);
        no->dir = Balanceamento(no->dir);
        if((no->rotacao==2)||(no->rotacao==-2)){
            if((no->rotacao>0)&&(no->esq->rotacao>0)){
                //Rotacao Direita
                aux = no->esq;
                no->esq = aux->dir;
                aux->dir = no;
                no->rotacao = 0;
                no=aux;
            }
            else{
                if((no->rotacao<0)&&(no->dir->rotacao<0)){
                    //Rotacao Esquerda
                    aux = no->dir;
                    no->dir = aux->esq;
                    aux->esq = no;
                    no->rotacao = 0;
                    no = aux;
                }
                else{
                    //Rotacao Dupla Direita
                    if((no->rotacao>0)&&(no->esq->rotacao<0)){
                        aux=no->esq;
                        aux2=aux->dir;
                        aux->dir=aux2->esq;
                        aux2->esq=aux;
                        no->esq=aux2->dir;
                        aux2->dir=no;
                        if(aux2->rotacao==-1){
                            no->rotacao=1;
                        }
                        else{
                            no->rotacao=0;
                        }
                        if(aux2->rotacao==1){
                            aux->rotacao=-1;
                        }
                        else{
                            aux->rotacao=0;
                        }
                        no=aux2;
                    }
                    else{
                        //Rotacao Dupla Esquerda
                        if((no->rotacao<0)&&(no->dir->rotacao>0)){
                            aux=no->dir;
                            aux2=aux->esq;
                            aux->esq=aux2->dir;
                            aux2->dir=aux;
                            no->dir=aux2->esq;
                            aux2->esq=no;
                            if(aux2->rotacao==-1){
                                no->rotacao=1;
                            }
                            else{
                                no->rotacao=0;
                            }
                            if(aux2->rotacao==1){
                                aux->rotacao=-1;
                            }
                            else{
                                aux->rotacao=0;
                            }
                            no=aux2;
                        }
                    }
                }
            }
        }
        return no;
    }
    return NULL;
}

void Insere(Arv **no,int valor){
	if((*no)==NULL){
		(*no)=(Arv*)malloc(sizeof(Arv));
		(*no)->dado=valor;
		(*no)->esq=NULL;
		(*no)->dir=NULL;
		(*no)->rotacao=0;
	}
	else{
		if(valor<=(*no)->dado){
            (*no)->rotacao++;
			Insere(&(*no)->esq,valor);
		}
		else{
		    (*no)->rotacao--;
			Insere(&(*no)->dir,valor);
		}
	}
}

void Imprime_preorder(Arv *no){
	if(no!=NULL){
		printf("<%d>",no->dado);
		Imprime_preorder(no->esq);
		Imprime_preorder(no->dir);
	}
}
void Imprime_inorder(Arv *no){
	if(no!=NULL){
		Imprime_inorder(no->esq);
		printf("<%d>",no->dado);
		Imprime_inorder(no->dir);
	}
}


