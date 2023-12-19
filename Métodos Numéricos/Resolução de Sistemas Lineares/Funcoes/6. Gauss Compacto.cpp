#include <stdio.h>
#define MAX 10

void GaussCompacto(int n, double A[][MAX], double B[]) {
    int i, j, k;
    double cont;

    for (k = 0; k < n - 1; k++) {
        for (i = k + 1; i < n; i++) {
            cont = A[i][k] / A[k][k];
            B[i] -= cont * B[k];
            for (j = k; j < n; j++) {
                A[i][j] -= cont * A[k][j];
            }
        }
    }
}

void vetorX(int n, double A[][MAX], double B[], double X[]) {
    int i, j;
    double cont;

    X[n-1] = B[n-1] / A[n-1][n-1];

    for (i = n-2; i >= 0; i--) {
        cont = B[i];
        for (j = i + 1; j < n; j++) {
            cont -= A[i][j] * X[j];
        }
        X[i] = cont / A[i][i];
    }
}

int main() {
    int n, i, j;
    double A[MAX][MAX], B[MAX];
    double X[MAX];

    printf("Digite a ordem da matriz: ");
    scanf("%d", &n);

    printf("\nDigite a matriz A:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("\nDigite o vetor B:\n");
    for (i = 0; i < n; i++) {
        scanf("%lf", &B[i]);
    }

    GaussCompacto(n, A, B);
    vetorX(n, A, B, X);

    printf("\n\nMatriz A Compacta \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%.2lf ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("\nVetor B Compacto = ( ");
    for (i = 0; i < n; i++) {
        printf("%.2lf ", B[i]);
    }
    printf(")");
    printf("\n");

    printf("\nVetor X = (");
    for (i = 0; i < n; i++) {
        printf(" %.2lf ", X[i]);
    }
    printf(")");

    return 0;
}
