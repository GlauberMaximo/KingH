#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// --- Definição da Estrutura para um Item do Carrinho ---
typedef struct {
    char nome[100];
    char tamanho[50]; // Para bebidas (ex: "310ml") ou batatas (ex: "Pequena"). Vazio para hambúrgueres.
    float valor_unitario;
    int quantidade;
    float valor_total_item; // valor_unitario * quantidade
} ItemCarrinho;

// --- Constantes para o Tamanho Máximo do Carrinho ---
#define MAX_ITENS_CARRINHO 50 // Capacidade máxima de itens diferentes no carrinho

// --- Variáveis Globais para o Carrinho e Status do Pedido ---
ItemCarrinho carrinho[MAX_ITENS_CARRINHO]; // O array que guarda todos os itens adicionados
int num_itens_carrinho = 0;              // Contador de itens atualmente no carrinho

// Constantes de valores fixos
const float TAXA_SERVICO = 5.90;
const float VALOR_DESCONTO_MINIMO = 100.00;
const float PORCENTAGEM_DESCONTO = 0.20; // 20%

// --- Variáveis Globais para Confirmação do Pedido e Resumo Final ---
bool pedido_confirmado = false; // Indica se a compra foi finalizada

// Array para guardar o estado do pedido no momento da confirmação (cópia do carrinho)
ItemCarrinho pedido_final[MAX_ITENS_CARRINHO];
int num_itens_pedido_final = 0; // Contador de itens no pedido final
float pedido_final_subtotal = 0.0;
float pedido_final_servico = 0.0;
float pedido_final_desconto = 0.0;
float pedido_final_total = 0.0;


// --- Função para limpar o buffer de entrada ---
void limpar_buffer() {
    while (getchar() != '\n' && getchar() != EOF);
}

// --- Função para adicionar um item ao carrinho ---
void adicionar_item_carrinho(const char* nome, const char* tamanho, float valor_unitario, int qtd) {
    if (num_itens_carrinho < MAX_ITENS_CARRINHO) {
        strcpy(carrinho[num_itens_carrinho].nome, nome);
        strcpy(carrinho[num_itens_carrinho].tamanho, tamanho);
        carrinho[num_itens_carrinho].valor_unitario = valor_unitario;
        carrinho[num_itens_carrinho].quantidade = qtd;
        carrinho[num_itens_carrinho].valor_total_item = valor_unitario * qtd;
        
        num_itens_carrinho++;
        printf("Item Adicionado: %d x %s %s (Total: R$ %.2f).\n", qtd, nome, (strlen(tamanho) > 0 ? tamanho : ""), (valor_unitario * qtd));
    } else {
        printf("Carrinho cheio! Não é possível adicionar mais itens (limite de %d itens diferentes).\n", MAX_ITENS_CARRINHO);
    }
    pedido_confirmado = false; // Invalida o pedido confirmado anterior ao adicionar novo item
}

// --- Função para calcular o subtotal atual do carrinho ---
float calcular_subtotal_carrinho() {
    float subtotal = 0.0;
    for (int i = 0; i < num_itens_carrinho; i++) {
        subtotal += carrinho[i].valor_total_item;
    }
    return subtotal;
}

// --- Função para exibir os detalhes do carrinho/pedido ---
void exibir_carrinho_detalhes(bool eh_pedido_final) {
    ItemCarrinho* lista_itens;
    int num_itens;

    if (eh_pedido_final) {
        lista_itens = pedido_final;
        num_itens = num_itens_pedido_final;
    } else {
        lista_itens = carrinho;
        num_itens = num_itens_carrinho;
    }

    if (num_itens == 0) {
        printf("Nenhum item para exibir.\n");
        return;
    }

    for (int i = 0; i < num_itens; i++) {
        printf("- %d x %s", lista_itens[i].quantidade, lista_itens[i].nome);
        if (strlen(lista_itens[i].tamanho) > 0) {
            printf(" %s", lista_itens[i].tamanho);
        }
        printf(" (R$ %.2f)\n", lista_itens[i].valor_total_item);
    }
}

