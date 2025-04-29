//Implemente uma TAD de Lista Simplesmente  Encadeada (LSE), de structs nodo_LSE, as quais possuem a struct musica como informação, onde contenha as seguintes operações (interfaces): – CriaLista – Insere – Remove – Consulta – Imprime 
// Crie um programa principal que seja capaz de utilizar a TAD em questão.
#include <stdio.h>
#include <stdlib.h>

    struct musica{ 
        char titulo[256]; 
        char artista[256]; 
        char letra[256]; 
        int codigo; 
        int execucoes; 
        } 

    struct nodo_LSE{ 
        struct nodo_LSE *prox; 
        struct musica *info; 
        } 
    struct desc_LSE{ 
        struct nodo_LSE *LSE; 
        int tamanho; 
        } 

    struct nodo* criaNodo(int novoDado){//nodos
        struct nodo *novoElem = (struct nodo *)malloc(sizeof(struct nodo));
        novoElem->dado = novoDado;
        novoElem->prox =  NULL;
        return novoElem;
        }

    struct desc_lista_encadeada * criaDescritor(void){
        struct desc_lista_encadeada *novoDescLista = (struct desc_lista_encadeada *)malloc(sizeof(struct desc_lista_encadeada));
        novoDescLista->tamanho = 0;
        novoDescLista->lista=NULL;
        return novoDescLista;
        }

            //Para inserir uma nova música
    void insere(struct desc_lista_encadeada *minhaLista, struct nodo *novo_elemento, int posicao, int chaveNova){

        printf("Em qual posição você deseja inserir a musica:\n");
        setbuf(stdin,NULL);
        scanf("%d", &posicao);
        printf("digite o valor do novo nodo\n");
		setbuf(stdin,NULL);
		scanf("%d",&chaveNova);
		novoNodo = criaNodo(chaveNova);
					
					insere(minhaNovaLista,novoNodo,posicao);
					break;

        if((minhaLista->lista == NULL)||(posicao ==0)){//começo
            novo_elemento->prox = minhaLista->lista;
            minhaLista->lista = novo_elemento;
            minhaLista->tamanho++;
        }
        else{ // não sendo no começo
            struct nodo *aux = minhaLista->lista;
            int listaPos = 0;
            if(minhaLista->tamanho < posicao){// se não tem a posição vai pro final da lista
                while(aux->prox != NULL){
                    aux = aux->prox; 
                }
                aux->prox = novo_elemento;
                minhaLista->tamanho++;
                return;
            }else{//se tem vai pro lugar
                struct nodo *anterior;
                while(aux != NULL){
                    anterior = aux;
                    aux = aux->prox; 
                    listaPos++;
                    if(listaPos == posicao){
                        novo_elemento->prox	= aux;
                        anterior->prox		= novo_elemento;
                        minhaLista->tamanho++;
                        return;
                    }
                }
            }
        }
    }
    
    struct nodo* removeLista(struct desc_lista_encadeada *minhaLista, int posicao){
        if((minhaLista->tamanho ==0)||(posicao > minhaLista->tamanho)){ //posicao nao existe na lista não remove nada
            printf("posicao não existe OU LISTA VAZIA!\n");
            return NULL;
        }
        else{
            if(posicao==0){ //delecao no inicio da lista atualiza apenas o ponteiro da lista do descritor de lista
                struct nodo *aux = minhaLista->lista;
                minhaLista->lista = minhaLista->lista->prox;
                minhaLista->tamanho--;
                return aux; 
            }
            else{ //delecao no meio ou no fim da lista
                int listaPos=0;
                struct nodo *anterior;
                struct nodo *aux = minhaLista->lista;
                while(aux != NULL){
                    anterior = aux;
                    aux = aux->prox;
                    listaPos++;
                    if(listaPos == posicao){
                        anterior->prox = aux->prox;
                        minhaLista->tamanho--;
                        return aux;
                    }
                }	
            }
        }
    }

        //Para imprimir todas as músicas
void imprime(struct desc_lista_encadeada *minhaLista){
    struct nodo* aux = minhaLista->lista;
    while(aux != NULL){
        printf("[%d] ", aux->dado);
            aux = aux->prox;
        }
        printf("\n");
    }
    

int main(void){
    int op;

    do {
    printf("Escolha uma opção\n");
    printf("1 Criar lista de músicas");
    printf("2 Inserir uma nova música a sua lista\n");
    printf("3 Remover uma música da lista\n");
    printf("4 Procurar por uma música\n");
    printf("5 Imprimir lista de músicas\n");
    printf("0 Encerrar");
    scanf("%d", &op);

    switch(op){
        case 0: 
        printf("Encerrando...");
        break;

        case 1:
        printf("Criando nova lista de músicas");
        break;

        case 2:
            printf("Vamos inserir uma música nova");
            insere(desc_lista_encadeada *minhaLista, nodo *novo_elemento, posicao, chaveNova)
            printf("Música inserida com sucesso");
        break;

        case 3
            printf("Música removida com sucesso");
        break;

        case 4
        printf("Vamos procurar por uma música\n");

        break;

        case 5
            printf("Aqui está sua lista de música");
            imprime(desc_lista_encadeada *minhaLista)
        break;

        default: 
        printf(" Opção invalida tente novamente...\n");
        break;
        

    }
    }while(op != 0);
    return 0;
}
