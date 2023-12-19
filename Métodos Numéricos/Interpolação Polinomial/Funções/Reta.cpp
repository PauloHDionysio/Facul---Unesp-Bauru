#include <stdio.h>
#define max 100

double somatorio(double V[], int t){
	int i;
	double cont=0;
	
	for(i=0 ; i<t ; i++)
		cont+=V[i];
	
	return cont;
}
double somatorioXX(double V[], int tam){
	int i;
	double cont=0;
	
	for(i=0 ; i<tam ; i++)
		cont+=(V[i]*V[i]);
	
	return cont;
}

double somatorioXY(double V[], double Z[], int tam){
	int i;
	double cont=0;
	
	for(i=0 ; i<tam ; i++)
		cont+=(V[i]*Z[i]);
	
	return cont;
}

void FY_ajusteReta (double Y_ajustado[], double a0, double a1, double X[], int  n){
	int i;
	
	for(i=0 ; i<n ; i++)
		Y_ajustado[i] = a0 + a1*X[i];
	
}


void mostra(double a0, double a1, double Y_ajustado[], int n){
	int i;
	
	printf("\na0 = %.4lf\na1 = %.4lf\n\n", a0, a1);
	printf("Vetor Y ajusatado reta:\n");

	printf("Y = %.4lf + %.4lf*x\n\n", a0, a1);

	for(i=0 ; i<n ; i++)
	printf("%.4lf ", Y_ajustado[i]);
	
}

void Ajuste_reta(int n, double tabela[][max], double a0, double a1, double Y_ajustado[]){
	double Y[max], X[max];
	int i;
	double somaX, somaY, somaXX, somaXY;
	
	//copia informacao pra vetor inves de usar matriz
	for(i=0 ; i<n ; i++)
		X[i] = tabela[0][i];
	
	for(i=0 ; i<n ; i++)
		Y[i] = tabela[1][i];
	
	somaX = somatorio(X, n);
	somaY = somatorio(Y, n);
	somaXX = somatorioXX(X, n);
	somaXY = somatorioXY(X, Y, n);
	
	a1 = (n*somaXY - somaX*somaY)/(n*somaXX - somaX*somaX);
	a0 = (somaY - a1*somaX)/n;
	
	FY_ajusteReta (Y_ajustado, a0, a1, X, n);
 	
 	mostra(a0, a1, Y_ajustado, n);
	
}



int main (){
	int n, grau;
	double tabela[max][max], a0, a1, Y_ajustado[max];
	
	printf("Digite a qtd de numeros tabelados: ");
	scanf("%d", &n);
	
	printf("Digite os pontos tabelados em formato x|y\n");
	for(int i=0; i<2 ; i++){
		for(int j=0; j<n ; j++){
			scanf("%lf", &tabela[i][j]);
		}
	}
	
	Ajuste_reta(n, tabela, a0, a1, Y_ajustado);
	

}
