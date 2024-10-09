#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define MAX_CARRINHO 50

typedef struct {
    int codigo_barras;
    char nome[50];
    float preco;
    int quantidade;  // Quantidade em estoque (para itens unitários)
    float peso;      // Peso em estoque (para itens vendidos por kg)
    int vendido;     // Total de unidades vendidas
    float vendido_kg; // Total de quilos vendidos
} Produto;

typedef struct {
    int codigo_barras;
    int quantidade;   // Quantidade do produto (para itens unitários)
    float peso;       // Peso do produto (para itens vendidos por kg)
} ItemCarrinho;

Produto estoque[MAX_PRODUTOS];
ItemCarrinho carrinho[MAX_CARRINHO];
int num_produtos = 0;
int num_itens_carrinho = 0;
float lucro_total = 0.0;

// Prototipos das Funções
void menu_principal();
void gerenciador();
void caixa();
void balanca();
void cadastrar_produto();
void exibir_estoque();
void exibir_transacoes();
void adicionar_carrinho(int codigo_barras, int quantidade, float peso);
void finalizar_venda();
void pesar_produto();
void limpar_tela();

// Função principal
int main() {
    menu_principal();
    return 0;
}

// Função para limpar a tela (cls no Windows, clear no Linux/Mac)
void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Menu Principal
void menu_principal() {
    int opcao;

    while (1) {
        limpar_tela();
        printf("\n--- Menu Principal ---\n");
        printf("1. Gerenciador\n");
        printf("2. Caixa\n");
        printf("3. Balança\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                gerenciador();
                break;
            case 2:
                caixa();
                break;
            case 3:
                balanca();
                break;
            case 4:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// Gerenciador
void gerenciador() {
    int opcao;

    while (1) {
        limpar_tela();
        printf("\n--- Gerenciador ---\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Exibir Estoque\n");
        printf("3. Exibir Transações\n");
        printf("4. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_produto();
                break;
            case 2:
                exibir_estoque();
                break;
            case 3:
                exibir_transacoes();
                break;
            case 4:
                return;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// Cadastrar Produto
void cadastrar_produto() {
    limpar_tela();
    if (num_produtos >= MAX_PRODUTOS) {
        printf("Estoque cheio! Não é possível cadastrar mais produtos.\n");
        return;
    }

    Produto novo_produto;

    printf("Digite o código de barras: ");
    scanf("%d", &novo_produto.codigo_barras);

    printf("Digite o nome do produto: ");
    scanf("%s", novo_produto.nome);

    printf("Digite o preço por unidade ou por kg (caso vendido a granel): ");
    scanf("%f", &novo_produto.preco);

    printf("Digite a quantidade em estoque (0 para produtos vendidos por kg): ");
    scanf("%d", &novo_produto.quantidade);

    if (novo_produto.quantidade == 0) {
        printf("Digite o peso total em estoque (kg): ");
        scanf("%f", &novo_produto.peso);
    } else {
        novo_produto.peso = 0;
    }

    novo_produto.vendido = 0;
    novo_produto.vendido_kg = 0.0;
    estoque[num_produtos] = novo_produto;
    num_produtos++;

    printf("Produto cadastrado com sucesso!\n");
    getchar();
    getchar();  // Pausar para o usuário ver a mensagem
}

// Exibir Estoque
void exibir_estoque() {
    limpar_tela();
    printf("\n--- Estoque Atual ---\n");
    if (num_produtos == 0) {
        printf("Estoque vazio!\n");
    } else {
        for (int i = 0; i < num_produtos; i++) {
            printf("Código: %d | Nome: %s | Preço: %.2f | Quantidade: %d | Peso: %.2f kg\n",
                   estoque[i].codigo_barras, estoque[i].nome, estoque[i].preco, estoque[i].quantidade, estoque[i].peso);
        }
    }
    getchar();
    getchar();
}

// Exibir Transações
void exibir_transacoes() {
    limpar_tela();
    printf("\n--- Transações do Dia ---\n");
    for (int i = 0; i < num_produtos; i++) {
        printf("Produto: %s | Unidades vendidas: %d | Quilos vendidos: %.2f\n", estoque[i].nome, estoque[i].vendido, estoque[i].vendido_kg);
    }
    printf("Lucro total do dia: R$ %.2f\n", lucro_total);
    getchar();
    getchar();
}

// Caixa
void caixa() {
    int opcao;

    while (1) {
        limpar_tela();
        printf("\n--- Caixa ---\n");
        printf("1. Registrar Produto na Cesta de Compras\n");
        printf("2. Finalizar Compra\n");
        printf("3. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                registrar_produto();
                break;
            case 2:
                finalizar_venda();
                break;
            case 3:
                return;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// Registrar Produto no Caixa
void registrar_produto() {
    limpar_tela();
    int codigo_barras, quantidade;
    
    printf("Digite o código de barras do produto: ");
    scanf("%d", &codigo_barras);

    int encontrado = -1;
    for (int i = 0; i < num_produtos; i++) {
        if (estoque[i].codigo_barras == codigo_barras) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Produto não encontrado!\n");
        getchar();
        getchar();
        return;
    }

    Produto *produto = &estoque[encontrado];
    printf("Produto: %s | Preço: %.2f | Estoque: %d\n", produto->nome, produto->preco, produto->quantidade);

    if (produto->peso > 0) {
        printf("Este produto é vendido por kg. Por favor, pese na balança.\n");
    } else {
        printf("Digite a quantidade comprada: ");
        scanf("%d", &quantidade);

        if (quantidade > produto->quantidade) {
            printf("Quantidade insuficiente em estoque!\n");
        } else {
            adicionar_carrinho(codigo_barras, quantidade, 0);
            printf("Produto adicionado à cesta de compras.\n");
        }
    }

    getchar();
    getchar();
}

// Finalizar Compra
void finalizar_venda() {
    limpar_tela();
    float total_venda = 0.0;

    printf("\n--- Cesta de Compras ---\n");
    for (int i = 0; i < num_itens_carrinho; i++) {
        int codigo_barras = carrinho[i].codigo_barras;
        int quantidade = carrinho[i].quantidade;
        float peso = carrinho[i].peso;

        for (int j = 0; j < num_produtos; j++) {
            if (estoque[j].codigo_barras == codigo_barras) {
                if (quantidade > 0) {
                    float total_item = quantidade * estoque[j].preco;
                    printf("Produto: %s | Quantidade: %d | Total: R$ %.2f\n", estoque[j].nome, quantidade, total_item);
                    estoque[j].quantidade -= quantidade;
                    estoque[j].vendido += quantidade;
                    total_venda += total_item;
                }
                if (peso > 0) {
                    float total_item = peso * estoque[j].preco;
                    printf("Produto: %s | Peso: %.2f kg | Total: R$ %.2f\n", estoque[j].nome, peso, total_item);
                    estoque[j].peso -= peso;
                    estoque[j].vendido_kg += peso;
                    total_venda += total_item;
                }
            }
        }
    }

    printf("\nTotal da venda: R$ %.2f\n", total_venda);
    lucro_total += total_venda;
    num_itens_carrinho = 0; // Limpa o carrinho após a venda

    getchar();
    getchar();
}

// Adicionar item ao Carrinho
void adicionar_carrinho(int codigo_barras, int quantidade, float peso) {
    if (num_itens_carrinho >= MAX_CARRINHO) {
        printf("Carrinho cheio!\n");
        return;
    }

    carrinho[num_itens_carrinho].codigo_barras = codigo_barras;
    carrinho[num_itens_carrinho].quantidade = quantidade;
    carrinho[num_itens_carrinho].peso = peso;
    num_itens_carrinho++;
}

// Balança
void balanca() {
    int opcao;

    while (1) {
        limpar_tela();
        printf("\n--- Balança ---\n");
        printf("1. Pesar Produto e Adicionar à Cesta de Compras\n");
        printf("2. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                pesar_produto();
                break;
            case 2:
                return;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// Pesagem de Produto na Balança
void pesar_produto() {
    limpar_tela();
    int codigo_barras;
    float peso;

    printf("Digite o código de barras do produto: ");
    scanf("%d", &codigo_barras);

    int encontrado = -1;
    for (int i = 0; i < num_produtos; i++) {
        if (estoque[i].codigo_barras == codigo_barras && estoque[i].peso > 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Produto não encontrado ou não vendido por kg!\n");
        getchar();
        getchar();
        return;
    }

    Produto *produto = &estoque[encontrado];
    printf("Produto: %s | Preço por kg: %.2f | Estoque em kg: %.2f\n", produto->nome, produto->preco, produto->peso);

    printf("Digite o peso vendido (kg): ");
    scanf("%f", &peso);

    if (peso > produto->peso) {
        printf("Peso insuficiente em estoque!\n");
    } else {
        adicionar_carrinho(codigo_barras, 0, peso);
        printf("Produto adicionado à cesta de compras com sucesso!\n");
    }

    getchar();
    getchar();
}


