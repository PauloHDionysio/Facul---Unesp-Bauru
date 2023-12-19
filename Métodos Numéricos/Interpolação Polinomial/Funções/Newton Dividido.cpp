#include <stdio.h>
#include <math.h>
#define max 100

void Calcula_DYD(double Y[][max], double X[], int n, int i){
	int j;
	for(j=0 ; j<n-1 ; j++){
		Y[i][j] = (Y[i-1][j+1] - Y[i-1][j])/(X[i+j] - X[j]);
	}
}

void Newton_Dividido(int n, double tabela[][max], double x){
	double polinomio=0, contx=0;
	double X[max], Y[max][max]; 	//DY = Delta Y
	int i, t=1, j;
	
	//copia informacao pra vetor inves de usar matriz
	for(i=0 ; i<n ; i++)
		X[i] = tabela[0][i];
	
	for(i=0 ; i<n ; i++)
		Y[0][i] = tabela[1][i];
	
	//calcula deltas
	for(i=n ; i>0 ; i--, t++){
		Calcula_DYD(Y, X, i, t);
	}
	t=n;
	printf("\nVetor Y:\n");
	for(i=0 ; i<n ; i++, t--){
	for(j=0 ; j<t ; j++)
	printf("%.3lf ", Y[i][j]);
	printf("\n");
}
	
	polinomio = Y[0][0];
	contx = 1;
	//para polinomio
	for(i=0 ; i<n-1 ; i++){
	contx *= (x - X[i]);
	polinomio += (contx*Y[i+1][0]);
	printf("\nO polinomio: %lf\nO contx vale: %lf\n", polinomio, contx);
	}
	printf("\nO polinomio no ponto %lf vale: %lf\n", x, polinomio);
}
	

int main (){
	int n, grau, i;
	double tabela[max][max], h, x;
	while(true){
	
	printf("\n\nDigite a qtd de numeros tabelados: ");
	scanf("%d", &n);
	
	printf("Digite os pontos tabelados em formato x|y\n");
	for(int i=0; i<2 ; i++){
		for(int j=0; j<n ; j++){
			scanf("%lf", &tabela[i][j]);
		}
	}
	printf("Digite o ponto a ser calculado: ");
	scanf("%lf", &x);
	
	Newton_Dividido(n, tabela, x);
}

}
