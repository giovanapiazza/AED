#include <stdio.h>
#include <stdlib.h>

typedef struct Arvore {
    int dado;
    int altura;
    struct Arvore *esq, *dir;
} Arv;

typedef struct {
    Arv *raiz;
} descritorAvl;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(Arv *no) {
    return (no == NULL) ? -1 : no->altura;
}

int fatorBalanceamento(Arv *no) {
    return (no == NULL) ? 0 : altura(no->esq) - altura(no->dir);
}

descritorAvl *Cria() {
    descritorAvl *avl = (descritorAvl *)malloc(sizeof(descritorAvl));
    avl->raiz = NULL;
    return avl;
}

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

    if (fb > 1 && valor < no->esq->dado)
        return rotacaoDireita(no);

    if (fb < -1 && valor > no->dir->dado)
        return rotacaoEsquerda(no);

    if (fb > 1 && valor > no->esq->dado) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }

    if (fb < -1 && valor < no->dir->dado) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

Arv *minValor(Arv *no) {
    while (no->esq != NULL)
        no = no->esq;
    return no;
}

Arv *Remove(Arv *raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->dado)
        raiz->esq = Remove(raiz->esq, valor);
    else if (valor > raiz->dado)
        raiz->dir = Remove(raiz->dir, valor);
    else {
        if (raiz->esq == NULL || raiz->dir == NULL) {
            Arv *temp = (raiz->esq) ? raiz->esq : raiz->dir;
            free(raiz);
            return temp;
        } else {
            Arv *temp = minValor(raiz->dir);
            raiz->dado = temp->dado;
            raiz->dir = Remove(raiz->dir, temp->dado);
        }
    }

    raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    int fb = fatorBalanceamento(raiz);

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

void Imprime_inorder(Arv *no) {
    if (no != NULL) {
        Imprime_inorder(no->esq);
        printf("<%d>", no->dado);
        Imprime_inorder(no->dir);
    }
}

void Imprime_preorder(Arv *no) {
    if (no != NULL) {
        printf("<%d>", no->dado);
        Imprime_preorder(no->esq);
        Imprime_preorder(no->dir);
    }
}

void Libera(Arv *no) {
    if (no != NULL) {
        Libera(no->esq);
        Libera(no->dir);
        free(no);
    }
}

