#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main() {
    int op, valor, controle = 0;
    descritorAvl *avl = NULL;

    do {
        printf("\n===== MENU AVL =====\n");
        printf("1- Criar AVL\n");
        printf("2- Remover uma chave\n");
        printf("3- Inserir uma chave\n");
        printf("4- Vizualizar arvore de forma inorder\n");
        printf("5- Visualizar arvore de forma preorder\n");
        printf("6- Finalizar programa\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
        case 1:
            if (controle == 0) {
                avl = Cria();
                printf("Árvore criada com sucesso!\n");
                controle = 1;
            } else {
                printf("Já existe uma árvore criada!\n");
            }
            break;

        case 2:
            if (controle != 0 && avl->raiz != NULL) {
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                avl->raiz = Remove(avl->raiz, valor);
                printf("Remoção concluída.\n");
            } else {
                printf("Crie a árvore e insira elementos primeiro!\n");
            }
            break;

        case 3:
            if (controle != 0) {
                printf("Digite um valor para inserir: ");
                scanf("%d", &valor);
                Insere(&(avl->raiz), valor);
                avl->raiz = Balanceamento(avl->raiz);
                printf("Valor inserido com sucesso!\n");
            } else {
                printf("Crie uma árvore primeiro!\n");
            }
            break;

        case 4:
            if (controle != 0 && avl->raiz != NULL) {
                printf("Inorder: ");
                Imprime_inorder(avl->raiz);
                printf("\n");
            } else {
                printf("Crie a árvore e insira elementos primeiro!\n");
            }
            break;

        case 5:
            if (controle != 0 && avl->raiz != NULL) {
                printf("Preorder: ");
                Imprime_preorder(avl->raiz);
                printf("\n");
            } else {
                printf("Crie a árvore e insira elementos primeiro!\n");
            }
            break;

        case 6:
            printf("Encerrando o programa...\n");
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }

    } while (op != 6);

    return 0;
}

