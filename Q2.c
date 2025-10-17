// Feito por: Camila Costa de Souza Careli - 221007582
// Objetivo: calcular o MMC de todos os ciclos e verificar se o resultado está dentro do limite de 50 anos

#include <stdio.h>
#include <stdlib.h>

int mdc(int a, int b) {
    while (b != 0) {
        int resto = b;
        b = a % b;
        a = resto;
    }
    return a;
}

int mmc(int a, int b) {
    return (a * b) / mdc(a, b);
}

int main() {
    int N;

    printf("=====\n");
    printf("Feito por: Camila Costa de Souza Careli\n");
    printf("Matricula: 221007582\n");
    printf("=====\n");


    printf("Digite o numero de chaves: ");
    scanf("%d", &N);

    if (N <= 0) {
        printf("Quantidade invalida de chaves\n");
        return 1;
    }

    int ciclos[N];
    printf("Digite os %d ciclos: ", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &ciclos[i]);
        if (ciclos[i] <= 0) {
            printf("Valor invalido para ciclo\n");
            return 1;
        }
    }

    int resultadoMMC = ciclos[0];
    for (int i = 1; i < N; i++) {
        resultadoMMC = mmc(resultadoMMC, ciclos[i]);
    }

    printf("O MMC dos ciclos e: %d\n", resultadoMMC);
    if (resultadoMMC <= 50) {
        printf("As chaves sincronizam dentro do limite de 50 anos\n");
    } else {
        printf("Impossivel sincronizar dentro do limite de 50 anos\n");
    }

    return 0;
}
