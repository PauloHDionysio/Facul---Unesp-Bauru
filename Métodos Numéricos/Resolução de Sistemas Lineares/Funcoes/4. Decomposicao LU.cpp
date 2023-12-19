#include <stdio.h>
#define MAX 10

double somatorioU(int i, int j, double M[][MAX], double L[][MAX], double U[][MAX]) {
    double cont = 0;
    int k;
    for (k = 0; k < i; k++) {
        cont += L[i][k] * U[k][j];
    }

    return cont;
}

void MU(int i, int n, double M[][MAX], double L[][MAX], double U[][MAX]) {
    int j;
    for (j = 0; j < n; j++) {
        if (i == 0) {
            U[i][j] = M[i][j];
			printf("\nMatriz U[%d][%d] = %.2lf\n", i, j, U[i][j]);
        } else {
            U[i][j] = M[i][j] - somatorioU(i, j, M, L, U);
			printf("\nMatriz U[%d][%d] = %.2lf\n", i, j, U[i][j]);
        }
    }
}

double somatorioL(int i, int j, double M[][MAX], double L[][MAX], double U[][MAX]) {
    double cont = 0;
    int k;
    for (k = 0; k < j; k++) {
        cont += L[i][k] * U[k][j];
    }

    return cont;
}

void ML(int j, int n, double M[][MAX], double L[][MAX], double U[][MAX]) {
    int i;
    for (i = 0; i < n; i++) {
        if (j == 0) {
            L[i][j] = M[i][j] / U[j][j];
			printf("\nMatriz L[%d][%d] = %.2lf\n", i, j, L[i][j]);
        } else {
            L[i][j] = (M[i][j] - somatorioL(i, j, M, L, U)) / U[j][j];
			printf("\nMatriz L[%d][%d] = %.2lf\n", i, j, L[i][j]);
        }
    }
}

void resolverSistema(int n, double L[][MAX], double U[][MAX], double B[], double X[]) {
    int i, j, k;
    double Y[MAX];

    //Ly = B
    Y[0] = B[0] / L[0][0];
    for (i = 1; i < n; i++) {
        double soma = 0;
        for (j = 0; j < i; j++) {
            soma += L[i][j] * Y[j];
        }
        Y[i] = (B[i] - soma) / L[i][i];
    }

    //Ux = y
    X[n - 1] = Y[n - 1] / U[n - 1][n - 1];
    for (i = n - 2; i >= 0; i--) {
        double soma = 0;
        for (j = i + 1; j < n; j++) {
            soma += U[i][j] * X[j];
        }
        X[i] = (Y[i] - soma) / U[i][i];
    }
}

void MLU(int t, double M[][MAX], double X[], double B[]) {
    int i, j;
    double U[MAX][MAX], L[MAX][MAX];

    for (i = 0; i < t; i++) {
        MU(i, t, M, L, U);
        ML(i, t, M, L, U);
    }

    resolverSistema(t, L, U, B, X);
}

int main() {
    double A[MAX][MAX], X[MAX], B[MAX];
    int i, n, j;

    printf("Digite a ordem da matriz: ");
    scanf("%d", &n);

    printf("\nDigite a matriz\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("Digite o vetor B\n");
    for (i = 0; i < n; i++) {
        scanf("%lf", &B[i]);
    }

    printf("\n\nA matriz eh:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%.2lf ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nO vetor B eh: \n");
    for (i = 0; i < n; i++) {
        printf("%.2lf ", B[i]);
    }

    MLU(n, A, X, B);

    printf("\n\nO vetor X eh: \n(");
    for (i = 0; i < n; i++) {
        printf(" %.2lf ", X[i]);
    }
    printf(")\n");

    return 0;
}
