#include <stdio.h>
#define MAX 10

void jacobi(int ordem, double matriz[][MAX], double vetorB[], double aproximacao[], double e, int maxIter, double solucao[], int* numIter) {
    double x[MAX], temp[MAX];
    int i, j, iter;

    for (iter = 1; iter <= maxIter; iter++) {
        double erro = 0.0;

        for (i = 0; i < ordem; i++) {
            temp[i] = vetorB[i];
            for (j = 0; j < ordem; j++) {
                if (i != j) {
                    temp[i] -= matriz[i][j] * aproximacao[j];
                }
            }
            temp[i] /= matriz[i][i];
        }

        for (i = 0; i < ordem; i++) {
            erro += (temp[i] - aproximacao[i]) * (temp[i] - aproximacao[i]);
        }

        for (i = 0; i < ordem; i++) {
            aproximacao[i] = temp[i];
        }

        if (erro < e) {
            break;
        }
    }

    for (i = 0; i < ordem; i++) {
        solucao[i] = aproximacao[i];
    }

    *numIter = iter;
}

int main() {
    int ordem, maxIter, numIter;
    double matriz[MAX][MAX], vetorB[MAX], aproximacao[MAX], solucao[MAX], e;

    printf("Digite a ordem do sistema: ");
    scanf("%d", &ordem);

    printf("Digite a matriz dos coeficientes:\n");
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            scanf("%lf", &matriz[i][j]);
        }
    }

    printf("Digite o vetor dos termos independentes:\n");
    for (int i = 0; i < ordem; i++) {
        scanf("%lf", &vetorB[i]);
    }

    printf("Digite a aproximacao inicial para a solucao:\n");
    for (int i = 0; i < ordem; i++) {
        scanf("%lf", &aproximacao[i]);
    }

    printf("Digite o valor de e (posicao desejada):\n");
    scanf("%lf", &e);

    printf("Digite o numero maximo de iteracoes: ");
    scanf("%d", &maxIter);

    jacobi(ordem, matriz, vetorB, aproximacao, e, maxIter, solucao, &numIter);

    printf("O vetor solucao sera:\n");
    for (int i = 0; i < ordem; i++) {
        printf("%.4lf ", solucao[i]);
    }
    printf("\n");

    printf("Número de iterações realizadas: %d\n", numIter);

    return 0;
}
