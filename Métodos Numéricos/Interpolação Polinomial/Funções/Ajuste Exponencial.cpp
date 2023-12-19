#include <stdio.h>
#include <math.h>
#define max 100
double somatorioerro(double Y[], double Y_medio[], int t){
	double cont=0;
	int i;
	
	for(i=0 ; i<t ; i++){
		cont += pow(Y_medio[i],2);
	}
	
	return cont;
}

void FY_medio(double Y[], double Y_ajustado[], double Y_medio[], int t){
	int i;
	
	for(i=0 ; i<t ; i++){
		Y_medio[i]= Y[i] - Y_ajustado[i];
	}
}

double somatorioX(double V[], int t){
	int i;
	double cont=0;
	
	for(i=0 ; i<t ; i++)
		cont+=V[i];
	
	return cont;
}

double somatorioY(double V[], int t){
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

void FY_ajusteExpo (double Y_ajustado[], double a0, double a1, double X[], int  n){
	int i;
	
	for(i=0 ; i<n ; i++)
	Y_ajustado[i] = a0 + a1*X[i];
}

void mostra(double a0, double a1, double Y_ajustado[], int n){
	int i;
	
	printf("\na0 = %.4lf\na1 = %.4lf\n", a0, a1);
	printf("\nY = ab^x\nY = %.4lf * %.4lf^x\n\n", a0, a1);
	printf("Vetor Y ajusatado exponencial:\n");
	for(i=0 ; i<n ; i++)
	printf("%.4lf ", Y_ajustado[i]);
	printf("\n");
}

void coefDeterminacao(double Y[], double Y_ajustado[], int n){
	double R2=0;
	double erro=0, numerador=0, denominador=0, Y_medio[max], somaY, somaYY;
	int i;
	
	FY_medio(Y, Y_ajustado, Y_medio, n);
	
	printf("Vetor Y medio:\n");
	for(i=0 ; i<n ; i++)
	printf("%.4lf ", Y_medio[i]);
	
	erro = somatorioerro(Y, Y_medio, n);
	somaY = somatorioX(Y, n);
	somaYY = somatorioXX(Y, n);
	
	printf("\nerro: %lf\nsomaYY: %lf\n soma Y2: %lf", erro, somaYY, somaY);
	
	
	numerador= n*erro;
	denominador= n*somaYY - somaY*somaY;
	
	R2 = 1 - numerador/denominador;
	printf("\nO erro eh: %lf\n", R2);
}

void Ajuste_Expo(int n, double tabela[][max], double a0, double a1, double Y_ajustado[]){
	double Y[max], X[max];
	int i;
	double somaX, somaY, somaXX, somaXY;
	double a, b;
	
	//copia informacao pra vetor inves de usar matriz
	for(i=0 ; i<n ; i++)
		X[i] = tabela[0][i];
	
	for(i=0 ; i<n ; i++)
		Y[i] = log(tabela[1][i]);
	printf("\nVetor Y\n");
	for(i=0 ; i<n ; i++)
	printf("%.4lf ", Y[i]);
	
	somaX = somatorioX(X, n);
	somaY = somatorioY(Y, n);
	somaXX = somatorioXX(X, n);
	somaXY = somatorioXY(X, Y, n);
	
	printf("\nsomaX= %.4lf\nsomaY= %.4lf\nsomaXX= %.4lf\nsomaXY= %.4lf\n",somaX ,somaY, somaXX, somaXY);
	
	b = (n*somaXY - somaX*somaY)/(n*somaXX - somaX*somaX);
	a = (somaY - b*somaX)/n;
	
	printf("\na= %.4lf\nb= %.4lf\n",a,b);
	a0 = exp(a);
	a1 = exp(b);
	
	FY_ajusteExpo(Y_ajustado, a, b, X, n);
 	
 	mostra(a0, a1, Y_ajustado, n);
	coefDeterminacao(Y, Y_ajustado, n);
}



int main (){
	int n, grau, i;
	double tabela[max][max], a0, a1, Y_ajustado[max];
	
	printf("Digite a qtd de numeros tabelados: ");
	scanf("%d", &n);
	
	printf("Digite os pontos tabelados em formato x|y\n");
	for(int i=0; i<2 ; i++){
		for(int j=0; j<n ; j++){
			scanf("%lf", &tabela[i][j]);
		}
	}
	
	printf("\nVetor X exponencial:\n");
	for(i=0 ; i<n ; i++)
	printf("%.0lf ", tabela[0][i]);
	
	printf("\nVetor Y exponencial:\n");
	for(i=0 ; i<n ; i++)
	printf("%.0lf ", tabela[1][i]);
	
	Ajuste_Expo(n, tabela, a0, a1, Y_ajustado);
	

}
