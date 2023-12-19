#include <stdio.h>
#include <stdlib.h>
#define MAX 10

void decomposicaoLU(int ordem, double matriz[][MAX], double L[][MAX], double U[][MAX]) {
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            U[i][j] = matriz[i][j];
        }
    }

    for (int k = 0; k < ordem; k++) {
        L[k][k] = 1.0;

        for (int i = k + 1; i < ordem; i++) {
            L[i][k] = U[i][k] / U[k][k];
            for (int j = k; j < ordem; j++) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
    }
}

void matrizInversa(int ordem, double matriz[][MAX], double inversa[][MAX]) {
    double L[MAX][MAX];
    double U[MAX][MAX];
    double identidade[MAX][MAX];

    // Inicializar matriz identidade
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            if (i == j) {
                identidade[i][j] = 1.0;
            } else {
                identidade[i][j] = 0.0;
            }
        }
    }

    decomposicaoLU(ordem, matriz, L, U);

    // Resolver sistema Ly = I
    for (int k = 0; k < ordem; k++) {
        double y[MAX];

        for (int i = 0; i < ordem; i++) {
            double soma = 0.0;
            for (int j = 0; j < i; j++) {
                soma += L[i][j] * y[j];
            }
            y[i] = (identidade[i][k] - soma) / L[i][i];
        }

        // Resolver sistema Ux = y
        for (int i = ordem - 1; i >= 0; i--) {
            double soma = 0.0;
            for (int j = i + 1; j < ordem; j++) {
                soma += U[i][j] * inversa[j][k];
            }
            inversa[i][k] = (y[i] - soma) / U[i][i];
        }
    }
}

int main() {
    int ordem;
    double matriz[MAX][MAX];
    double inversa[MAX][MAX];
    
    printf("Digite a ordem da matriz: ");
    scanf("%d", &ordem);

    printf("\nDigite os valores da matriz %d X %d: \n", ordem, ordem);
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            scanf("%lf", &matriz[i][j]);
        }
    }

    matrizInversa(ordem, matriz, inversa);

    printf("\nA matriz inversa, por decomposicao LU e:\n");
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            printf("%.5lf  ", inversa[i][j]);
        }
        printf("\n");
    }

    return 0;
}
