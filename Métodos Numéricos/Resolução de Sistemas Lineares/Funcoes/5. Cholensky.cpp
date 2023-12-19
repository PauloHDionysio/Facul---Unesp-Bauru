#include <stdio.h>
#include <math.h>
#include <string.h>
#define max 10

double somatorioPrincipal(int i, double L[][max]) {
    double cont = 0;
    for (int k = 0; k < i; k++) {
        cont += pow(L[i][k], 2);
    }
    return cont;
}

void DPrincipal(int i, double M[][max], double L[][max]) {
    if (i == 0) {
        L[0][0] = sqrt(M[0][0]);
        printf("\n\nMatriz L[0][0]: %.4lf\n\n", L[0][0]);
    } else {
        L[i][i] = sqrt(M[i][i] - somatorioPrincipal(i, L));
        printf("Matriz L[%i][%i]: %.4lf\n\n", i, i, L[i][i]);
    }
}

double somatorioResto(int i, int j, double L[][max]) {
    double cont = 0;
    for (int k = 0; k < j; k++) {
        cont += L[i][k] * L[j][k];
    }
    return cont;
}

void DResto(int i, int j, double M[][max], double L[][max]) {
    if (i == 0) {
        L[i][j] = M[i][j] / L[i][i];
        printf("Matriz L[%d][%d] = %.4lf\n\n", i, j, L[i][j]);
        L[j][i] = L[i][j];
        printf("Matriz L[%d][%d] = %.4lf\n\n", j, i, L[j][i]);
    } else {
        L[i][j] = (M[i][j] - somatorioResto(i, j, L)) / L[j][j];
        printf("Matriz L[%d][%d] = %.4lf\n\n", i, j, L[i][j]);
    }
}

// double somatoriaEQLY(int j, int i, double L[][10], double X[]) {
//     double cont = 0;
//     for (; j <= i - 1; j++) {
//         cont += L[i][j] * X[j];
//     }
//     return cont;
// }

void EQLY(int t, double L[][max], double Y[], double B[]) {
    int i, j;

    printf("\nVetor Y:");
    for (i = 0; i < t; i++) {
        double sum = B[i];
        for (j = 0; j < i; j++) {
            sum -= L[i][j] * Y[j];
        }
        Y[i] = sum / L[i][i];
        printf("\nY[%d] = %.2lf", i, Y[i]);
    }
}

// double somatoriaEQUX(int j, int i, double M[][10], double X[]) {
//     double cont = 0;
//     int aux;
//     aux = j;
//     for (; j < i; j++) {
//         cont += M[aux][j] * X[j];
//     }
//     return cont;
// }

void EQUX(double t, double LT[][max], double X[], double Y[]) {
    int i, j;

    printf("\nVetor X:");
    for (i = t - 1; i >= 0; i--) {
        double sum = Y[i];
        for (j = t - 1; j > i; j--) {
            sum -= LT[i][j] * X[j];
        }
        X[i] = sum / LT[i][i];
        printf("\nX[%d] = %.2lf", i, X[i]);
    }
}

void MCHO(int t, double M[][10], double X[], double B[]) {
    int i, j;
    double L[max][max];

    for (i = 0; i < t; i++) {
        for (j = 0; j < i; j++) {
            DResto(i, j, M, L);
        }
        DPrincipal(i, M, L);
    }

    double Y[max];
    EQLY(t, L, Y, B);

    printf("\n\nMatriz L\n\n");
    for (i = 0; i < t; i++) {
        for (j = 0; j < t; j++) {
            printf("%.2lf ", L[i][j]);
        }
        printf("\n");
    }

    double LT[max][max];
    for (i = 0; i < t; i++) {
        for (j = 0; j < t; j++) {
            LT[i][j] = L[j][i];
        }
    }

    printf("\n\nTransposta:\n");
    for (i = 0; i < t; i++) {
        for (j = 0; j < t; j++) {
            printf("%.2lf ", LT[i][j]);
        }
        printf("\n");
    }

    EQUX(t, LT, X, Y);
}

int main() {
    double A[max][max], X[max], B[max];
    int i, j;
    int n;

    printf("Digite a ordem da matriz: ");
    scanf("%d", &n);

    printf("\nDigite a matriz\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("\nDigite o vetor B\n");
    for (i = 0; i < n; i++) {
        scanf("%lf", &B[i]);
    }

    printf("\nA matriz eh:\n");
    for (i = 0; i < n; i++) {
        printf("\n");
        for (j = 0; j < n; j++) {
            printf("%.4lf ", A[i][j]);
        }
    }

    printf("\n\nO vetor B eh: \n(");

    for (i = 0; i < n; i++) {
        printf(" %.4lf ", B[i]);
    }
    printf(")\n");

    MCHO(n, A, X, B);

    printf(" \n\nO vetor X eh: \n(");

    for (i = 0; i < n; i++) {
        printf(" %.4lf ", X[i]);
    }

    printf(")");

    return 0;
}
