#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100

typedef struct {
    int codigo_barras;
    char nome[50];
    float preco;
    int quantidade;
} Produto;

Produto estoque[MAX_PRODUTOS];
int num_produtos = 0;

void cadastrar_produto() {
    if (num_produtos >= MAX_PRODUTOS) {
        printf("Estoque cheio!\n");
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

void exibir_estoque() {
    printf("\n--- Estoque ---\n");
    for (int i = 0; i < num_produtos; i++) {
        printf("Código: %d | Nome: %s | Preço: %.2f | Quantidade: %d\n",
               estoque[i].codigo_barras, estoque[i].nome, estoque[i].preco, estoque[i].quantidade);
    }
    printf("------------------\n");
}

void passar_produto_no_caixa() {
    int codigo_barras, quantidade_vendida;
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
        return;
    }

    Produto *produto = &estoque[encontrado];

    printf("Produto: %s | Preço: %.2f | Estoque: %d\n", produto->nome, produto->preco, produto->quantidade);

    printf("Digite a quantidade vendida: ");
    scanf("%d", &quantidade_vendida);

    if (quantidade_vendida > produto->quantidade) {
        printf("Quantidade insuficiente em estoque!\n");
    } else {
        produto->quantidade -= quantidade_vendida;
        float total = quantidade_vendida * produto->preco;
        printf("Total da venda: %.2f\n", total);
        printf("Venda realizada com sucesso!\n");
    }
}

int main() {
    int opcao;

    while (1) {
        printf("\n--- Sistema de Hortifruti ---\n");
        printf("1. Cadastrar produto\n");
        printf("2. Exibir estoque\n");
        printf("3. Passar produto no caixa\n");
        printf("4. Sair\n");
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
                passar_produto_no_caixa();
                break;
            case 4:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}