#ifndef INTEIROS_H
#define INTEIROS_H

typedef struct {
    int* elementos;
    int tamanho, alocado;
} Inteiros;

Inteiros criar();
int tamanho(Inteiros* c);
void inserir(Inteiros* c, int numero);
void remover(Inteiros* c, int posicao);
Inteiros uniao(Inteiros* c1, Inteiros* c2);
Inteiros intersecao(Inteiros* c1, Inteiros* c2);
Inteiros diferenca(Inteiros* c1, Inteiros* c2);
int imenor(Inteiros* c);
int imaior(Inteiros* c);
int busca(Inteiros* c, int numero);
int iguais(Inteiros* c1, Inteiros* c2);
int vazio(Inteiros* c);
void imprime(Inteiros*c);

#endif