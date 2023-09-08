#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_CHARS 50

typedef struct {
    char nome[NOME_CHARS];
    double preco;
    int quantidade;
} Produto;

typedef struct {
    Produto produtos[100];
    int produtos_total;
} CatalogoProdutos;

enum OPCOES {
    SAIR = 0,
    ADICIONAR,
    VERIFICAR,
    IMPRIMIR
};

void criarCatalogo(CatalogoProdutos *c) {
    c->produtos_total = 0;
}

void adicionarProduto(CatalogoProdutos *c, char *nome, double preco, int quantidade) {
    Produto novo;
    strcpy(novo.nome, nome);
    novo.preco = preco;
    novo.quantidade = quantidade;

    c->produtos[c->produtos_total] = novo;
}

int verificarEstoque(CatalogoProdutos *c, char *nome) {
    for (int i = 0; i < c->produtos_total; i++) {
        if (strcmp(nome, c->produtos[i].nome) == 0) {
            return c->produtos[i].quantidade;
        }
    }

    return 0;
}

void imprimirCatalogo(CatalogoProdutos *c) {
    for (int i = 0; i < c->produtos_total; i++) {
        printf("Produto %d { Nome = %s | Preco = %.2lf | Quantidade = %d }\n", i + 1, c->produtos[i].nome, c->produtos[i].preco, c->produtos[i].quantidade);
    }
}

int getOpcao() {
    int opcao;

    printf("\n======================\n");
    printf("(%d) Adicionar produto\n", ADICIONAR);
    printf("(%d) Verificar estoque\n", VERIFICAR);
    printf("(%d) Imprimir catalogo\n", IMPRIMIR);
    printf("(%d) Sair\n", SAIR);
    printf("======================\n");
    printf("Opcao escolhida: ");
    scanf("%d", &opcao);

    printf("\n");
    return opcao;
}

Produto *getProduto(CatalogoProdutos *catalogo, char *nome) {
    for (int i = 0; i < catalogo->produtos_total; i++) {
        if (strcmp(catalogo->produtos[i].nome, nome) == 0) {
            return &catalogo->produtos[i];
        }
    }
    return NULL;
}

int main() {
    CatalogoProdutos catalogo;
    criarCatalogo(&catalogo);

    int quantidade;
    double preco;
    char nome[NOME_CHARS + 1];

    int sair = 0;
    while (!sair) {
        switch (getOpcao()) {
            case SAIR:
                sair = 1;
                break;
            case ADICIONAR:
                setbuf(stdin, NULL);
                printf("Nome: ");
                fgets(nome, NOME_CHARS + 1, stdin);
                if (nome[strlen(nome) - 1] == '\n')
                    nome[strlen(nome) - 1] = '\0';
                setbuf(stdin, NULL);
                printf("Preco: ");
                scanf("%lf", &preco);
                printf("Quantidade: ");
                scanf("%d", &quantidade);

                if (getProduto(&catalogo, nome) == NULL) {
                    adicionarProduto(&catalogo, nome, preco, quantidade);
                    catalogo.produtos_total++;
                    printf("Produto adicionado com sucesso\n");
                } else {
                    printf("Produto ja existente\n");
                }
                break;
            case VERIFICAR:
                setbuf(stdin, NULL);
                printf("Nome: ");
                fgets(nome, NOME_CHARS + 1, stdin);
                if (nome[strlen(nome) - 1] == '\n')
                    nome[strlen(nome) - 1] = '\0';
                setbuf(stdin, NULL);

                if (getProduto(&catalogo, nome) != NULL) {
                    printf("Quantidade = %d\n", verificarEstoque(&catalogo, nome));
                } else {
                    printf("Produto nao encontrado\n");
                }
                break;
            case IMPRIMIR:
                imprimirCatalogo(&catalogo);
                break;
            default:
                printf("Opcao invalida - Tente novamente\n");
                break;
        }
    }

    return 0;
}