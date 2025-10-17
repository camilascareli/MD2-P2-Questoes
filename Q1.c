// Feito por: Camila Costa de Souza Careli - 221007582
// Objetivo: Implementar RSA, fatorando com método p de Pollard, sem uso de long long

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int mulmod(int a, int b, int mod) {
    int res = 0;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1)
            res = (res + a) % mod;
        a = (2 * a) % mod;
        b /= 2;
    }
    return res;
}

int mdc(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

int mdc_verbose(int a, int b) {
    printf("  Calculando mdc(%d, %d) com Algoritmo de Euclides:\n", a, b);
    int original_a = abs(a);
    int original_b = abs(b);
    while (original_b != 0) {
        printf("    -> %d = %d * %d + %d\n", original_a, original_b, original_a / original_b, original_a % original_b);
        int resto = original_a % original_b;
        original_a = original_b;
        original_b = resto;
    }
    printf("  Resultado do MDC: %d\n", original_a);
    return original_a;
}

int inverso_modular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 1, x1 = 0;

    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x1;
        x1 = x0 - q * x1;
        x0 = t;
    }

    if (x0 < 0)
        x0 += m0;

    return x0;
}

int inverso_modular_verbose(int a, int m) {
    printf("  Calculando inverso modular de %d mod %d (Algoritmo Estendido de Euclides):\n", a, m);
    int m0 = m, t, q;
    int x0 = 1, x1 = 0;
    int iter = 1;

    if (m == 1) return 0;

    int temp_a = a, temp_m = m;
    while (temp_a > 1) {
        q = temp_a / temp_m;
        t = temp_m;
        printf("    Passo %d: q=%d, a=%d, m=%d, x0=%d, x1=%d\n", iter++, q, temp_a, temp_m, x0, x1);
        temp_m = temp_a % temp_m, temp_a = t;
        t = x1;
        x1 = x0 - q * x1;
        x0 = t;
    }
    
    printf("    Inverso preliminar: %d\n", x0);
    if (x0 < 0) {
        x0 += m0;
        printf("    Ajustando para positivo: %d\n", x0);
    }
    
    return x0;
}

int powmod(int base, int exp, int mod) {
    int resultado = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            resultado = mulmod(resultado, base, mod);
        base = mulmod(base, base, mod);
        exp /= 2;
    }
    return resultado;
}

int eh_primo(int n) {
    if (n < 2) return 0;
    if (n % 2 == 0) return n == 2;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return 0;
    return 1;
}

int pollard_rho_verbose(int n) {
    if (n % 2 == 0) return 2;
    if (eh_primo(n)) return n;

    int x = 2, y = 2, d = 1, iter = 1;
    printf("  Iniciando Pollard's Rho com x=2, y=2.\n");
    while (d == 1) {
        x = (mulmod(x, x, n) + 1) % n;
        y = (mulmod(y, y, n) + 1) % n;
        y = (mulmod(y, y, n) + 1) % n;
        
        d = mdc(abs(x - y), n);
        printf("    Iteracao %d: x=%d, y=%d, |x-y|=%d, mdc(%d, %d)=%d\n", iter++, x, y, abs(x - y), abs(x - y), n, d);
    }

    if (d == n) return -1; 
    return d;
}


void pre_codificar(const char *msg, char *saida) {
    int k = 0;
    for (int i = 0; msg[i] != '\0'; i++) {
        char c = toupper(msg[i]);
        if (c == ' ') {
            saida[k++] = '0';
            saida[k++] = '0';
        } else if (c >= 'A' && c <= 'Z') {
            int valor = 11 + (c - 'A');
            saida[k++] = (valor / 10) + '0';
            saida[k++] = (valor % 10) + '0';
        }
    }
    saida[k] = '\0';
}

void decodificar(const char *entrada, char *saida) {
    int j = 0;
    for (int i = 0; entrada[i] != '\0'; i += 2) {
        int v = (entrada[i] - '0') * 10 + (entrada[i + 1] - '0');
        if (v == 0) {
            saida[j++] = ' ';
        } else if (v >= 11 && v <= 36) {
            saida[j++] = 'A' + (v - 11);
        }
    }
    saida[j] = '\0';
}

