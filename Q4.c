// Feito por: Camila Costa de Souza Careli - 221007582
// Objetivo: Implementar cálculo modular com inverso e exponenciação

#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

int mdcComPassos (int a, int b) {
    int resto;
    while (b != 0) { // [Linha 10]
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto; // [Linha 14]
    }
    return a;
}

int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1; // x1 é o inverso modular
    int A = a, B = m;

    while (m != 0) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0; // Ajuste quando inverso é negativo

    printf("\nSubstituindo, temos que o inverso de %d em %d é %d.\n\n", A, B, x1);
    return x1;
}

long long powMod(long long base, long long exp, long long mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) // Se o bit menos significativo for 1, multiplica
            res = (res * b) % mod;
        b = (b * b) % mod; // quadratura
        exp >>= 1;          // divide exp por 2
    }
    return (int)res;
}

int main() {
    #ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    int H, G, Zn, x, n1;
    printf("Insira H: "); scanf("%d", &H);
    printf("Insira G: "); scanf("%d", &G);
    printf("Insira Zn: "); scanf("%d", &Zn);
    printf("Insira x: "); scanf("%d", &x);
    printf("Insira n1: "); scanf("%d", &n1);
    printf("\n");

    int inverso = inversoModular(G, Zn); // Calculando inverso modular
    int a = (H * inverso) % Zn;          // Representa H / G modular

    printf("Fazendo a multiplicação modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    
    int resultado = powMod(a, x, n1); // Cálculo final da congruência

    printf("Sendo %d o inverso de %d \n", inverso, G);
    printf("Valor final da congruência: %d\n", resultado);

    return 0;
}

/*
========== Previsão de saída para H=7, G=3, Zn=11, x=10, n1=13: ===========

    Insira H: 7
    Insira G: 3
    Insira Zn: 11
    Insira x: 10
    Insira n1: 13

    Substituindo, temos que o inverso de 3 em 11 é 4.

    Fazendo a multiplicação modular: 7 * 4 mod 11 = 6
    Sendo 4 o inverso de 3
    Valor final da congruência: 4
*/

/* 
=========== Respostas para Verdadeiro ou Falso: ===========

    (V) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.
    (F) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.
        Justificativa: O inverso modular só existe se mdc(a, n) = 1.
    (V) A operação (H * inverso) % Zn representa a divisão modular de H por G.
    (V) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de a^x mod n1.
        Justificativa: Para n1 primo, φ(n1) = n1-1 e a^φ(n1) ≡ 1 mod n1.
    (F) A função powMod implementa multiplicações diretas sem otimização.
        Justificativa: Utiliza exponenciação por quadratura (binária), que é otimizada.
    (V) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.
        Justificativa: Garante que o inverso esteja em {0, 1, ..., n-1}.
    (V) O cálculo de φ(n1) é usado apenas quando n1 não é primo.
        Justificativa: Para n1 primo, Pequeno Teorema de Fermat simplifica o cálculo.
*/
