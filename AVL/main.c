#include <stdio.h>


int main(){
  int op, valor, controle=0;
	
	descritorAvl *avl=NULL;
	Arv *aux=NULL;

do {
  printf("Escolha uma opção\n");
  printf("1- Criar AVL\n");
  printf("2- Remover uma chave\n");
  printf("3- Inserir uma chave\n");
  printf("4- Vizualizar arvore de forma inorder\n");
  printf("5- Visualizar arvore de formar preorder\n");
  printf("6- Finalizar programa\n");
  scanf("%d", &op);
  getchar();

   switch (op) {
      case 1:
        f(controle==0){
	    			avl=Cria();
	    			printf("Arvore criada com sucesso\n");
	    			controle++;
	    		}
	    		else{
	    			printf("Já existe uma arvore criada\n");
	    		}
	    		break;

      case 2:
        f(controle!=0){
	    			printf("Digite um valor para inserir\n");
	    			scanf("%d",&valor);
	    			Insere(&(avl->raiz),valor);
	    			avl->raiz=Balanceamento(avl->raiz);
	    			printf("Valor adicionado com sucesso\n");
	    		}
	    		else{
	    			printf("Crie uma arvore primeiro\n");
	    		}
	    		break;

      case 3:
        if(avl->raiz!=NULL && controle!=0){
	    			printf("Pre order= ");
		    		Imprime_preorder(avl->raiz);
		    		printf("\nIn order= ");
	    			Imprime_inorder(avl->raiz);
	    			printf("\nPos order= ");
	    			Imprime_posorder(avl->raiz);
	    			printf("\n");
	    		}
	    		else
                {
                    printf("Crie uma arvore primeiro ou adicione uma valor a arvore\n");
                }
           break;
      case 4:
        if(controle!=0){
						Imprime_inorder(Arv *no);
					}
					else{
						printf("Crie uma arvore primeiro\n");
					}
            break;
      case 5: 
        if(controle!=0){
						Imprime_preorder(Arv *no);
					}
					else{
						printf("Crie uma arvore primeiro\n");
					}
      break;
      case 6: 
        printf("O programa esta sendo encerrado\n");
      break;
      default:
      printf("A opção está invalida\n");
      printf("Por favor tente novamente\n");
      break;
   }
} while(op!=6);

return 0;
}