int main() {
    int op, valor, controle = 0;
    descritorAvl *avl = NULL;

    do {
        printf("\n===== MENU AVL =====\n");
        printf("1- Criar AVL\n");
        printf("2- Remover uma chave\n");
        printf("3- Inserir uma chave\n");
        printf("4- Visualizar árvore (Inorder)\n");
        printf("5- Visualizar árvore (Preorder)\n");
        printf("6- Finalizar programa\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        switch (op) {
        case 1:
            if (controle == 0) {
                avl = Cria();
                printf("Árvore criada com sucesso!\n");
                controle = 1;
            } else {
                printf("Árvore já foi criada!\n");
            }
            break;

        case 2:
            if (controle && avl->raiz != NULL) {
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                avl->raiz = Remove(avl->raiz, valor);
                printf("Remoção concluída.\n");
            } else {
                printf("Crie a árvore e insira elementos primeiro!\n");
            }
            break;

        case 3:
            if (controle) {
                printf("Digite um valor para inserir: ");
                scanf("%d", &valor);
                avl->raiz = Insere(avl->raiz, valor);
                printf("Valor inserido com sucesso!\n");
            } else {
                printf("Crie a árvore primeiro!\n");
            }
            break;

        case 4:
            if (controle && avl->raiz != NULL) {
                printf("Inorder: ");
                Imprime_inorder(avl->raiz);
                printf("\n");
            } else {
                printf("Crie a árvore e insira elementos primeiro!\n");
            }
            break;

        case 5:
            if (controle && avl->raiz != NULL) {
                printf("Preorder: ");
                Imprime_preorder(avl->raiz);
                printf("\n");
            } else {
                printf("Crie a árvore e insira elementos primeiro!\n");
            }
            break;

        case 6:
            printf("Encerrando o programa...\n");
            if (controle) {
                Libera(avl->raiz);
                free(avl);
            }
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }

    } while (op != 6);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aresta {
    int partida, chegada, peso;
    struct Aresta *prox;
} Aresta;

typedef struct Nodo {
    int chave;
    Aresta *adjacencias;
    struct Nodo *prox;
} Nodo;

typedef struct Grafo {
    int max_vertices;
    int max_arestas;
    Nodo *nodos;
} Grafo;

typedef struct NodoPilhaVertice {
    Nodo *vertice;
    struct NodoPilhaVertice *prox;
} NodoPilhaVertice;

typedef struct {
    NodoPilhaVertice *topo;
    int tamanho;
} PilhaVertice;

Grafo *inicializaGrafo(int tamanho) {
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->max_vertices = tamanho;
    grafo->max_arestas = 0;
    grafo->nodos = NULL;

    for (int i = 0; i < tamanho; i++) {
        Nodo *novo = malloc(sizeof(Nodo));
        novo->chave = i + 1;
        novo->adjacencias = NULL;
        novo->prox = grafo->nodos;
        grafo->nodos = novo;
    }
    return grafo;
}

Nodo *buscaVertice(Grafo *grafo, int chave) {
    Nodo *atual = grafo->nodos;
    while (atual != NULL) {
        if (atual->chave == chave)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

Grafo *insereAresta(Grafo *grafo, int saida, int chegada, int peso) {
    Nodo *nodo = buscaVertice(grafo, saida);
    if (!nodo) return grafo;

    Aresta *nova = malloc(sizeof(Aresta));
    nova->partida = saida;
    nova->chegada = chegada;
    nova->peso = peso;
    nova->prox = nodo->adjacencias;
    nodo->adjacencias = nova;

    grafo->max_arestas++;
    return grafo;
}

Grafo *parser(char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        return NULL;
    }

    int total;
    fscanf(file, "%d", &total);
    Grafo *grafo = inicializaGrafo(total);

    int p, c, peso;
    while (fscanf(file, "%d %d %d", &p, &c, &peso) == 3) {
        grafo = insereAresta(grafo, p, c, peso);
    }

    fclose(file);
    return grafo;
}

void imprimeGrafoDe(Nodo *inicio) {
    Nodo *nodo = inicio;
    while (nodo != NULL) {
        printf("Nodo %d - ", nodo->chave);
        Aresta *adj = nodo->adjacencias;
        while (adj != NULL) {
            printf("[ ->%d (peso %d) ] ", adj->chegada, adj->peso);
            adj = adj->prox;
        }
        printf("\n");
        nodo = nodo->prox;
    }
}

void liberarGrafo(Grafo *grafo) {
    Nodo *n = grafo->nodos;
    while (n) {
        Aresta *a = n->adjacencias;
        while (a) {
            Aresta *tmpA = a;
            a = a->prox;
            free(tmpA);
        }
        Nodo *tmpN = n;
        n = n->prox;
        free(tmpN);
    }
    free(grafo);
}

PilhaVertice *criaPilhaVertice() {
    PilhaVertice *pilha = malloc(sizeof(PilhaVertice));
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

void pushVertice(PilhaVertice *pilha, Nodo *vertice) {
    NodoPilhaVertice *novo = malloc(sizeof(NodoPilhaVertice));
    novo->vertice = vertice;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
}

Nodo *popVertice(PilhaVertice *pilha) {
    if (!pilha->topo) return NULL;
    NodoPilhaVertice *removido = pilha->topo;
    Nodo *v = removido->vertice;
    pilha->topo = removido->prox;
    free(removido);
    pilha->tamanho--;
    return v;
}

void liberaPilhaVertice(PilhaVertice *pilha) {
    while (pilha->topo) {
        NodoPilhaVertice *tmp = pilha->topo;
        pilha->topo = tmp->prox;
        free(tmp);
    }
    free(pilha);
}

int main() {
    int opcao, chave_busca;
    Grafo *grafo = NULL;
    char nomeArquivo[100];

    do {
        printf("\n--------------MENU--------------\n");
        printf("1 - Carregar grafo (lista)\n");
        printf("2 - Buscar vertice\n");
        printf("3 - Imprimir grafo\n");
        printf("4 - DFS iterativa\n");
        printf("0 - Sair\n");
        printf("\nEscolha sua opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo: ");
                fgets(nomeArquivo, sizeof(nomeArquivo), stdin);
                nomeArquivo[strcspn(nomeArquivo, "\n")] = 0;
                grafo = parser(nomeArquivo);
                if (grafo)
                    printf("Grafo carregado com sucesso!\n");
                break;

            case 2:
                if (!grafo) {
                    printf("Grafo nao carregado!\n");
                    break;
                }
                printf("Digite a chave do vertice: ");
                scanf("%d", &chave_busca);
                Nodo *encontrado = buscaVertice(grafo, chave_busca);
                if (encontrado) {
                    printf("Vertice encontrado: %d\n", encontrado->chave);
                    Aresta *a = encontrado->adjacencias;
                    if (!a) printf("Nao ha arestas partindo desse vertice.\n");
                    else {
                        while (a) {
                            printf("- %d -> %d (peso %d)\n", a->partida, a->chegada, a->peso);
                            a = a->prox;
                        }
                    }
                } else {
                    printf("Vertice nao encontrado.\n");
                }
                break;

            case 3:
                if (grafo)
                    imprimeGrafoDe(grafo->nodos);
                else
                    printf("Grafo nao carregado!\n");
                break;

            case 4:
                if (!grafo) {
                    printf("Grafo nao carregado!\n");
                    break;
                }
                printf("Digite o vertice de inicio: ");
                int inicio;
                scanf("%d", &inicio);

                int *visitado = calloc(grafo->max_vertices + 1, sizeof(int));
                PilhaVertice *pilha = criaPilhaVertice();

                Nodo *vInicio = buscaVertice(grafo, inicio);
                if (!vInicio) {
                    printf("Vertice nao encontrado!\n");
                    break;
                }

                printf("DFS a partir do vertice %d:\n", inicio);
                pushVertice(pilha, vInicio);

                while (pilha->topo) {
                    Nodo *atual = popVertice(pilha);
                    if (!visitado[atual->chave]) {
                        visitado[atual->chave] = 1;
                        printf("Visitando vertice: %d\n", atual->chave);
                        Aresta *a = atual->adjacencias;
                        while (a) {
                            Nodo *vizinho = buscaVertice(grafo, a->chegada);
                            if (!visitado[vizinho->chave])
                                pushVertice(pilha, vizinho);
                            a = a->prox;
                        }
                    }
                }
                liberaPilhaVertice(pilha);
                free(visitado);
                break;

            case 0:
                printf("Encerrando programa...\n");
                if (grafo)
                    liberarGrafo(grafo);
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

