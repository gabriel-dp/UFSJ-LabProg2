#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[20];
    int matricula;
    double nota;
} Aluno;

void imprimeAluno(Aluno aluno) {
    printf("Nome = %s | Matricula = %d | Nota = %.2f\n", aluno.nome, aluno.matricula, aluno.nota);
}

void imprimeMax(Aluno* alunos, int n) {
    int max = 0;
    for (int i = 1; i < n; i++) {
        if (alunos[i].nota > alunos[max].nota) max = i;
    }
    printf("Maior - ");
    imprimeAluno(alunos[max]);
}

void imprimeMin(Aluno* alunos, int n) {
    int min = 0;
    for (int i = 1; i < n; i++) {
        if (alunos[i].nota < alunos[min].nota) min = i;
    }
    printf("Menor - ");
    imprimeAluno(alunos[min]);
}

int main() {
    Aluno a, b, c;
    strcpy(a.nome, "Ana");
    a.matricula = 1;
    a.nota = 10;
    strcpy(b.nome, "Davi");
    b.matricula = 2;
    b.nota = 9.9;
    strcpy(c.nome, "Prenassi");
    c.matricula = 3;
    c.nota = 9.8;

    Aluno alunos[] = {a, b, c};
    imprimeMax(alunos, sizeof(alunos) / sizeof(alunos[0]));
    imprimeMin(alunos, sizeof(alunos) / sizeof(alunos[0]));

    return 0;
}