#ifndef ARVOREB_H
#define ARVOREB_H

#include <stdio.h>
#include <stdlib.h>

#define M 2
#define MM (M * 2)  // 2M
#define FALSE 0
#define TRUE 1

typedef struct Registro {
    int chave;
    /*outros componentes*/
} Registro;

typedef struct Pagina *Apontador;

typedef struct Pagina {
    int n;  // Qtd de registros na pagina
    Registro r[MM];
    Apontador p[MM + 1];
} Pagina;

typedef struct Pagina *ArvoreB;

ArvoreB *criaArvoreB() {
    ArvoreB *raiz;
    raiz = (ArvoreB *)malloc(sizeof(ArvoreB));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

Pagina *criapagina() {
    Pagina *pag;
    pag = (Pagina *)malloc(sizeof(Pagina));
    pag->n = 0;
    int i;
    for (i = 0; i < (MM + 1); i++)
        pag->p[i] = NULL;
    return pag;
}

void destroiPagina(Pagina *pag) {
    if (pag == NULL) return;
    int i;
    for (i = 0; i < (MM + 1); i++)
        destroiPagina(pag->p[i]);
    free(pag);
}

void destroiArvoreB(ArvoreB *raiz) {
    if (raiz != NULL) {
        destroiPagina(*raiz);
        free(raiz);
    }
}

int estaVazia(ArvoreB *raiz) {
    if (raiz == NULL) return 0;
    return (*raiz == NULL);
}

void pre_ordem(Pagina *raiz, int nivel) {
    if (raiz != NULL) {
        int i;
        printf("Nivel %d: ", nivel);
        for (i = 0; i < raiz->n; i++)
            printf("%2d ", raiz->r[i].chave);
        printf("\n");

        // int contP = 0;
        // for(i=0; i<MM+1; i++) if(raiz->p[i] != NULL) contP++;
        // printf("%d ponteiros\n", contP);

        for (i = 0; i < raiz->n + 1; i++)
            pre_ordem(raiz->p[i], nivel + 1);
    }
}

void imprimeArvoreB(ArvoreB *raiz) {
    if (raiz == NULL) return;
    if (estaVazia(raiz)) {
        printf("Arvore B Vazia!\n");
        return;
    }
    pre_ordem(*raiz, 0);
    printf("\n");
}

// Procedimento de PESQUISAR

void pesquisaRec(Registro *x, Apontador ap) {
    if (ap == NULL) {
        printf("Registro nao esta presente na arvore\n");
        return;
    }
    int i = 1;
    while (i < ap->n && x->chave > ap->r[i - 1].chave) i++;
    if (x->chave == ap->r[i - 1].chave) {
        printf("Registro (chave %2d) encontrado!\n", x->chave);
        *x = ap->r[i - 1];  // Atribui reg
        return;
    }
    if (x->chave < ap->r[i - 1].chave)
        pesquisaRec(x, ap->p[i - 1]);
    else
        pesquisaRec(x, ap->p[i]);
}

void pesquisaArvoreB(ArvoreB *raiz, Registro *reg) {
    if (raiz == NULL) return;
    if (estaVazia(raiz)) {
        printf("Arvore B Vazia!\n");
        return;
    }
    pesquisaRec(reg, *raiz);
}

// Procedimento de INSERIR

void insereNaPagina(Apontador ap, Registro reg, Apontador apDir) {
    int k, NaoAchouPosicao;
    k = ap->n;
    NaoAchouPosicao = (k > 0);

    while (NaoAchouPosicao) {
        if (reg.chave >= ap->r[k - 1].chave) {
            NaoAchouPosicao = FALSE;
            break;
        }

        ap->r[k] = ap->r[k - 1];  // Atribui reg
        ap->p[k + 1] = ap->p[k];
        k--;

        if (k < 1) NaoAchouPosicao = FALSE;
    }

    ap->r[k] = reg;  // Atribui reg
    ap->p[k + 1] = apDir;
    ap->n++;
}

void insereRec(Registro reg, Apontador ap, int *Cresceu, Registro *regRetorno, Apontador *apRetorno) {
    int i = 1, j;
    Apontador apTemp;

    if (ap == NULL) {
        printf("Inserindo %2d..\n", reg.chave);
        *Cresceu = TRUE;
        *regRetorno = reg;  // Atribui reg
        *apRetorno = NULL;
        return;
    }

    while (i < ap->n && reg.chave > ap->r[i - 1].chave) i++;

    if (reg.chave == ap->r[i - 1].chave) {
        printf("Erro: Registro ja esta presente\n");
        *Cresceu = FALSE;
        return;
    }

    if (reg.chave < ap->r[i - 1].chave) i--;

    insereRec(reg, ap->p[i], Cresceu, regRetorno, apRetorno);

    if (!*Cresceu) return;

    if (ap->n < MM) { /* Página tem espaço */
        insereNaPagina(ap, *regRetorno, *apRetorno);
        *Cresceu = FALSE;
        return;
    }

    /* Overflow: Página tem que ser dividida */
    // Original Comentado
    // apTemp = (Pagina*) malloc (sizeof(Pagina));
    // apTemp->n = 0;
    // apTemp->p[0] = NULL;

    apTemp = criapagina();

    if (i < (M + 1)) {
        insereNaPagina(apTemp, ap->r[MM - 1], ap->p[MM]);
        ap->n--;
        ap->p[MM] = NULL;
        insereNaPagina(ap, *regRetorno, *apRetorno);
    } else {
        insereNaPagina(apTemp, *regRetorno, *apRetorno);
    }

    for (j = M + 2; j <= MM; j++) {
        insereNaPagina(apTemp, ap->r[j - 1], ap->p[j]);
        ap->p[j] = NULL;
    }

    ap->n = M;
    apTemp->p[0] = ap->p[M + 1];
    ap->p[M + 1] = NULL;
    *regRetorno = ap->r[M];  // Atribui reg
    *apRetorno = apTemp;
}

void insereArvoreB(ArvoreB *raiz, Registro reg) {
    if (raiz == NULL) return;

    int Cresceu;
    Registro regRetorno;
    Pagina *apRetorno, *apTemp;

    insereRec(reg, *raiz, &Cresceu, &regRetorno, &apRetorno);

    if (Cresceu) { /* Árvore cresce na altura pela raiz */
        // apTemp = (Pagina *) malloc (sizeof(Pagina));
        apTemp = criapagina();
        apTemp->n = 1;
        apTemp->r[0] = regRetorno;
        apTemp->p[1] = apRetorno;
        apTemp->p[0] = *raiz;
        *raiz = apTemp;
    }
}

// Procedimento de RETIRAR
void Reconstitui(Apontador apPag, Apontador apPai, int PosPai, int *Diminuiu) {
    Pagina *Aux;
    int DispAux, j;

    if (PosPai < apPai->n) { /* Aux = Pagina a direita de apPag */
        Aux = apPai->p[PosPai + 1];
        DispAux = (Aux->n - M + 1) / 2;

        apPag->r[apPag->n] = apPai->r[PosPai];
        apPag->p[apPag->n + 1] = Aux->p[0];
        apPag->n++;

        if (DispAux > 0) { /* Existe folga: transfere de Aux para apPag */
            for (j = 1; j < DispAux; j++)
                insereNaPagina(apPag, Aux->r[j - 1], Aux->p[j]);

            apPai->r[PosPai] = Aux->r[DispAux - 1];
            Aux->n -= DispAux;

            for (j = 0; j < Aux->n; j++)
                Aux->r[j] = Aux->r[j + DispAux];

            for (j = 0; j <= Aux->n; j++)
                Aux->p[j] = Aux->p[j + DispAux];

            *Diminuiu = FALSE;
        } else { /* Fusão: intercala Aux em apPag e libera Aux */
            for (j = 1; j <= M; j++)
                insereNaPagina(apPag, Aux->r[j - 1], Aux->p[j]);

            free(Aux);

            for (j = PosPai + 1; j < apPai->n; j++) {
                apPai->r[j - 1] = apPai->r[j];
                apPai->p[j] = apPai->p[j + 1];
            }

            apPai->n--;

            if (apPai->n >= M) *Diminuiu = FALSE;
        }
    } else { /* Aux = Pagina a esquerda de apPag */
        Aux = apPai->p[PosPai - 1];
        DispAux = (Aux->n - M + 1) / 2;

        for (j = apPag->n; j >= 1; j--)
            apPag->r[j] = apPag->r[j - 1];

        apPag->r[0] = apPai->r[PosPai - 1];

        for (j = apPag->n; j >= 0; j--)
            apPag->p[j + 1] = apPag->p[j];

        apPag->n++;

        if (DispAux > 0) { /* Existe folga: transfere de Aux para apPag */
            for (j = 1; j < DispAux; j++)
                insereNaPagina(apPag, Aux->r[Aux->n - j], Aux->p[Aux->n - j + 1]);

            apPag->p[0] = Aux->p[Aux->n - DispAux + 1];
            apPai->r[PosPai - 1] = Aux->r[Aux->n - DispAux];
            Aux->n -= DispAux;
            *Diminuiu = 0;
        } else { /* Fusão: intercala apPag em Aux e libera apPag */
            for (j = 1; j <= M; j++)
                insereNaPagina(Aux, apPag->r[j - 1], apPag->p[j]);

            free(apPag);
            apPai->n--;

            if (apPai->n >= M) *Diminuiu = FALSE;
        }
    }
}

void Antecessor(Apontador ap, int i, Apontador apPai, int *Diminuiu) {
    if (apPai->p[apPai->n] != NULL) {
        Antecessor(ap, i, apPai->p[apPai->n], Diminuiu);
        if (*Diminuiu)
            Reconstitui(apPai->p[apPai->n], apPai, (int)apPai->n, Diminuiu);
        return;
    }

    ap->r[i - 1] = apPai->r[apPai->n - 1];
    apPai->n--;
    *Diminuiu = (apPai->n < M);
}

void removeRec(int Ch, Apontador *ap, int *Diminuiu) {
    int j, i = 1;
    Apontador Pag;

    if (*ap == NULL) {
        printf("Erro: registro nao esta na arvore\n");
        *Diminuiu = FALSE;
        return;
    }

    Pag = *ap;

    while (i < Pag->n && Ch > Pag->r[i - 1].chave) i++;

    if (Ch == Pag->r[i - 1].chave) {
        if (Pag->p[i - 1] == NULL) { /* Pagina folha */
            Pag->n--;
            *Diminuiu = (Pag->n < M);

            for (j = i; j <= Pag->n; j++) {
                Pag->r[j - 1] = Pag->r[j];
                Pag->p[j] = Pag->p[j + 1];
            }

            return;
        }

        /* Pagina nao e folha: trocar com antecessor */
        Antecessor(*ap, i, Pag->p[i - 1], Diminuiu);

        if (*Diminuiu) Reconstitui(Pag->p[i - 1], *ap, i - 1, Diminuiu);

        return;
    }

    if (Ch > Pag->r[i - 1].chave) i++;

    removeRec(Ch, &Pag->p[i - 1], Diminuiu);

    if (*Diminuiu) Reconstitui(Pag->p[i - 1], *ap, i - 1, Diminuiu);
}

void removeArvoreB(ArvoreB *raiz, Registro reg) {
    int Diminuiu;
    Apontador Aux;

    printf("Removendo %2d..\n", reg.chave);

    removeRec(reg.chave, raiz, &Diminuiu);

    if (Diminuiu && (*raiz)->n == 0) { /* Arvore diminui na altura */
        Aux = *raiz;
        *raiz = Aux->p[0];
        free(Aux);
    }
}

#endif