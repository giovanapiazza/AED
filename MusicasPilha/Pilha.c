#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições das estruturas
struct musica {
    char titulo[256];
    char artista[256];
    char letra[256];
    int codigo;
    int execucoes;
};

struct nodo_pilha {
    struct nodo_pilha *prox;
    struct musica *info;
};

struct desc_pilha {
    struct nodo_pilha *topo;
    int tamanho;
};

// Função para criar a descrição da pilha
struct desc_pilha *criaDescPilha(void) {
    struct desc_pilha *pilha = malloc(sizeof(struct desc_pilha));
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

// Função para criar uma música
struct musica *criarMusica() {
    struct musica *m = malloc(sizeof(struct musica));
    printf("Título: ");
    fgets(m->titulo, 256, stdin);
    m->titulo[strcspn(m->titulo, "\n")] = '\0';

    printf("Artista: ");
    fgets(m->artista, 256, stdin);
    m->artista[strcspn(m->artista, "\n")] = '\0';

    printf("Letra: ");
    fgets(m->letra, 256, stdin);
    m->letra[strcspn(m->letra, "\n")] = '\0';

    printf("Código: ");
    scanf("%d", &m->codigo);
    printf("Execuções: ");
    scanf("%d", &m->execucoes);
    getchar(); // limpar buffer
    return m;
}

// Cria nodo da pilha
struct nodo_pilha *criaNodoPilha(struct musica *m) {
    struct nodo_pilha *novo = malloc(sizeof(struct nodo_pilha));
    novo->info = m;
    novo->prox = NULL;
    return novo;
}

// Inserir no topo
void inserir(struct desc_pilha *pilha, struct nodo_pilha *novoElemento) {
    novoElemento->prox = pilha->topo;
    pilha->topo = novoElemento;
    pilha->tamanho++;
}

// Remover do topo
struct nodo_pilha *remover(struct desc_pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Pilha vazia.\n");
        return NULL;
    }
    struct nodo_pilha *aux = pilha->topo;
    pilha->topo = pilha->topo->prox;
    pilha->tamanho--;
    return aux;
}

// Ver topo
struct nodo_pilha *topo(struct desc_pilha *pilha) {
    return pilha->topo;
}

// Verifica se existe uma lista
int procurarLista(struct desc_pilha *pilha) {
    return pilha != NULL && pilha->topo != NULL;
}

// Imprimir pilha
void imprimir(struct desc_pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        printf("Pilha vazia.\n");
        return;
    }
    struct nodo_pilha *aux = pilha->topo;
    printf("\n--- Músicas na Pilha ---\n");
    while (aux != NULL) {
        printf("Título: %s\n", aux->info->titulo);
        printf("Artista: %s\n", aux->info->artista);
        printf("Letra: %s\n", aux->info->letra);
        printf("Código: %d\n", aux->info->codigo);
        printf("-----------------------------\n");
        aux = aux->prox;
    }
}

int main() {
    int op;
    struct desc_pilha *pilha = NULL;

    do {
        printf("\n---------- Menu ----------\n");
        printf("1 - Criar pilha de músicas\n");
        printf("2 - Inserir nova música\n");
        printf("3 - Remover o topo\n");
        printf("4 - Ver o topo\n");
        printf("5 - Verificar se existe uma lista\n");
        printf("6 - Imprimir a pilha\n");
        printf("7 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        getchar(); 

        switch (op) {
            case 1:
                if (pilha == NULL) {
                    pilha = criaDescPilha();
                    printf("Pilha criada com sucesso!\n");
                } else {
                    printf("Pilha já existe.\n");
                }
                break;

            case 2:
                if (pilha == NULL) {
                    printf("Crie a pilha primeiro!\n");
                    break;
                }
                printf("\nInserir nova música:\n");
                struct musica *m = criarMusica();
                struct nodo_pilha *n = criaNodoPilha(m);
                inserir(pilha, n);
                printf("Música inserida no topo!\n");
                break;

            case 3:
                if (pilha == NULL || pilha->topo == NULL) {
                    printf("Pilha vazia ou inexistente.\n");
                    break;
                }
                struct nodo_pilha *rem = remover(pilha);
                if (rem) {
                    printf("Música '%s' removida do topo.\n", rem->info->titulo);
                    free(rem->info);
                    free(rem);
                }
                break;

            case 4:
                if (pilha == NULL || pilha->topo == NULL) {
                    printf("Pilha vazia ou inexistente.\n");
                } else {
                    struct nodo_pilha *top = topo(pilha);
                    printf("Topo: %s (%s)\n", top->info->titulo, top->info->artista);
                }
                break;

            case 5:
                if (procurarLista(pilha))
                    printf("Sim, existe uma lista com elementos.\n");
                else
                    printf("Não existe uma lista com elementos.\n");
                break;

            case 6:
                imprimir(pilha);
                break;

            case 7:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida, tente novamente!\n");
                break;
        }
    } while (op != 7);
  
    return 0;
}
