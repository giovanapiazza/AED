#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Musicatad.h"

void liberaLista(struct desc_LDE *lista) {
    struct nodo_LDE *aux = lista->inicio;
    while (aux != NULL) {
        struct nodo_LDE *temp = aux;
        aux = aux->prox;
        free(temp->info);
        free(temp);
    }
    free(lista);
}

int main(void) {
    struct desc_LDE *lista = criaDescritor();
    if (!lista) {
        fprintf(stderr, "Erro ao criar lista!\n");
        return 1;
    }

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
                if (!m) break;

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

                struct nodo_LDE *novo = criaNodo(m);
                insere(lista, novo, pos);
                break;
            }

            case 3: {
                imprime(lista);
                int pos;
                printf("Posição da música a remover: ");
                scanf("%d", &pos);
                setbuf(stdin, NULL);
                struct nodo_LDE *rem = removeLista(lista, pos);
                if (rem) {
                    free(rem->info);
                    free(rem);
                }
                break;
            }

            case 4: {
                imprime(lista);
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

    liberaLista(lista);
    return 0;
}
