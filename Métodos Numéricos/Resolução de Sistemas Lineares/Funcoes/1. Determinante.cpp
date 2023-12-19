#include <stdio.h>
#define MAX 10

double det(int t, double M[][MAX]) {
    if (t == 1) {
        return M[0][0];
    } else {
        double cont = 0;
        int i, jj, ii, aux, col;
        
        // Iterar sobre a primeira linha da matriz
        for (i = 0; i < t; i++) {
            if (M[0][i] != 0) {
                ii = jj = 0;
                double A1[MAX][MAX];
                
                // Construir a matriz A1 removendo a primeira linha e a coluna atual
                for (aux = 1; aux < t; aux++) {
                    for (col = 0; col < t; col++) {
                        if (col != i) {
                            A1[ii][jj] = M[aux][col];
                            jj++;
                        }
                    }
                    ii++;
                    jj = 0;
                }
                
                double factor = (i % 2 == 0) ? M[0][i] : -M[0][i];
                cont = cont + factor * det(t - 1, A1);
            }
        }
        return cont;
    }
}

int main() {
    double A[MAX][MAX];
    int i, n, j;
    
    printf("Digite a ordem da matriz: ");
    scanf("%d", &n);
    
    printf("\nDigite a matriz %d x %d:\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }
    
    printf("\nA matriz inserida foi:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%.0lf ", A[i][j]);
        }
        printf("\n");
    }
    
    printf("\nO determinante da matriz e: %.0lf\n", det(n, A));
    
    return 0;
}
