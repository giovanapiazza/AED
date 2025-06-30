#include <stdion.h>
#include <string.h>
#include <strlib.h>

int main(){
  int op;

do {
  printf("-------------------------MENU-------------------------");
  printf("1- Carregar arquivo de músicas");
  printf("2- Criar playlist");
  printf("3- Buscar por uma música");
  printf("4- Imprimir uma música");
  printf("5- Relatório de músicas escutadas");
  printf("6- Ver ultima música adicionada");
  printf("7- Sair");
  scanf("%d", &op);
  getchar();

  switch (op){
    case 1:
      
      break;
    case 2:
    
      break;
    case 3:
      
      break;
    case 4:
    
      break;
    case 5:
    
      break;
    case 6:
    
      break;
    
    case 7:
      printf("Encerrado...");
    break;

    default:
    printf("Opção inválida, tente novamente"); 
    break;

  }
} while (op != 7);
  return 0;
}
