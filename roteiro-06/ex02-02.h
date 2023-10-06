/*----------------- File: FPHeap.h ---------------------+
|Fila de Prioridades com Heap Binaria                   |
|					      		                        |
|					      		                        |
| Implementado por Guilherme C. Pena em 26/09/2023      |
+-------------------------------------------------------+ */

#ifndef FPHEAP_H
#define FPHEAP_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct NO{
    int info, prio;
}NO;

typedef struct{
    int qtd;
    NO dados[MAX];
}FilaP;

FilaP* criaFila(){
    FilaP* fp;
    fp = (FilaP*) malloc (sizeof(FilaP));
    if(fp != NULL)
        fp->qtd = 0;
    return fp;
}

void destroiFila(FilaP** fp){
    if(*fp != NULL) {
        free(*fp);
        *fp = NULL;
    }
}

int tamanhoFila(FilaP *fp){
  if(fp == NULL) return -1;
  return fp->qtd;
}

int estaCheia(FilaP *fp){
  if(fp == NULL) return -1;
  return (fp->qtd == MAX);
}

int estaVazia(FilaP *fp){
  if(fp == NULL) return -1;
  return (fp->qtd == 0);
}

void trocaNO(NO* a, NO* b){
    NO temp;
    temp.info = a->info;
    temp.prio = a->prio;
    a->info = b->info;
    a->prio = b->prio;
    b->info = temp.info;
    b->prio = temp.prio;
}

void ajustaHeapInsere(FilaP* fp, int filho){
    NO temp;
    int pai = (filho-1)/2;
    int prioPai = fp->dados[pai].prio;
    int prioFilho = fp->dados[filho].prio;
    while(filho > 0 && prioPai < prioFilho){
        trocaNO(&fp->dados[filho], &fp->dados[pai]);
        filho = pai;
        pai = (pai-1)/2;
        prioPai = fp->dados[pai].prio;
        prioFilho = fp->dados[filho].prio;
    }
}

int inserirPrio(FilaP* fp, int elem, int pri){
    if(fp == NULL) return 0;
    if(estaCheia(fp)) return 0;
    fp->dados[fp->qtd].info = elem;
    fp->dados[fp->qtd].prio = pri;
    ajustaHeapInsere(fp, fp->qtd);
    fp->qtd++;
    return 1;
}

void ajustaHeapRemove(FilaP* fp, int pai){
    NO temp;
    int filho = 2*pai + 1;
    while(filho < fp->qtd){ 
        if(filho < fp->qtd-1)
            if(fp->dados[filho].prio < fp->dados[filho+1].prio)
                filho++;
        
        if(fp->dados[pai].prio > fp->dados[filho].prio)
            break;
        
        trocaNO(&fp->dados[pai], &fp->dados[filho]);
        pai = filho;
        filho = 2*pai + 1;
    }
}

int removeInicio(FilaP* fp){
    if(fp == NULL) return 0;
    if(estaVazia(fp)) return 0;

    fp->qtd--;
    fp->dados[0].info = fp->dados[fp->qtd].info;
    fp->dados[0].prio = fp->dados[fp->qtd].prio;
    ajustaHeapRemove(fp, 0);
    return 1;
}

int verInicio(FilaP* fp, int* valor, int* pri){
  if(fp == NULL) return 0;
  if(estaVazia(fp)) return 0;
  *valor = fp->dados[0].info;
  *pri = fp->dados[0].prio;
  return 1;
}

void imprime(FilaP* fp){
    if(fp == NULL) return;
    if(estaVazia(fp)){
        printf("Fila Vazia!\n");
        return;
    }
    printf("Elementos:\n");
    int i;
    for(i=0; i<fp->qtd; i++)
        printf("[%d, %d] (%d) -- ", fp->dados[i].prio, fp->dados[i].info, i);
    printf("\n");
}

#endif