#include <stdio.h>
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