int main() {
    printf("=====\n");
    printf("Feito por: Camila Costa de Souza Careli\n");
    printf("Matricula: 221007582\n");
    printf("=====\n");

    int N1, N2;
    printf("Digite o primeiro numero composto N1 (3 ou 4 digitos): ");
    scanf("%d", &N1);
    printf("Digite o segundo numero composto N2 (3 ou 4 digitos): ");
    scanf("%d", &N2);

    if (N1 < 100 || N1 > 9999 || N2 < 100 || N2 > 9999) {
        printf("Erro: Os numeros devem ter 3 ou 4 digitos.\n");
        return 1;
    }

    printf("\n--- ETAPA 1: Fatoracao com Metodo p de Pollard ---\n");
    printf("Fatorando N1 = %d...\n", N1);
    int p = pollard_rho_verbose(N1);
    if (p == -1) {
        printf("Falha ao fatorar N1. O metodo pode falhar para alguns numeros. Tente outro.\n");
        return 1;
    }
    printf("Fator primo 'p' de N1 encontrado: p = %d\n\n", p);

    printf("Fatorando N2 = %d...\n", N2);
    int q = pollard_rho_verbose(N2);
    if (q == -1) {
        printf("Falha ao fatorar N2. O metodo pode falhar para alguns numeros. Tente outro.\n");
        return 1;
    }
    printf("Fator primo 'q' de N2 encontrado: q = %d\n", q);

    printf("\n--- ETAPA 2: Geracao das Chaves RSA ---\n");
    int n = p * q;
    int z = (p - 1) * (q - 1);

    printf("Calculando o modulo: n = p * q = %d * %d = %d\n", p, q, n);
    printf("Calculando o totiente de Euler: z = (p-1)*(q-1) = %d * %d = %d\n\n", p-1, q-1, z);

    printf("Escolhendo o expoente publico 'e' (menor e > 1 tal que mdc(e, z) = 1)...\n");
    int e = 2;
    while (1) {
        printf("Testando e = %d...\n", e);
        if (mdc(e, z) == 1) {
            printf("  -> mdc(%d, %d) = 1. 'e' encontrado!\n", e, z);
            break;
        }
        printf("  -> mdc(%d, %d) != 1. Tentando o proximo.\n", e, z);
        e++;
    }
    
    printf("\nCalculando o expoente privado 'd' (d * e = 1 mod z)...\n");
    int d = inverso_modular_verbose(e, z);

    printf("\n[CHAVES GERADAS]\n");
    printf("Chave Publica: (n = %d, e = %d)\n", n, e);
    printf("Chave Privada: (n = %d, d = %d)\n", n, d);

    printf("\n--- ETAPA 3: Codificacao e Decodificacao ---\n");
    char msg[100], cod[201], dec[101];
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nDigite a mensagem EM CAIXA ALTA  para cifrar: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0';

    pre_codificar(msg, cod);
    printf("Mensagem pre-codificada em blocos de 2 digitos: %s\n", cod);

    printf("\n[Criptografando a Mensagem...]\n");
    int C[100], k = 0;
    for (int i = 0; cod[i] != '\0' && cod[i + 1] != '\0'; i += 2) {
        int bloco = (cod[i] - '0') * 10 + (cod[i + 1] - '0');
        
        printf("  Criptografando bloco M = %02d:\n", bloco);
        printf("    Justificativa: A operacao C = M^e mod n e validada pelo Teorema de Euler, pois mdc(M, n) geralmente e 1.\n");
        C[k] = powmod(bloco, e, n);
        printf("    Calculo: C = %d^%d mod %d = %d\n", bloco, e, n, C[k]);
        
        k++;
    }

    printf("\nMensagem Cifrada (sequencia de blocos C): ");
    for(int j=0; j<k; j++) printf("%d ", C[j]);
    printf("\n");

    printf("\n[Descriptografando a Mensagem...]\n");
    char recod[201] = "";
    for (int j = 0; j < k; j++) {
        int M = powmod(C[j], d, n);
        
        printf("  Descriptografando bloco C = %d:\n", C[j]);
        printf("    Justificativa: A operacao M = C^d mod n funciona porque 'd' e o inverso modular de 'e' mod z.\n");
        printf("    Calculo: M = %d^%d mod %d = %02d\n", C[j], d, n, M);
        
        char temp[4];
        sprintf(temp, "%02d", M);
        strcat(recod, temp);
    }

    decodificar(recod, dec);
    printf("\n--- RESULTADO FINAL ---\n");
    printf("Mensagem Original:   %s\n", msg);
    printf("Mensagem Decifrada:  %s\n", dec);

    if(strcmp(msg, dec) == 0) {
        printf("\nConfirmacao: A mensagem decifrada e identica a original!\n");
    } else {
        printf("\nErro: A mensagem decifrada e diferente da original.\n");
    }

    return 0;
}