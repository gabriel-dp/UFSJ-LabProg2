#include "trie.h"

#include <stdio.h>

// Função principal
int main() {
    // Chaves de entrada (use apenas 'a' a 'z' em minúsculas)
    char chaves[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    char saida[][32] = {"Nao encontrada na TRIE", "Encontrada na TRIE"};

    NO *raiz = criaNO();
    // Construir a trie
    int i;
    printf("\n---- Trie - INSERCAO:\n");
    for (i = 0; i < 8; i++) {
        printf("Inserindo %s\n", chaves[i]);
        inserir(raiz, chaves[i]);
    }

    printf("\n\n---- Trie - APOS INSERCAO:\n");
    imprimeTrie(raiz);

    // Buscar por diferentes chaves
    printf("\n---- Trie - PESQUISA:\n");
    printf("%s --- %s\n", "the", saida[buscar(raiz, "the")]);
    printf("%s --- %s\n", "these", saida[buscar(raiz, "these")]);
    printf("%s --- %s\n", "their", saida[buscar(raiz, "their")]);
    printf("%s --- %s\n\n", "thaw", saida[buscar(raiz, "thaw")]);

    return 0;
}
