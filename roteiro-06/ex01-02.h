#ifndef DDE_H
#define DDE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NO{
    int info;
    struct NO* prox;
    struct NO* ant;
}NO;

typedef struct{
    int qtd;
    struct NO* ini;
    struct NO* fim;
}Deque;


NO* alocarNO(){
    return (NO*) malloc (sizeof(NO));
}

void liberarNO(NO* q){
    free(q);
}

Deque* criaDeque(){
    Deque* dq;
    dq = (Deque*) malloc (sizeof(Deque));
    if(dq != NULL){
        dq->qtd = 0;
        dq->ini = NULL;
        dq->fim = NULL;
    }
    return dq;
}

void destroiDeque(Deque **dq){
    if(*dq != NULL){
        NO* aux;
        while((*dq)->ini != NULL){
            aux = (*dq)->ini;
            (*dq)->ini = (*dq)->ini->prox;
            liberarNO(aux);
        }
        free(*dq);        
        *dq = NULL;
    }
}

int tamanhoDeque(Deque *dq){
    if(dq == NULL)
        return -1;
    return dq->qtd;
}

int estaVazio(Deque *dq){
    if(dq == NULL)
        return -1;
    return (dq->qtd == 0);
}

int insereInicio(Deque* dq, int elem){
    if(dq == NULL) return 0;
    NO* novo = alocarNO();
    if(novo == NULL) return 0;
    novo->info = elem;
    novo->ant = NULL;
    if(estaVazio(dq)){
        novo->prox = NULL;
        dq->fim = novo;
    }else{
        dq->ini->ant = novo;
        novo->prox = dq->ini;
    }
    dq->ini = novo;
    dq->qtd++;
    return 1;
}

int insereFim(Deque* dq, int elem){
    if(dq == NULL) return 0;
    NO* novo = alocarNO();
    if(novo == NULL) return 0;
    novo->info = elem;
    novo->prox = NULL;
    if(estaVazio(dq)){
        novo->ant = NULL;
        dq->ini = novo;
    }else{
        dq->fim->prox = novo;
        novo->ant = dq->fim;
    }
    dq->fim = novo;
    dq->qtd++;
    return 1;
}

int removeInicio(Deque* dq){
    if(dq == NULL) return 0;
    if(estaVazio(dq)) return 0;
    NO* aux = dq->ini;
    if(dq->ini == dq->fim){
        dq->ini = dq->fim = NULL;
    }else{
        dq->ini = dq->ini->prox;
        dq->ini->ant = NULL;
    }
    liberarNO(aux);
    dq->qtd--;
    return 1;
}

int removeFim(Deque* dq){
    if(dq == NULL) return 0;
    if(estaVazio(dq)) return 0;
    NO* aux = dq->fim;
    if(dq->ini == dq->fim){
        dq->ini = dq->fim = NULL;
    }else{
        dq->fim = dq->fim->ant;
        dq->ini->prox = NULL;
    }
    liberarNO(aux);
    dq->qtd--;
    return 1;
}

int verInicio(Deque* dq, int* p){
  if(dq == NULL) return 0;
  if(estaVazio(dq)) return 0;
  *p = dq->ini->info;
  return 1;
}

int verFim(Deque* dq, int* p){
  if(dq == NULL) return 0;
  if(estaVazio(dq)) return 0;
  *p = dq->fim->info;
  return 1;
}

void imprime(Deque* dq){
  if(dq == NULL) return;
  if(estaVazio(dq)){
    printf("Deque Vazio!\n");
    return;
  }
  NO* aux = dq->ini;
  printf("Elementos:\n");
  while(aux != NULL){
    printf("%d ", aux->info);
    aux = aux->prox;
  }
  printf("\n");
}

#endif