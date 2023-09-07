#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_CHARS 50
#define CONTAS_MAX 100

typedef struct {
    int numero;
    char titular[NOME_CHARS + 1];
    double saldo;
} ContaBancaria;

typedef struct {
    ContaBancaria contas[CONTAS_MAX];
    int quantidade;
} Banco;

enum OPCOES {
    SAIR = 0,
    CRIAR,
    DEPOSITAR,
    SACAR,
    CONSULTAR,
    IMPRIMIR
};

Banco criarBanco() {
    Banco novo;
    novo.quantidade = 0;
    return novo;
}

void criarConta(ContaBancaria* c, int numero, char* titular) {
    c->numero = numero;
    strcpy(c->titular, titular);
    c->saldo = 0.0;
}

void depositar(ContaBancaria* c, double valor) {
    c->saldo += valor;
}

void sacar(ContaBancaria* c, double valor) {
    if (c->saldo >= valor) {
        c->saldo -= valor;
    }
}

double consultarSaldo(ContaBancaria* c) {
    return c->saldo;
}

void imprimirInfo(ContaBancaria* c) {
    printf("Numero: %d\n", c->numero);
    printf("Titular: %s\n", c->titular);
    printf("Saldo: %.2lf\n", c->saldo);
}

int getOpcao() {
    int opcao;

    printf("\n========================\n");
    printf("(%d) Criar conta\n", CRIAR);
    printf("(%d) Depositar\n", DEPOSITAR);
    printf("(%d) Sacar\n", SACAR);
    printf("(%d) Consultar saldo\n", CONSULTAR);
    printf("(%d) Imprimir informacoes\n", IMPRIMIR);
    printf("(%d) Sair\n", SAIR);
    printf("========================\n");

    printf("Opcao escolhida: ");
    scanf("%d", &opcao);

    printf("\n");
    return opcao;
}

ContaBancaria* getConta(int numero, Banco* banco) {
    for (int i = 0; i < banco->quantidade; i++) {
        if (banco->contas[i].numero == numero) {
            return &banco->contas[i];
        }
    }
    return NULL;
}

int main() {
    Banco banco = criarBanco();
    int numero;
    double valor;
    char titular[NOME_CHARS + 1];
    ContaBancaria* conta;

    int sair = 0;
    while (!sair) {
        switch (getOpcao()) {
            case SAIR:
                sair = 1;
                break;
            case CRIAR:
                printf("Numero: ");
                scanf("%d", &numero);
                setbuf(stdin, NULL);
                printf("Titular: ");
                fgets(titular, NOME_CHARS + 1, stdin);
                if (titular[strlen(titular) - 1] == '\n')
                    titular[strlen(titular) - 1] = '\0';
                setbuf(stdin, NULL);

                conta = getConta(numero, &banco);
                if (conta == NULL) {
                    criarConta(&banco.contas[banco.quantidade], numero, titular);
                    banco.quantidade++;
                    printf("Conta criada com sucesso\n");
                } else {
                    printf("Conta ja existente\n");
                }
                break;
            case DEPOSITAR:
                printf("Numero: ");
                scanf("%d", &numero);
                printf("Valor: ");
                scanf("%lf", &valor);

                conta = getConta(numero, &banco);
                if (conta != NULL) {
                    depositar(conta, valor);
                    printf("Deposito efetuado com sucesso\n");
                } else {
                    printf("Conta nao encontrada\n");
                }
                break;
            case SACAR:
                printf("Numero: ");
                scanf("%d", &numero);
                printf("Valor: ");
                scanf("%lf", &valor);

                conta = getConta(numero, &banco);
                if (conta != NULL) {
                    sacar(conta, valor);
                    printf("Saque efetuado com sucesso\n");
                } else {
                    printf("Conta nao encontrada\n");
                }
                break;
            case CONSULTAR:
                printf("Numero: ");
                scanf("%d", &numero);

                conta = getConta(numero, &banco);
                if (conta != NULL) {
                    printf("Saldo = %2lf\n", consultarSaldo(conta));
                } else {
                    printf("Conta nao encontrada\n");
                }
                break;
            case IMPRIMIR:
                printf("Numero: ");
                scanf("%d", &numero);

                conta = getConta(numero, &banco);
                if (conta != NULL) {
                    imprimirInfo(conta);
                } else {
                    printf("Conta nao encontrada\n");
                }
                break;
            default:
                printf("Opcao invalida - Tente novamente\n");
                break;
        }
    }

    return 0;
}