#include <stdio.h>
#include <math.h>
#define max 100

void Calcula_DY(double Y[][max], int n, int i) {
    int j;
    for (j=0; j<n-1; j++) {
        Y[i][j]=Y[i-1][j+1]-Y[i-1][j];
    }
}

double fatorial(int N) {
    double cont1=1;
    for (int i=N; i>0; i--) {
        cont1=cont1*i;
    }
    return cont1;
}

double intervalo(double tabela[][max], int n) {
    int acho=0, i;
    double hh, h;
    h = tabela[0][1]-tabela[0][0];
    printf("\nh : %lf\n", h);
    for (i=1; i<n && acho == 0; i++) {
        acho=0;
        hh=tabela[0][i]-tabela[0][i-1];
        printf("\nhh : %lf\n", hh);
        if (fabs(h - hh) > 1e-9) {
            acho=1;
            printf("\nh e hh: %lf e %lf\n", h, hh);
        }
    }
    printf("\nacho : %d\n", acho);
    if (acho== 1)return 0;
    if (acho== 0)return h;
}

void mostra(double a0, double a1, double Y_ajustado[], int n) {
    int i;

    printf("\na0 = %.4lf\na1 = %.4lf\n\n", a0, a1);
    printf("Vetor Y ajustado exponencial:\n");
    for (i=0; i<n; i++)
        printf("%.4lf ", Y_ajustado[i]);
}

void Newton_Gregory(int n, double tabela[][max], double h, double x) {
    double s, conts=0, polinomio=0;
    double X[max], Y[max][max]; // DY = Delta Y
    int i, t = 1, j;

    // copia informacao para vetor invés de usar matriz
    for (i=0; i<n; i++)
        X[i]=tabela[0][i];

    for (i = 0; i < n; i++)
        Y[0][i]=tabela[1][i];

    // calcula s
    s = (x-X[0])/h;
    // calcula deltas
    for (i=n; i>0; i--, t++) {
        Calcula_DY(Y, i, t);
    }
    t = n;
    printf("Vetor Y:\n");
    for (i=0; i<n; i++, t--) {
        for (j=0; j<t; j++) {
            printf("%.4lf ", Y[j][i]);
        }
        printf("\n");
    }

    polinomio = Y[0][0];
    conts = 1;
    // para polinomio
    for (i=0; i<n-1; i++) {
        conts *= (s - i);
        polinomio += (conts * Y[i+1][0])/fatorial(i+1);
    }
    printf("\nO polinomio no ponto %lf vale: %.4lf\n", x, polinomio);
}

int main() {
    int n, grau, i;
    double tabela[max][max], h, x;
    while (1) {
        printf("Digite a qtd de numeros tabelados: ");
        scanf("%d", &n);

        printf("Digite os pontos tabelados em formato x|y\n");
        for (i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%lf", &tabela[i][j]);
            }
        }
        printf("Digite o ponto a ser calculado: ");
        scanf("%lf", &x);

        h = intervalo(tabela, n);
        printf("\nmain h: %lf\n", h);
        if (h != 0)
            Newton_Gregory(n, tabela, h, x);
    }
    return 0;
}
