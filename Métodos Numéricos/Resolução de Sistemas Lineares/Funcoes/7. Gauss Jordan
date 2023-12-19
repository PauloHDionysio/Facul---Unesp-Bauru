#include <stdio.h>
#include <stdlib.h>
#define MAX 10

void gauss_jordan(int ordem, int max, double matriz[][MAX], double vetor_independente[MAX], double solucao[MAX]) {
    double matriz_aumentada[MAX][MAX + 1];

    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem + 1; j++) {
            if (j == ordem) {
                matriz_aumentada[i][j] = vetor_independente[i];
            }
            else {
                matriz_aumentada[i][j] = matriz[i][j];
            }
        }
    }

    for (int i = 0; i < ordem; i++) {
        double pivo = matriz_aumentada[i][i];

        // Verificar se o pivô é igual a zero
        if (pivo == 0.0) {
            printf("\nSistema Indeterminado.\n");
        }
		else {
            for (int j = i; j <= ordem; j++) {
                matriz_aumentada[i][j] /= pivo;
            }

            for (int k = 0; k < ordem; k++) {
                if (k != i) {
                    double fator = matriz_aumentada[k][i];
                    for (int j = i; j <= ordem; j++) {
                        matriz_aumentada[k][j] -= fator * matriz_aumentada[i][j];
                    }
                }
            }
        }
    }

    for (int i = 0; i < ordem; i++) {
        solucao[i] = matriz_aumentada[i][ordem];
    }
}

int main() {
    int ordem;
    double matriz[MAX][MAX];
    double vetor_independente[MAX];
    double solucao[MAX];

    printf("Digite a ordem da matriz: ");
    scanf("%d", &ordem);

    printf("\nDigite os valores da matriz %d X %d: \n", ordem, ordem);
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            scanf("%lf", &matriz[i][j]);
        }
    }

    printf("\n\nDigite o vetor independente (B): ");
    for (int i = 0; i < ordem; i++) {
        scanf("%lf", &vetor_independente[i]);
    }

    gauss_jordan(ordem, MAX, matriz, vetor_independente, solucao);

    printf("\nSolucao:\n");
    for (int i = 0; i < ordem; i++) {
        printf("%.5lf\n", solucao[i]);
    }

    return 0;
}
