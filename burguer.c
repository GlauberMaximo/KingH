#include<stdio.h> // funções de entrada e saida
#include<string.h> // Pra mexer com textos (palavras e frases)
#include<stdbool.h> // 'true' e 'false'

// ficha para guardar os itens que vai colocoar no carrinho
typedef struct {
    char nome[100]; // O nome do item
    char tamanho[50]; // O tamanho do item, se não tiver, fica vazio.
    float preco_unitario; // Quanto custa uma unidade desse item
    int quantidade; // Quantos desse item a gente quer
    float preco_total_do_item; // o preco_unitario * quantidade
} ItemDoCarrinho; // Nome da ficha

// --- Limites do nosso carrinho ---
#define MAXIMO_ITENS_NO_CARRINHO 50

// Função para mostrar tudo o que tem no carrinho
void mostrar_itens(ItemDoCarrinho* lista_de_itens, int quantos_itens_tem) {
    if (quantos_itens_tem == 0) { // Se não tiver nada na lista
        printf("Não tem nada pra mostrar aqui.\n");
        return; // Sai da função
    }

    // Mostra cada item da lista
    for (int i = 0; i < quantos_itens_tem; i++) {
        printf("- %d x %s", lista_de_itens[i].quantidade, lista_de_itens[i].nome);
        // Se tiver tamanho, mostra o tamanho
        if (strlen(lista_de_itens[i].tamanho) > 0) {
            printf(" %s", lista_de_itens[i].tamanho);
        }
        printf(" (R$ %.2f)\n", lista_de_itens[i].preco_total_do_item);
    }
}
int main(){
    // Onde a gente guarda as coisas do carrinho
    ItemDoCarrinho meu_carrinho[MAXIMO_ITENS_NO_CARRINHO]; // Aqui é onde a gente vai guardar as fichas dos itens
    int total_de_itens_no_carrinho = 0; // Quantos itens diferentes já estão no carrinho

    // Valores de taxas
    float TAXA_DE_ENTREGA = 5.90; // Um valor fixo pro serviço de entrega
    float VALOR_PRA_TER_DESCONTO = 100.00; // Se o pedido for maior que isso, tem desconto
    float PORCENTAGEM_DO_DESCONTO = 0.10; // O desconto é de 10% (0.10 é o mesmo que 10%)
    // Preços dos hamburgueres 
    float PRECO_MINI_KING = 10.90;
    float PRECO_PRINCE_BURGUER = 16.99;
    float PRECO_KING_SUPREMO = 22.99;
    // Preços das batatas
    float PRECO_BATATA_PEQUENA = 6.90;
    float PRECO_BATATA_MEDIA = 11.99;
    float PRECO_BATATA_GRANDE = 16.99;
    // Preços das bebidas
    float PRECO_REFRI_LATA = 4.90;
    float PRECO_REFRI_600ML = 6.49;
    float PRECO_REFRI_2LITROS = 12.99;

    // Variáveis que vamos usar para guardar coisas temporariamente
    char nome_do_item_temporario[100]; // Pra guardar o nome do item que o usuário escolher
    char tamanho_do_item_temporario[50]; // Pra guardar o tamanho
    float preco_unitario_temporario; // Pra guardar o preço de uma unidade

    int quantidade_digitada; // Pra guardar a quantidade que o usuário digitar
    char continuar_no_menu_principal = 's'; // Começa como 's' pra entrar no loop principal
    char continuar_no_submenu; // Pra controlar os submenus
    int escolha_menu_principal, escolha_cardapio, escolha_item, escolha_tamanho_bebida, escolha_carrinho;
    int escolha_forma_pagamento; // Pra guardar a escolha da forma de pagamento
    char nome_forma_pagamento[50]; // Pra guardar o nome da forma de pagamento

    // Menu Principal
    while (continuar_no_menu_principal == 's'){
        printf("\n--- Bem-vindo ao King Burguers ---\n");
        printf("1 - Ver o Cardapio\n");
        printf("2 - Ver meu Carrinho\n");
        printf("3 - Sair do Sistema\n");
        printf("-----------------------------------\n");
        printf("O que você quer fazer? Digite o número: ");
        scanf("%d", &escolha_menu_principal);
        printf("-----------------------------------\n");
        switch (escolha_menu_principal){
            case 1: // Ver o Cardapio
                continuar_no_submenu = 's';
                // Menu do cardápio
                while (continuar_no_submenu == 's'){
                    printf("\n--- Cardapio do King Burguers ---\n");
                    printf("1 - Hamburgueres\n");
                    printf("2 - Batatas\n");
                    printf("3 - Bebidas\n");
                    printf("4 - Voltar pro Menu Principal\n");
                    printf("-----------------------------------\n");
                    printf("Escolha o que você quer ver no cardápio: ");
                    scanf("%d", &escolha_cardapio);

                    switch (escolha_cardapio){
                        case 1: // Menu de Hamburgueres
                            printf("\n--- Nossos Hamburgueres --- \n");
                            printf("1 - Mini King\n");
                            printf("    Ingredientes: Pão tradicional, hambúrguer de carne 80g, queijo cheddar e maionese.\n");
                            printf("    Preço: R$ %.2f\n", PRECO_MINI_KING);
                            printf("2 - Prince Burguer\n");
                            printf("    Ingredientes: Pão brioche, hambúrguer de carne 120g, queijo prato, alface, tomate e molho especial.\n");
                            printf("    Preço: R$ %.2f\n", PRECO_PRINCE_BURGUER);
                            printf("3 - King Supremo \n");
                            printf("    Ingredientes: Pão australiano, dois hambúrgueres de carne 120g, queijo mussarela, bacon, cebola e maionese.\n");
                            printf("    Preço: R$ %.2f\n", PRECO_KING_SUPREMO);
                            printf("4 - Voltar\n");
                            printf("-----------------------------------\n");
                            printf("Escolha qual hamburguer você quer: ");
                            scanf("%d", &escolha_item);

                            preco_unitario_temporario = 0.0; // Zera o preço temporário
                            strcpy(tamanho_do_item_temporario, ""); // Deixa o tamanho vazio

                            switch (escolha_item){
                                case 1:
                                    strcpy(nome_do_item_temporario, "Mini King");
                                    preco_unitario_temporario = PRECO_MINI_KING;
                                    break;
                                case 2:
                                    strcpy(nome_do_item_temporario, "Prince Burguer");
                                    preco_unitario_temporario = PRECO_PRINCE_BURGUER;
                                    break;
                                case 3:
                                    strcpy(nome_do_item_temporario, "King Supremo");
                                    preco_unitario_temporario = PRECO_KING_SUPREMO;
                                    break;
                                case 4: // Volta ao cardápio
                                    printf("Voltando para as categorias do Cardápio...\n");
                                    continue; // Volta pro menu do cardápio
                                default:
                                    printf("Opção Inválida. Por favor, tente de novo.\n");
                                    continue; // Volta pro menu dos hamburgueres
                            }
                            
                            // Se o preço for maior que zero (quer dizer que escolheu um item válido)
                            if (preco_unitario_temporario > 0) {
                                printf("Quantos %s você quer?\n", nome_do_item_temporario);
                                scanf("%d", &quantidade_digitada);
                                if (quantidade_digitada > 0) { // Se a quantidade for válida
                                    if (total_de_itens_no_carrinho < MAXIMO_ITENS_NO_CARRINHO) {
                                        strcpy(meu_carrinho[total_de_itens_no_carrinho].nome, nome_do_item_temporario);
                                        strcpy(meu_carrinho[total_de_itens_no_carrinho].tamanho, tamanho_do_item_temporario);
                                        meu_carrinho[total_de_itens_no_carrinho].preco_unitario = preco_unitario_temporario;
                                        meu_carrinho[total_de_itens_no_carrinho].quantidade = quantidade_digitada;
                                        meu_carrinho[total_de_itens_no_carrinho].preco_total_do_item = preco_unitario_temporario * quantidade_digitada;
                                        
                                        total_de_itens_no_carrinho++;
                                        printf("Você adicionou: %d x %s %s (Custa: R$ %.2f).\n", quantidade_digitada, nome_do_item_temporario, (strlen(tamanho_do_item_temporario) > 0 ? tamanho_do_item_temporario : ""), (preco_unitario_temporario * quantidade_digitada));
                                    } else {
                                        printf("O carrinho está lotado! Não dá pra adicionar mais itens (só cabem %d tipos de itens).\n", MAXIMO_ITENS_NO_CARRINHO);
                                    }
                                } else {
                                    printf("Quantidade inválida. O item não foi adicionado.\n");
                                }
                                printf("Voltando ao cardápio...\n");
                            }
                            break; 
                        
                        case 2: // Menu de Batatas
                            printf("\n--- Nossas Batatas --- \n");
                            printf("1 - Batata Frita Pequena\n");
                            printf("    Preço: R$ %.2f\n", PRECO_BATATA_PEQUENA);
                            printf("2 - Batata Frita Media\n");
                            printf("    Preço: R$ %.2f\n", PRECO_BATATA_MEDIA);
                            printf("3 - Batata Frita Grande\n");
                            printf("    Preço: R$ %.2f\n", PRECO_BATATA_GRANDE);
                            printf("4 - Voltar\n");
                            printf("-----------------------------------\n");
                            printf("Escolha o tamanho da batata: ");
                            scanf("%d", &escolha_item);

                            preco_unitario_temporario = 0.0;
                            strcpy(nome_do_item_temporario, "Batata Frita"); // O nome base é sempre "Batata Frita"
                            
                            switch (escolha_item){
                                case 1:
                                    preco_unitario_temporario = PRECO_BATATA_PEQUENA;
                                    strcpy(tamanho_do_item_temporario, "Pequena");
                                    break;
                                case 2:
                                    preco_unitario_temporario = PRECO_BATATA_MEDIA;
                                    strcpy(tamanho_do_item_temporario, "Media");
                                    break;
                                case 3:
                                    preco_unitario_temporario = PRECO_BATATA_GRANDE;
                                    strcpy(tamanho_do_item_temporario, "Grande");
                                    break;
                                case 4: // Volta ao cardápio
                                    printf("Voltando para as categorias do Cardápio...\n");
                                    continue; // Volta pro menu do cardápio
                                default:
                                    printf("Opção Inválida. Por favor, tente de novo.\n");
                                    continue;
                            }

                            if (preco_unitario_temporario > 0) {
                                printf("Quantas Batatas Fritas %s você quer?\n", tamanho_do_item_temporario);
                                scanf("%d", &quantidade_digitada);
                                if (quantidade_digitada > 0) {
                                    if (total_de_itens_no_carrinho < MAXIMO_ITENS_NO_CARRINHO) {
                                        strcpy(meu_carrinho[total_de_itens_no_carrinho].nome, nome_do_item_temporario);
                                        strcpy(meu_carrinho[total_de_itens_no_carrinho].tamanho, tamanho_do_item_temporario);
                                        meu_carrinho[total_de_itens_no_carrinho].preco_unitario = preco_unitario_temporario;
                                        meu_carrinho[total_de_itens_no_carrinho].quantidade = quantidade_digitada;
                                        meu_carrinho[total_de_itens_no_carrinho].preco_total_do_item = preco_unitario_temporario * quantidade_digitada;
                                        
                                        total_de_itens_no_carrinho++;
                                        printf("Você adicionou: %d x %s %s (Custa: R$ %.2f).\n", quantidade_digitada, nome_do_item_temporario, tamanho_do_item_temporario, (preco_unitario_temporario * quantidade_digitada));
                                    } else {
                                        printf("O carrinho está lotado! Não dá pra adicionar mais itens (só cabem %d tipos de itens).\n", MAXIMO_ITENS_NO_CARRINHO);
                                    }
                                } else {
                                    printf("Quantidade inválida. O item não foi adicionado.\n");
                                }
                                printf("Voltando ao cardápio...\n");
                            }
                            break;
                            
                        case 3: // Menu de Bebidas
                            printf("\n--- Nossas Bebidas ---\n");
                            printf("1 - Coca-Cola\n");
                            printf("2 - Pepsi\n");
                            printf("3 - Guaraná Antartica\n");
                            printf("4 - Voltar\n");
                            printf("-----------------------------------\n");
                            printf("Escolha uma bebida: ");
                            scanf("%d", &escolha_item);

                            preco_unitario_temporario = 0.0;
                            strcpy(tamanho_do_item_temporario, "");

                            if (escolha_item >= 1 && escolha_item <= 3) {
                                if (escolha_item == 1) strcpy(nome_do_item_temporario, "Coca-Cola");//if reduzido
                                else if (escolha_item == 2) strcpy(nome_do_item_temporario, "Pepsi");//elseif reduzido
                                else strcpy(nome_do_item_temporario, "Guaraná Antartica");//else reduzido

                                printf("\nVocê escolheu %s.\n", nome_do_item_temporario);
                                printf("--- Escolha o Tamanho para %s ---\n", nome_do_item_temporario);
                                printf("1 - Lata (310ml) - R$ %.2f\n", PRECO_REFRI_LATA);
                                printf("2 - 600ml - R$ %.2f\n", PRECO_REFRI_600ML);
                                printf("3 - 2 Litros - R$ %.2f\n", PRECO_REFRI_2LITROS);
                                printf("4 - Voltar para escolha de bebida\n");
                                printf("-----------------------------------\n");
                                printf("Escolha o tamanho: ");
                                scanf("%d", &escolha_tamanho_bebida);
                                
                                switch (escolha_tamanho_bebida){
                                    case 1:
                                        preco_unitario_temporario = PRECO_REFRI_LATA;
                                        strcpy(tamanho_do_item_temporario, "310ml");
                                        break;
                                    case 2:
                                        preco_unitario_temporario = PRECO_REFRI_600ML;
                                        strcpy(tamanho_do_item_temporario, "600ml");
                                        break;
                                    case 3:
                                        preco_unitario_temporario = PRECO_REFRI_2LITROS;
                                        strcpy(tamanho_do_item_temporario, "2 Litros");
                                        break;
                                    case 4:
                                        printf("Voltando para as opções de bebidas...\n");
                                        continue;
                                    default:
                                        printf("Opção de tamanho inválida.\n");
                                        continue;
                                }
                                
                                if (preco_unitario_temporario > 0) {
                                    printf("Quantas %s %s você quer?\n", nome_do_item_temporario, tamanho_do_item_temporario);
                                    scanf("%d", &quantidade_digitada);
                                    if (quantidade_digitada > 0) {
                                        if (total_de_itens_no_carrinho < MAXIMO_ITENS_NO_CARRINHO) {
                                            strcpy(meu_carrinho[total_de_itens_no_carrinho].nome, nome_do_item_temporario);
                                            strcpy(meu_carrinho[total_de_itens_no_carrinho].tamanho, tamanho_do_item_temporario);
                                            meu_carrinho[total_de_itens_no_carrinho].preco_unitario = preco_unitario_temporario;
                                            meu_carrinho[total_de_itens_no_carrinho].quantidade = quantidade_digitada;
                                            meu_carrinho[total_de_itens_no_carrinho].preco_total_do_item = preco_unitario_temporario * quantidade_digitada;
                                            
                                            total_de_itens_no_carrinho++;
                                            printf("Você adicionou: %d x %s %s (Custa: R$ %.2f).\n", quantidade_digitada, nome_do_item_temporario, tamanho_do_item_temporario, (preco_unitario_temporario * quantidade_digitada));
                                        } else {
                                            printf("O carrinho está lotado! Não dá pra adicionar mais itens (só cabem %d tipos de itens).\n", MAXIMO_ITENS_NO_CARRINHO);
                                        }
                                    } else {
                                        printf("Quantidade inválida. O item não foi adicionado.\n");
                                    }
                                    printf("Voltando ao cardápio...\n");
                                }

                            } else if (escolha_item == 4) {
                                printf("Voltando para as categorias do Cardápio...\n");
                            } else {
                                printf("Opção Inválida. Por favor, tente de novo.\n");
                            }
                            break;

                        case 4: // Voltar ao Menu Principal (do Cardápio)
                            printf("Voltando para o Menu Principal...\n");
                            continuar_no_submenu = 'n'; // Sai do loop do cardápio
                            break;
                        default:
                            printf("Opção de Cardápio Inválida. Por favor, tente de novo.\n");
                    }
                }
                break; 
            
            case 2: // Ver meu Carrinho
                printf("\n--- Seu Carrinho de Compras ---\n");
                if (total_de_itens_no_carrinho == 0) { // Se o carrinho estiver vazio
                    printf("Você ainda não escolheu nenhum item do cardápio.\n");
                } else {
                    printf("Os itens no seu carrinho são:\n");
                    mostrar_itens(meu_carrinho, total_de_itens_no_carrinho); // Mostra os itens do carrinho

                    float subtotal_carrinho_atual = 0.0;
                    for (int i = 0; i < total_de_itens_no_carrinho; i++) { // Valor sem taxa
                        subtotal_carrinho_atual += meu_carrinho[i].preco_total_do_item;
                    }

                    float valor_com_servico_carrinho_atual = subtotal_carrinho_atual + TAXA_DE_ENTREGA;
                    float valor_desconto_carrinho_atual = 0.0; // Começa com zero
                    float valor_final_carrinho_atual = valor_com_servico_carrinho_atual; // Começa com o valor sem desconto
                    
                    printf("\nPreço total dos produtos: R$ %.2f\n", subtotal_carrinho_atual);
                    printf("Taxa de Entrega: R$ %.2f\n", TAXA_DE_ENTREGA);

                    // Mensagem de desconto
                    if (subtotal_carrinho_atual < VALOR_PRA_TER_DESCONTO) {
                        printf("Adicione mais R$ %.2f em produtos para ganhar 10%% de desconto!\n", VALOR_PRA_TER_DESCONTO - subtotal_carrinho_atual);
                    }

                    // Verifica se o subtotal é maior que o valor para ter desconto
                    if (subtotal_carrinho_atual > VALOR_PRA_TER_DESCONTO) {
                        valor_desconto_carrinho_atual = subtotal_carrinho_atual * PORCENTAGEM_DO_DESCONTO;
                        valor_final_carrinho_atual = valor_com_servico_carrinho_atual - valor_desconto_carrinho_atual;
                        printf("Você ganhou um DESCONTO de 10%%! (Economia de R$ %.2f)\n", valor_desconto_carrinho_atual);
                    }
                    
                    printf("Total a Pagar (com taxa e desconto se tiver): R$ %.2f\n", valor_final_carrinho_atual);

                    printf("\nComo deseja prosseguir?\n");
                    printf("1 - Limpar o carrinho\n");
                    printf("2 - Prosseguir com a compra\n");
                    printf("3 - Voltar para o menu principal\n");
                    printf("-----------------------------------\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &escolha_carrinho);

                    switch(escolha_carrinho){
                        case 1: // Limpar Carrinho
                            total_de_itens_no_carrinho = 0; // Coloca o contador de itens no carrinho pra zero
                            printf("Seu carrinho está vazio agora.\n");
                            break;
                        case 2: // Finalizar Compra
                            if (total_de_itens_no_carrinho == 0) {
                                printf("Seu carrinho está vazio! Adicione itens antes de fechar a compra.\n");
                            } else {
                                printf("\n--- Escolha a Forma de Pagamento ---\n");
                                printf("1 - Dinheiro\n");
                                printf("2 - Cartão de Crédito\n");
                                printf("3 - Pix\n");
                                printf("------------------------------------\n");
                                printf("Escolha uma opção de pagamento: ");
                                scanf("%d", &escolha_forma_pagamento);

                                switch(escolha_forma_pagamento){
                                    case 1:
                                        strcpy(nome_forma_pagamento, "Dinheiro");
                                        break;
                                    case 2:
                                        strcpy(nome_forma_pagamento, "Cartão de Crédito");
                                        break;
                                    case 3:
                                        strcpy(nome_forma_pagamento, "Pix");
                                        break;
                                    default:
                                        printf("Opção de pagamento inválida. Voltando ao carrinho.\n");
                                        // Não finaliza a compra se a opção de pagamento for inválida
                                        continue; 
                                }

                                printf("\nParabéns! Sua compra foi finalizada com sucesso!\n");
                                printf("--- NOTA FISCAL SIMPLES ---\n");
                                printf("King Burguers - Seu Lanche na Hora!\n");
                                printf("-----------------------------------\n");
                                printf("Itens do Pedido:\n");
                                mostrar_itens(meu_carrinho, total_de_itens_no_carrinho); // Mostra os itens do pedido
                                printf("\nSubtotal dos produtos: R$ %.2f\n", subtotal_carrinho_atual);
                                printf("Taxa de Entrega: R$ %.2f\n", TAXA_DE_ENTREGA);
                                if (valor_desconto_carrinho_atual > 0) {
                                    printf("Desconto Aplicado (10%%): -R$ %.2f\n", valor_desconto_carrinho_atual);
                                }
                                printf("-----------------------------------\n");
                                printf("Total Final: R$ %.2f\n", valor_final_carrinho_atual);
                                printf("Forma de Pagamento: %s\n", nome_forma_pagamento);
                                printf("-----------------------------------\n");
                                printf("Agradecemos a preferência! Volte sempre!\n");
                                
                                total_de_itens_no_carrinho = 0; // Esvazia o carrinho após a compra
                            }
                            break;
                        case 3: // Voltar ao Menu Principal
                            printf("Voltando para o Menu Principal...\n");
                            break;
                        default:
                            printf("Opção Inválida. Por favor, tente de novo.\n");
                            break;
                    }
                }
                break;

            case 3:
                printf("Fechando o sistema King Burguers. Obrigado pela sua visita!\n");
                continuar_no_menu_principal = 'n';
                break;
            default: // Opção não existente
                printf("Opção Inválida. Por favor, escolha um número de 1 a 3.\n");
                break;
        }
    }
    return 0;