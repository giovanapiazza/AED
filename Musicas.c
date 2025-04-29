#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structs principais
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

// Funções da TAD
struct nodo_LSE* criaNodo(struct musica *novaMusica) {
    struct nodo_LSE *novo = malloc(sizeof(struct nodo_LSE));
    novo->info = novaMusica;
    novo->prox = NULL;
    return novo;
}

struct desc_LSE* criaDescritor(void) {
    struct desc_LSE *novoDesc = malloc(sizeof(struct desc_LSE));
    novoDesc->LSE = NULL;
    novoDesc->tamanho = 0;
    return novoDesc;
}

void insere(struct desc_LSE *lista, struct nodo_LSE *novo_elemento, int posicao) {
    if (lista->LSE == NULL || posicao <= 0) {
        novo_elemento->prox = lista->LSE;
        lista->LSE = novo_elemento;
    } else {
        struct nodo_LSE *aux = lista->LSE;
        int contador = 0;
        struct nodo_LSE *anterior = NULL;

        while (aux != NULL && contador < posicao) {
            anterior = aux;
            aux = aux->prox;
            contador++;
        }

        novo_elemento->prox = aux;
        if (anterior != NULL)
            anterior->prox = novo_elemento;
    }

    lista->tamanho++;
}

struct nodo_LSE* removeLista(struct desc_LSE *lista, int posicao) {
    if (lista->tamanho == 0 || posicao < 0 || posicao >= lista->tamanho) {
        printf("Posição inválida ou lista vazia!\n");
        return NULL;
    }

    struct nodo_LSE *removido;
    if (posicao == 0) {
        removido = lista->LSE;
        lista->LSE = lista->LSE->prox;
    } else {
        struct nodo_LSE *aux = lista->LSE;
        for (int i = 0; i < posicao - 1; i++) {
            aux = aux->prox;
        }
        removido = aux->prox;
        aux->prox = removido->prox;
    }

    lista->tamanho--;
    printf("Música removida com sucesso!\n");
    return removido;
}

void procurar(struct desc_LSE *lista, char nome[256]) {
    struct nodo_LSE *aux = lista->LSE;
    while (aux != NULL) {
        if (strcmp(aux->info->titulo, nome) == 0) {
            printf("Música encontrada!\n");
            printf("Título: %s\n", aux->info->titulo);
            printf("Artista: %s\n", aux->info->artista);
            printf("Letra: %s\n", aux->info->letra);
            printf("Código: %d\n", aux->info->codigo);
            printf("Execuções: %d\n", aux->info->execucoes);
            return;
        }
        aux = aux->prox;
    }
    printf("Música não encontrada.\n");
}

void imprime(struct desc_LSE *lista) {
    struct nodo_LSE *aux = lista->LSE;
    int i = 1;
    while (aux != NULL) {
        printf("\nMúsica %d:\n", i++);
        printf("Título: %s\n", aux->info->titulo);
        printf("Artista: %s\n", aux->info->artista);
        printf("Execuções: %d\n", aux->info->execucoes);
        aux = aux->prox;
    }
}

void criaListaComDados(struct desc_LSE *lista) {
    int qtd;

    printf("Quantas músicas deseja adicionar? ");
    scanf("%d", &qtd);
    setbuf(stdin, NULL);

    for (int i = 0; i < qtd; i++) {
        struct musica *m = malloc(sizeof(struct musica));

        printf("\nMúsica %d:\n", i + 1);
        printf("Título: ");
        fgets(m->titulo, sizeof(m->titulo), stdin);
        m->titulo[strcspn(m->titulo, "\n")] = '\0';

        printf("Artista: ");
        fgets(m->artista, sizeof(m->artista), stdin);
        m->artista[strcspn(m->artista, "\n")] = '\0';

        printf("Letra: ");
        fgets(m->letra, sizeof(m->letra), stdin);
        m->letra[strcspn(m->letra, "\n")] = '\0';

        printf("Código: ");
        scanf("%d", &m->codigo);
        setbuf(stdin, NULL);

        printf("Número de execuções: ");
        scanf("%d", &m->execucoes);
        setbuf(stdin, NULL);

        struct nodo_LSE *nodo = criaNodo(m);
        insere(lista, nodo, lista->tamanho); // insere no final
    }

    printf("\nLista criada com %d músicas!\n", lista->tamanho);
}

int main(void) {
    struct desc_LSE *lista = criaDescritor();
    int op;

    do {
        printf("\n--- MENU ---\n");
        printf("1 - Criar lista de músicas\n");
        printf("2 - Inserir uma nova música\n");
        printf("3 - Remover uma música da lista\n");
        printf("4 - Procurar por uma música\n");
        printf("5 - Imprimir lista de músicas\n");
        printf("0 - Encerrar\n");
        printf("Opção: ");
        scanf("%d", &op);
        setbuf(stdin, NULL);

        switch(op) {
            case 0:
                printf("Encerrando...\n");
                break;

            case 1:
                criaListaComDados(lista);
                break;

            case 2: {
                struct musica *m = malloc(sizeof(struct musica));
                int pos;

                printf("Título: ");
                fgets(m->titulo, sizeof(m->titulo), stdin);
                m->titulo[strcspn(m->titulo, "\n")] = '\0';

                printf("Artista: ");
                fgets(m->artista, sizeof(m->artista), stdin);
                m->artista[strcspn(m->artista, "\n")] = '\0';

                printf("Letra: ");
                fgets(m->letra, sizeof(m->letra), stdin);
                m->letra[strcspn(m->letra, "\n")] = '\0';

                printf("Código: ");
                scanf("%d", &m->codigo);
                setbuf(stdin, NULL);

                printf("Número de execuções: ");
                scanf("%d", &m->execucoes);
                setbuf(stdin, NULL);

                printf("Posição para inserir (0 a %d): ", lista->tamanho);
                scanf("%d", &pos);
                setbuf(stdin, NULL);

                struct nodo_LSE *novo = criaNodo(m);
                insere(lista, novo, pos);
                break;
            }

            case 3: {
                int pos;
                printf("Posição da música a remover: ");
                scanf("%d", &pos);
                setbuf(stdin, NULL);
                struct nodo_LSE *rem = removeLista(lista, pos);
                if (rem) free(rem->info);
                free(rem);
                break;
            }

            case 4: {
                char nome[256];
                printf("Digite o nome da música: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                procurar(lista, nome);
                break;
            }

            case 5:
                imprime(lista);
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (op != 0);

    return 0;
}
