#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100

typedef struct
{
    int codigo_barras;
    char nome[50];
    float preco;
    int quantidade;
} Produto;

// Variáveis Globais
Produto estoque[MAX_PRODUTOS];
int num_produtos = 0;

// Prototipos das Funções
void menu_principal();
void menu_estoque();
void menu_caixa();
void cadastrar_produto();
void exibir_estoque();
void passar_produto_no_caixa();

// Função principal que carrega o menu inicial
int main()
{
    menu_principal();
    return 0;
}

// Função que exibe o Menu Principal
void menu_principal()
{
    int opcao;

    while (1)
    {
        printf("\n--- Menu Principal ---\n");
        printf("1. Gestão de Estoque\n");
        printf("2. Sistema de Caixa\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            menu_estoque();
            break;
        case 2:
            menu_caixa();
            break;
        case 3:
            printf("Saindo...\n");
            exit(0);
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// Função para o menu de gestão de estoque
void menu_estoque()
{
    int opcao;

    while (1)
    {
        printf("\n--- Gestão de Estoque ---\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Exibir Estoque\n");
        printf("3. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrar_produto();
            break;
        case 2:
            exibir_estoque();
            break;
        case 3:
            return; // Voltar para o menu principal
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// Função para o menu do sistema de caixa
void menu_caixa()
{
    int opcao;

    while (1)
    {
        printf("\n--- Sistema de Caixa ---\n");
        printf("1. Passar Produto no Caixa\n");
        printf("2. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            passar_produto_no_caixa();
            break;
        case 2:
            return; // Voltar para o menu principal
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// Função para cadastrar um novo produto
void cadastrar_produto()
{
    if (num_produtos >= MAX_PRODUTOS)
    {
        printf("Estoque cheio! Não é possível cadastrar mais produtos.\n");
        return;
    }

    Produto novo_produto;

    printf("Digite o código de barras: ");
    scanf("%d", &novo_produto.codigo_barras);

    printf("Digite o nome do produto: ");
    scanf("%s", novo_produto.nome);

    printf("Digite o preço do produto: ");
    scanf("%f", &novo_produto.preco);

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novo_produto.quantidade);

    estoque[num_produtos] = novo_produto;
    num_produtos++;

    printf("Produto cadastrado com sucesso!\n");
}

// Função para exibir o estoque
void exibir_estoque()
{
    printf("\n--- Estoque Atual ---\n");
    for (int i = 0; i < num_produtos; i++)
    {
        printf("Código: %d | Nome: %s | Preço: %.2f | Quantidade: %d\n",
               estoque[i].codigo_barras, estoque[i].nome, estoque[i].preco, estoque[i].quantidade);
    }
    printf("-------------------------\n");
}

// Função para passar produto no caixa
void passar_produto_no_caixa()
{
    int codigo_barras, quantidade_vendida;
    printf("Digite o código de barras do produto: ");
    scanf("%d", &codigo_barras);

    int encontrado = -1;
    for (int i = 0; i < num_produtos; i++)
    {
        if (estoque[i].codigo_barras == codigo_barras)
        {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1)
    {
        printf("Produto não encontrado!\n");
        return;
    }

    Produto *produto = &estoque[encontrado];

    printf("Produto: %s | Preço: %.2f | Estoque: %d\n", produto->nome, produto->preco, produto->quantidade);

    printf("Digite a quantidade vendida: ");
    scanf("%d", &quantidade_vendida);

    if (quantidade_vendida > produto->quantidade)
    {
        printf("Quantidade insuficiente em estoque!\n");
    }
    else
    {
        produto->quantidade -= quantidade_vendida;
        float total = quantidade_vendida * produto->preco;
        printf("Total da venda: %.2f\n", total);
        printf("Venda realizada com sucesso!\n");
    }
}