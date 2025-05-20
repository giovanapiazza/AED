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
