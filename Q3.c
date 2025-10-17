// Feito por: Camila Costa de Souza Careli - 221007582
// Objetivo: Calcular a Razão de Eficiência de N e imprimir o resultado com duas casas decimais de precisão

#include <stdio.h>
#include <math.h>

void fatorar(int N, int fatores[], int expoentes[], int *numFatores) {
    int n = N;
    int i = 0;
    int count = 0;

    while (n % 2 == 0) {
        count++;
        n /= 2;
    }
    if (count > 0) {
        fatores[i] = 2;
        expoentes[i] = count;
        i++;
    }

    for (int d = 3; d*d <= n; d += 2) {
        count = 0;
        while (n % d == 0) {
            count++;
            n /= d;
        }
        if (count > 0) {
            fatores[i] = d;
            expoentes[i] = count;
            i++;
        }
    }

    if (n > 1) {
        fatores[i] = n;
        expoentes[i] = 1;
        i++;
    }

    *numFatores = i;

    printf("Fatores primos de %d:\n", N);
    for (int j = 0; j < i; j++) {
        printf("%d^%d\n", fatores[j], expoentes[j]);
    }
}

int calcularTau(int expoentes[], int numFatores) {
    int tau = 1;
    for (int i = 0; i < numFatores; i++) {
        tau *= (expoentes[i] + 1);
    }
    return tau;
}

int calcularSigma(int fatores[], int expoentes[], int numFatores) {
    int sigma = 1;
    for (int i = 0; i < numFatores; i++) {
        int p = fatores[i];
        int a = expoentes[i];
        int termo = 0;
        int pot = 1;
        for (int j = 0; j <= a; j++) {
            termo += pot;
            pot *= p;
        }
        sigma *= termo;
    }
    return sigma;
}

int main() {
    int N;
    printf("Digite um numero inteiro N: ");
    scanf("%d", &N);

    int fatores[100];
    int expoentes[100];
    int numFatores;

    fatorar(N, fatores, expoentes, &numFatores);

    int tau = calcularTau(expoentes, numFatores);
    printf("Tau(N) = %d\n", tau);

    int sigma = calcularSigma(fatores, expoentes, numFatores);
    printf("Sigma(N) = %d\n", sigma);

    double razao = (tau + sigma) / (double)N;
    printf("Razao de eficiencia: %.2lf\n", razao);

    return 0;
}
