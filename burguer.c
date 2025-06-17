#include<stdio.h>
#include <string.h> // Inclua esta biblioteca para usar strcpy
int main(){
    char b2[100], b3[100]; //nome dos hamburguers
    char b1[100];
    //float v1, v2, v3; //valores hamburguers
    //int qtd; //quantidade geral
    char c1, c2; //condições para while
    int op1, op2; // variáveis para os switch cases

    while (c1 = 's'){
        printf("\nCardápio\n");
        printf("1 - Hamburguers\n");
        printf("2 - Bebidas\n");
        printf("3 - Batata\n");
        printf("4 - Carrinho\n");
        printf("5 - Fechar Cardapio\n");
        scanf("%d", &op1);
        printf("-----------------------------------\n");

        
        

         switch (op1){
            case 1:
                c2 = 's';
                while (c2 = 's'){
                    printf("Opcoes de Hamburguers\n");
                    printf("1 - Mini King\n");
                    printf("2 - Prince Burguer\n");
                    printf("3 - King Supremo \n");
                    printf("4 - Voltar");
                    scanf("%d", &op2);

                    switch (op2){
                        case 1:
                            printf("Mini King\n");
                            // Use strcpy para copiar a string "Mini King" para b1
                            strcpy(b1, "Mini King");
                            printf("Você selecionou: %s\n", b1);
                            printf("");
                            break;
                        case 2:

                            break;
                        case 3:

                            break;
                        case 4:
                            c1 = 'n';
                            printf("Voltando...\n");
                            break;
                        default:
                            printf("Opcao Inválida");
                    }
                }
                

                break;
            case 2:
                printf("Opcoes de Bebidas\n");
                break;
            case 3:
                printf("Opcoes de Batata\n");
                break;
            case 4:
                printf("Carrinho\n");
                break;
            case 5:
                printf("Fechando sistema...\n");
                c1 = 'n';
                break;
            default:
                printf("Opção Inválida \n");
        }

        return 0;
    }
    return 0;
}