// --- Função para limpar todo o carrinho ---
void limpar_carrinho_completo() {
    num_itens_carrinho = 0;
    // Não alteramos pedido_confirmado aqui, pois limpar o carrinho atual não afeta o pedido já confirmado.
    // Ele só seria invalidado se novos itens fossem adicionados ao carrinho.
    printf("Carrinho limpo.\n");
}


int main(){
    // Valores unitários dos hamburgueres
    const float V_MINI_KING = 10.90;
    const float V_PRINCE_BURGUER = 16.99;
    const float V_KING_SUPREMO = 22.99;

    // Valores unitários para Batatas
    const float V_BATATA_PEQUENA = 6.90;
    const float V_BATATA_MEDIA = 11.99;
    const float V_BATATA_GRANDE = 16.99;

    // Valores unitários para Bebidas por tipo e tamanho
    const float V_COCA_LATA = 4.90;
    const float V_COCA_600ML = 6.49;
    const float V_COCA_2LITROS = 12.99;
    const float V_PEPSI_LATA = 4.90;
    const float V_PEPSI_600ML = 6.49;
    const float V_PEPSI_2LITROS = 12.99;
    const float V_GUARANA_LATA = 4.90;
    const float V_GUARANA_600ML = 6.49;
    const float V_GUARANA_2LITROS = 12.99;

    // Variáveis locais para uso temporário
    char temp_nome_item[100];
    char temp_tamanho_item[50];
    float temp_valor_unitario;

    int qtd;
    char c1 = 's';
    char c_submenu;
    int op_principal, op_cardapio, op_item, op_tamanho_bebida, op_carrinho;

    while (c1 == 's'){
        printf("\n--- Bem-vindo ao King Burguers ---\n");
        printf("1 - Acessar Cardapio\n");
        printf("2 - Visualizar Carrinho\n");
        printf("3 - Visualizar Pedido\n");
        printf("4 - Fechar sistema\n");
        printf("-----------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op_principal);
        limpar_buffer();

        printf("-----------------------------------\n");
        
        switch (op_principal){
            case 1: // Acessar Cardapio
                c_submenu = 's';
                while (c_submenu == 's'){
                    printf("\n--- Cardapio King Burguers ---\n");
                    printf("1 - Hamburguers\n");
                    printf("2 - Batata\n");
                    printf("3 - Bebidas\n");
                    printf("4 - Voltar ao Menu Principal\n");
                    printf("-----------------------------------\n");
                    printf("Escolha uma categoria: ");
                    scanf("%d", &op_cardapio);
                    limpar_buffer();

                    switch (op_cardapio){
                        case 1: // Menu de Hamburguers
                            printf("\n--- Opções de Hamburguers ---\n");
                            printf("1 - Mini King\n");
                            printf("    Ingredientes: Pão tradicional, hambúrguer de carne 80g, queijo cheddar e maionese.\n");
                            printf("    Valor: R$ %.2f\n", V_MINI_KING);
                            printf("2 - Prince Burguer\n");
                            printf("    Ingredientes: Pão brioche, hambúrguer de carne 120g, queijo prato, alface, tomate e molho especial.\n");
                            printf("    Valor: R$ %.2f\n", V_PRINCE_BURGUER);
                            printf("3 - King Supremo \n");
                            printf("    Ingredientes: Pão australiano, dois hambúrgueres de carne 120g, queijo mussarela, bacon, cebola e maionese.\n");
                            printf("    Valor: R$ %.2f\n", V_KING_SUPREMO);
                            printf("4 - Voltar\n");
                            printf("-----------------------------------\n");
                            printf("Escolha um hamburguer: ");
                            scanf("%d", &op_item);
                            limpar_buffer();

                            temp_valor_unitario = 0.0;
                            strcpy(temp_tamanho_item, "");

                            switch (op_item){
                                case 1:
                                    strcpy(temp_nome_item, "Mini King");
                                    temp_valor_unitario = V_MINI_KING;
                                    break;
                                case 2:
                                    strcpy(temp_nome_item, "Prince Burguer");
                                    temp_valor_unitario = V_PRINCE_BURGUER;
                                    break;
                                case 3:
                                    strcpy(temp_nome_item, "King Supremo");
                                    temp_valor_unitario = V_KING_SUPREMO;
                                    break;
                                case 4:
                                    printf("Voltando ao Cardápio King Burguers...\n");
                                    continue;
                                default:
                                    printf("Opcao Inválida. Tente novamente.\n");
                                    continue;
                            }
                            
                            if (temp_valor_unitario > 0) {
                                printf("Qual a quantidade desejada de %s?\n", temp_nome_item);
                                scanf("%d", &qtd);
                                limpar_buffer();
                                if (qtd > 0) {
                                    adicionar_item_carrinho(temp_nome_item, temp_tamanho_item, temp_valor_unitario, qtd);
                                } else {
                                    printf("Quantidade inválida. Item não adicionado.\n");
                                }
                                printf("Voltando ao cardápio...\n");
                            }
                            break; 
                        
                        case 2: // Menu de Batatas
                            printf("\n--- Opções de Batatas ---\n");
                            printf("1 - Batata Frita Pequena\n");
                            printf("    Valor: R$ %.2f\n", V_BATATA_PEQUENA);
                            printf("2 - Batata Frita Media\n");
                            printf("    Valor: R$ %.2f\n", V_BATATA_MEDIA);
                            printf("3 - Batata Frita Grande\n");
                            printf("    Valor: R$ %.2f\n", V_BATATA_GRANDE);
                            printf("4 - Voltar\n");
                            printf("-----------------------------------\n");
                            printf("Escolha o tamanho da batata: ");
                            scanf("%d", &op_item);
                            limpar_buffer();

                            temp_valor_unitario = 0.0;
                            strcpy(temp_nome_item, "Batata Frita");
                            
                            switch (op_item){
                                case 1:
                                    temp_valor_unitario = V_BATATA_PEQUENA;
                                    strcpy(temp_tamanho_item, "Pequena");
                                    break;
                                case 2:
                                    temp_valor_unitario = V_BATATA_MEDIA;
                                    strcpy(temp_tamanho_item, "Media");
                                    break;
                                case 3:
                                    temp_valor_unitario = V_BATATA_GRANDE;
                                    strcpy(temp_tamanho_item, "Grande");
                                    break;
                                case 4:
                                    printf("Voltando ao Cardápio King Burguers...\n");
                                    continue;
                                default:
                                    printf("Opcao Inválida. Tente novamente.\n");
                                    continue;
                            }

                            if (temp_valor_unitario > 0) {
                                printf("Qual a quantidade desejada de Batata Frita %s?\n", temp_tamanho_item);
                                scanf("%d", &qtd);
                                limpar_buffer();
                                if (qtd > 0) {
                                    adicionar_item_carrinho(temp_nome_item, temp_tamanho_item, temp_valor_unitario, qtd);
                                } else {
                                    printf("Quantidade inválida. Item não adicionado.\n");
                                }
                                printf("Voltando ao cardápio...\n");
                            }
                            break;
                            
                        case 3: // Menu de Bebidas
                            printf("\n--- Opções de Bebidas ---\n");
                            printf("1 - Coca-Cola\n");
                            printf("    Tamanhos: 310 ml (R$ %.2f), 600 ml (R$ %.2f), 2 Litros (R$ %.2f)\n", V_COCA_LATA, V_COCA_600ML, V_COCA_2LITROS);
                            printf("2 - Pepsi\n");
                            printf("    Tamanhos: 310 ml (R$ %.2f), 600 ml (R$ %.2f), 2 Litros (R$ %.2f)\n", V_PEPSI_LATA, V_PEPSI_600ML, V_PEPSI_2LITROS);
                            printf("3 - Guaraná Antartica\n");
                            printf("    Tamanhos: 310 ml (R$ %.2f), 600 ml (R$ %.2f), 2 Litros (R$ %.2f)\n", V_GUARANA_LATA, V_GUARANA_600ML, V_GUARANA_2LITROS);
                            printf("4 - Voltar\n");
                            printf("-----------------------------------\n");
                            printf("Escolha uma bebida: ");
                            scanf("%d", &op_item);
                            limpar_buffer();

                            temp_valor_unitario = 0.0;
                            strcpy(temp_tamanho_item, "");

                            if (op_item >= 1 && op_item <= 3) {
                                if (op_item == 1) strcpy(temp_nome_item, "Coca-Cola");
                                else if (op_item == 2) strcpy(temp_nome_item, "Pepsi");
                                else strcpy(temp_nome_item, "Guaraná Antartica");

                                printf("\nVocê selecionou %s.\n", temp_nome_item);
                                printf("--- Escolha o Tamanho para %s ---\n", temp_nome_item);
                                printf("1 - Lata (310ml) - R$ %.2f\n", (op_item == 1 ? V_COCA_LATA : (op_item == 2 ? V_PEPSI_LATA : V_GUARANA_LATA)));
                                printf("2 - 600ml - R$ %.2f\n", (op_item == 1 ? V_COCA_600ML : (op_item == 2 ? V_PEPSI_600ML : V_GUARANA_600ML)));
                                printf("3 - 2 Litros - R$ %.2f\n", (op_item == 1 ? V_COCA_2LITROS : (op_item == 2 ? V_PEPSI_2LITROS : V_GUARANA_2LITROS)));
                                printf("4 - Voltar para escolha de bebida\n");
                                printf("-----------------------------------\n");
                                printf("Escolha o tamanho: ");
                                scanf("%d", &op_tamanho_bebida);
                                limpar_buffer();
                                
                                switch (op_tamanho_bebida){
                                    case 1:
                                        temp_valor_unitario = (op_item == 1 ? V_COCA_LATA : (op_item == 2 ? V_PEPSI_LATA : V_GUARANA_LATA));
                                        strcpy(temp_tamanho_item, "310ml");
                                        break;
                                    case 2:
                                        temp_valor_unitario = (op_item == 1 ? V_COCA_600ML : (op_item == 2 ? V_PEPSI_600ML : V_GUARANA_600ML));
                                        strcpy(temp_tamanho_item, "600ml");
                                        break;
                                    case 3:
                                        temp_valor_unitario = (op_item == 1 ? V_COCA_2LITROS : (op_item == 2 ? V_PEPSI_2LITROS : V_GUARANA_2LITROS));
                                        strcpy(temp_tamanho_item, "2 Litros");
                                        break;
                                    case 4:
                                        printf("Voltando às opções de bebidas...\n");
                                        continue;
                                    default:
                                        printf("Opcao de tamanho inválida.\n");
                                        continue;
                                }
                                
                                if (temp_valor_unitario > 0) {
                                    printf("Qual a quantidade desejada de %s %s?\n", temp_nome_item, temp_tamanho_item);
                                    scanf("%d", &qtd);
                                    limpar_buffer();
                                    if (qtd > 0) {
                                        adicionar_item_carrinho(temp_nome_item, temp_tamanho_item, temp_valor_unitario, qtd);
                                    } else {
                                        printf("Quantidade inválida. Item não adicionado.\n");
                                    }
                                    printf("Voltando ao cardápio...\n");
                                }

                            } else if (op_item == 4) {
                                printf("Voltando ao Cardápio King Burguers...\n");
                            } else {
                                printf("Opcao Inválida. Tente novamente.\n");
                            }
                            break;

                        case 4: // Voltar ao Menu Principal (do Cardápio)
                            printf("Voltando ao Menu Principal...\n");
                            c_submenu = 'n'; 
                            break;
                        default:
                            printf("Opção de Cardápio Inválida. Tente novamente.\n");
                    }
                }
                break; 
            
            case 2: // Visualizar Carrinho
                printf("\n--- Carrinho de Compras ---\n");
                if (num_itens_carrinho == 0) {
                    printf("Não foi selecionado nenhum item do cardápio.\n");
                } else {
                    printf("Itens no seu carrinho:\n");
                    exibir_carrinho_detalhes(false);

                    float subtotal_carrinho = calcular_subtotal_carrinho();
                    float valor_com_servico_carrinho = subtotal_carrinho + TAXA_SERVICO;
                    float valor_desconto_carrinho = 0.0;
                    float valor_final_carrinho = valor_com_servico_carrinho;
                    
                    printf("\nSubtotal dos produtos: R$ %.2f\n", subtotal_carrinho);
                    printf("Taxa de Serviço: R$ %.2f\n", TAXA_SERVICO);

                    if (subtotal_carrinho > VALOR_DESCONTO_MINIMO) {
                        valor_desconto_carrinho = subtotal_carrinho * PORCENTAGEM_DESCONTO;
                        valor_final_carrinho = valor_com_servico_carrinho - valor_desconto_carrinho;
                        printf("DESCONTO de 20%% aplicado! (R$ %.2f)\n", valor_desconto_carrinho);
                    }
                    
                    printf("Total a Pagar (incl. serviço e desconto): R$ %.2f\n", valor_final_carrinho);

                    printf("\nOpções do Carrinho:\n");
                    printf("1 - Limpar Carrinho (Deletar todos os itens)\n");
                    printf("2 - Finalizar Compra\n");
                    printf("3 - Voltar ao Menu Principal\n");
                    printf("-----------------------------------\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &op_carrinho);
                    limpar_buffer();

                    switch(op_carrinho){
                        case 1: // Limpar Carrinho
                            limpar_carrinho_completo();
                            break;
                        case 2: // Finalizar Compra
                            if (num_itens_carrinho == 0) {
                                printf("Carrinho vazio! Adicione itens antes de finalizar a compra.\n");
                            } else {
                                printf("\nCompra finalizada com sucesso! Seu pedido foi confirmado.\n");
                                pedido_confirmado = true;
                                
                                // --- CORREÇÃO APLICADA AQUI ---
                                // 1. Resetar o contador de itens do pedido final antes de copiar
                                num_itens_pedido_final = 0; 
                                // 2. Copiar CADA item do carrinho para o pedido_final
                                for(int i = 0; i < num_itens_carrinho; i++){
                                    pedido_final[i] = carrinho[i]; // Copia a struct completa
                                    num_itens_pedido_final++; // Incrementa para cada item copiado
                                }
                                // 3. Armazenar os valores calculados no momento da confirmação
                                pedido_final_subtotal = subtotal_carrinho;
                                pedido_final_servico = TAXA_SERVICO;
                                pedido_final_desconto = valor_desconto_carrinho;
                                pedido_final_total = valor_final_carrinho;

                                // Após a compra, limpamos o carrinho atual
                                limpar_carrinho_completo(); 
                            }
                            break;
                        case 3: // Voltar ao Menu Principal
                            printf("Voltando ao Menu Principal...\n");
                            break;
                        default:
                            printf("Opção Inválida. Tente novamente.\n");
                            break;
                    }
                }
                break;

            case 3: // Visualizar Pedido
                printf("\n--- Resumo do Pedido ---\n");
                // Verificar se o pedido foi confirmado E se há itens para exibir no pedido final
                if (!pedido_confirmado || num_itens_pedido_final == 0) { 
                    printf("Nenhum pedido foi confirmado ainda ou o pedido está vazio. Por favor, finalize sua compra no Carrinho.\n");
                } else {
                    printf("Seu último pedido confirmado:\n");
                    exibir_carrinho_detalhes(true); // Exibe os itens do pedido final

                    printf("\nValor dos Produtos: R$ %.2f\n", pedido_final_subtotal);
                    printf("Serviço: R$ %.2f\n", pedido_final_servico);
                    
                    if (pedido_final_desconto > 0) {
                        printf("Desconto Aplicado (20%%): -R$ %.2f\n", pedido_final_desconto);
                    }
                    printf("-----------------------------------\n");
                    printf("Total Final do Pedido: R$ %.2f\n", pedido_final_total);
                    printf("Agradecemos a preferência!\n");
                }
                printf("\nVoltando ao Menu Principal...\n");
                break;

            case 4: // Fechar sistema
                printf("Fechando sistema King Burguers. Obrigado pela sua visita!\n");
                c1 = 'n';
                break;
            default:
                printf("Opção Inválida. Por favor, escolha uma opção entre 1 e 4.\n");
                break;
        }
    }
    return 0; 
}