#include <stdio.h>
#define MAX 10

void gaussCompacto(int ordem, double matriz[][MAX], double inversa[][MAX]) {
    double matriz_aumentada[MAX][2 * MAX];
    
    // Concatenar matriz com a matriz identidade
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            matriz_aumentada[i][j] = matriz[i][j];
            matriz_aumentada[i][j + ordem] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Aplicar o algoritmo de Gauss compacto
    for (int i = 0; i < ordem; i++) {
        // Encontrar o pivô
        double pivo = matriz_aumentada[i][i];
        if (pivo == 0.0) {
            // Se o pivô for zero, trocar com uma linha abaixo que tenha um elemento não zero na mesma coluna
            int troca = 0;
            for (int j = i + 1; j < ordem; j++) {
                if (matriz_aumentada[j][i] != 0.0) {
                    // Trocar a linha atual com outra linha que tenha um elemento não zero
                    troca = 1;
                    for (int k = 0; k < 2 * ordem; k++) {
                        double temp = matriz_aumentada[i][k];
                        matriz_aumentada[i][k] = matriz_aumentada[j][k];
                        matriz_aumentada[j][k] = temp;
                    }
                    break;
                }
            }
            if (troca == 0) {
                // Se não for possível encontrar um pivô não zero, a matriz não tem inversa
                printf("A matriz não tem inversa.\n");
                return;
            }
            pivo = matriz_aumentada[i][i];
        }

        // Dividir a linha pelo pivô
        for (int j = 0; j < 2 * ordem; j++) {
            matriz_aumentada[i][j] /= pivo;
        }

        // Reduzir as outras linhas
        for (int k = 0; k < ordem; k++) {
            if (k != i) {
                double fator = matriz_aumentada[k][i];
                for (int j = 0; j < 2 * ordem; j++) {
                    matriz_aumentada[k][j] -= fator * matriz_aumentada[i][j];
                }
            }
        }
    }

    // Extrair a matriz inversa
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            inversa[i][j] = matriz_aumentada[i][j + ordem];
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

    gaussCompacto(ordem, matriz, inversa);

    printf("\nA matriz inversa, calculada pelo metodo de Gauss Compacto e:\n");
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            printf("%.5lf  ", inversa[i][j]);
        }
        printf("\n");
    }

    return 0;
}
