//Interpolação Polinomial e Ajuste de Curvas - Métodos Numéricos Computacionais
/*Trabalho feito por:
	Enzo Campanholo Paschoalini - RA: 221026215
	Manuele S. Christófalo - RA: 221029261
	Paulo Henrique de Camargo Dionysio Martins - RA: 221026169
	Thiago Bigotte Gullo - RA: 221026241
*/
//UNESP Bauru - 02/07/2023
//OBS: o ajuste de ponto ao polinômio é calculado através de Decomposição LU

#include <bits/stdc++.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
using namespace std;

#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define UP 72
#define DOWN 80

#define BRANCO 127
#define PRETO 112
#define CINZA 120
#define VERDE 114
#define AZUL 113
#define CIANO 115
#define VERMELHO 116

#define MAX 100

int n, grau;
double tabela[2][MAX], A[MAX], Y_ajustado[MAX], x, h;

//FORMATAÇÃO ==========================================================================================================
void gotoxy(int x, int y){ //Posição do cursor
	COORD pos={x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void cursor(bool val){ //Esconde o cursor
   HANDLE consoleHandle=GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize=10;
   info.bVisible=val;
   SetConsoleCursorInfo(consoleHandle, &info);
}

int SetColor(char color){ //Cor
	HANDLE h;
	h=GetStdHandle(STD_OUTPUT_HANDLE);
	return SetConsoleTextAttribute(h,color);
}

void limpaTela(){ //Limpa a tela
	system("cls");
	SetColor(CINZA);
}

void menuSelecao(int pos){ //Menu de Seleção
	limpaTela();
	SetColor(AZUL); cout << "\n Qual a operacao desejada?\n\n\n"; SetColor(BRANCO);
	cout << "  Calcular polinomio interpolado por Newton" << endl;
	cout << "  Calcular polinomio interpolado por Newton-Gregory" << endl;
	cout << "  Ajustar os pontos tabelados a uma reta da forma y=a0+a1x" << endl;
	cout << "  Ajustar os pontos tabelados a um polinomio de grau desejado" << endl;
	cout << "  Ajustar os pontos tabelados a uma curva exponencial da forma y=ab^x" << endl;
	cout << "  SAIR";

	switch(pos){
		case 1: gotoxy(2, 4); SetColor(CINZA); cout << "  Calcular polinomio interpolado por Newton" << endl; break;
		case 2: gotoxy(2, 5); SetColor(CINZA); cout << "  Calcular polinomio interpolado por Newton-Gregory" << endl; break;
		case 3: gotoxy(2, 6); SetColor(CINZA); cout << "  Ajustar os pontos tabelados a uma reta da forma y=a0+a1x" << endl; break;
		case 4: gotoxy(2, 7); SetColor(CINZA); cout << "  Ajustar os pontos tabelados a um polinomio de grau desejado" << endl; break;
		case 5: gotoxy(2, 8); SetColor(CINZA); cout << "  Ajustar os pontos tabelados a uma curva exponencial da forma y=ab^x" << endl; break;
		case 6: gotoxy(2, 9); SetColor(VERMELHO); cout << "  SAIR"; break;
	}
}

bool voltaMenu(){ //Opção tentar ou voltar
	char saida='a'; cursor(false);
	SetColor(CINZA); cout << endl << endl << "Pressione ";
	SetColor(CIANO); cout << "<ENTER>"; SetColor(CINZA); cout << " para tentar com outros valores ou ";
	SetColor(CIANO); cout << "<ESC>"; SetColor(CINZA); cout << " para voltar ao menu de opcoes.";
	while(saida!=ENTER && saida!=ESC) saida=getch();

	if(saida==ESC) return 1;
	return 0;
}


//FUNÇÕES BASE ========================================================================================================
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


//NEWTON ==============================================================================================================
void Calcula_DYD(double Y[][MAX], double X[], int n, int i){
	int j;
	for(j=0 ; j<n-1 ; j++){
		Y[i][j] = (Y[i-1][j+1] - Y[i-1][j])/(X[i+j] - X[j]);
	}
}

void Newton_Dividido(int n, double tabela[][MAX], double x){
	double polinomio=0, contx=0;
	double X[MAX], Y[MAX][MAX]; 	//DY = Delta Y
	int i, t=1, j;
	
	//copia informacao pra vetor inves de usar matriz
	for(i=0 ; i<n ; i++) X[i] = tabela[0][i];
	
	for(i=0 ; i<n ; i++) Y[0][i] = tabela[1][i];
	
	//calcula deltas
	for(i=n ; i>0 ; i--, t++) Calcula_DYD(Y, X, i, t);
	t=n;

    SetColor(CINZA); cout << endl << "Vetor Y:" << endl; SetColor(BRANCO);
	for(i=0 ; i<n ; i++, t--){
        for(j=0 ; j<t ; j++) cout << fixed << setprecision(3) << Y[i][j] << "  ";
        cout << endl;
    }
	cout << endl;
	
	polinomio = Y[0][0];
	contx = 1;
	//para polinomio
	for(i=0 ; i<n-1 ; i++){
        contx *= (x - X[i]);
        polinomio += (contx*Y[i+1][0]);
        SetColor(CINZA); cout << endl << "Polinomio: "; SetColor(BRANCO); cout << polinomio << endl;
        SetColor(CINZA); cout << "contx: "; SetColor(BRANCO); cout << contx << endl;
	}
	cout << endl << endl;

    SetColor(VERDE); 
    cout << "No ponto " << x << " o polinomio vale: " << fixed << setprecision(4) << polinomio << endl;
}


//NEWTON GREGÓRIO =====================================================================================================
void Calcula_DY(double Y[][MAX], int n, int i) {
    int j;
    for (j=0; j<n-1; j++) {
        Y[i][j]=Y[i-1][j+1]-Y[i-1][j];
    }
}

double fatorial(int N) {
    double cont1=1;
    for (int i=N; i>0; i--) {
        cont1=cont1*i;
    }
    return cont1;
}

double intervalo(double tabela[][MAX], int n) {
    int acho=0, i;
    double hh, h;
    h = tabela[0][1]-tabela[0][0];
    
    for (i=1; i<n && acho == 0; i++) {
        acho=0;
        hh=tabela[0][i]-tabela[0][i-1];
        if (fabs(h - hh) > 1e-9) acho=1;
    }

    if (acho==1) return 0;
    if (acho==0) return h;
}

void Newton_Gregory(int n, double tabela[][MAX], double h, double x) {
    double s, conts=0, polinomio=0;
    double X[MAX], Y[MAX][MAX]; // DY = Delta Y
    int i, t = 1, j;

    // copia informacao para vetor invés de usar matriz
    for (i=0; i<n; i++) X[i]=tabela[0][i];

    for (i = 0; i < n; i++) Y[0][i]=tabela[1][i];

    // calcula s
    s = (x-X[0])/h;

    // calcula deltas
    for (i=n; i>0; i--, t++) Calcula_DY(Y, i, t);
    t = n;

    SetColor(CINZA); cout << "Vetor Y:" << endl; SetColor(BRANCO);
	for(i=0 ; i<n ; i++, t--){
        for(j=0 ; j<t ; j++) cout << fixed << setprecision(3) << Y[i][j] << "  ";
        cout << endl;
    }

    polinomio = Y[0][0];
    conts = 1;
    // para polinomio
    for (i=0; i<n-1; i++) {
        conts *= (s - i);
        polinomio += (conts * Y[i+1][0])/fatorial(i+1);
    }
    cout << endl << endl;

    SetColor(VERDE); 
    cout << "No ponto " << x << " o polinomio vale: " << fixed << setprecision(4) << polinomio << endl;
}


//COEFICIENTE DE DETERMINAÇÃO =========================================================================================
void coefDeterminacao(double Y[], double Y_ajustado[], int n){
	double R2=0;
	double erro=0, numerador=0, denominador=0, Y_medio[MAX], somaY, somaYY;
	
	FY_medio(Y, Y_ajustado, Y_medio, n);
	
	SetColor(CINZA); cout << endl << "Vetor Y medio: "; SetColor(BRANCO);
	for(int i=0; i<n ; i++) cout << fixed << setprecision(4) << Y_medio[i] << "  ";
	
	erro = somatorioerro(Y, Y_medio, n);
	somaY = somatorio(Y, n);
	somaYY = somatorioXX(Y, n);
	
	cout << endl;
	SetColor(CINZA); cout << endl << "Erro: "; SetColor(BRANCO); cout << erro;
	SetColor(CINZA); cout << endl << "Soma YY: "; SetColor(BRANCO); cout << somaYY;
	SetColor(CINZA); cout << endl << "Soma Y2: "; SetColor(BRANCO); cout << somaY << endl;	
	
	numerador= n*erro;
	denominador= n*somaYY - somaY*somaY;
	
	R2 = 1 - numerador/denominador;
	SetColor(CINZA); cout << endl << "O erro eh: "; SetColor(BRANCO); cout << R2 << endl;
}


//AJUSTE RETA =========================================================================================================
void FY_ajusteReta(double Y_ajustado[], double a0, double a1, double X[], int  n){
	int i;
	
	for(i=0 ; i<n ; i++)
		Y_ajustado[i] = a0 + a1*X[i];
	
}

void mostra(double a0, double a1, double Y_ajustado[], int n){
	int i;
	
	SetColor(CINZA); cout << endl << "a0 = "; SetColor(BRANCO); cout << fixed << setprecision(4) << a0;
	SetColor(CINZA); cout << endl << "a1 = "; SetColor(BRANCO); cout << a1;

	SetColor(VERDE); cout << endl << endl << endl << "Vetor y ajustado a reta (Y = " << a0 << " + " << a1 << "*x):" << endl;
	for(i=0 ; i<n ; i++) cout << Y_ajustado[i] << "  ";
	cout << endl;
}

void Ajuste_reta(int n, double tabela[][MAX], double a0, double a1, double Y_ajustado[]){
	double Y[MAX], X[MAX];
	int i;
	double somaX, somaY, somaXX, somaXY;
	
	//copia informacao pra vetor inves de usar matriz
	for(i=0 ; i<n ; i++) X[i] = tabela[0][i];
	
	for(i=0 ; i<n ; i++) Y[i] = tabela[1][i];
	
	somaX = somatorio(X, n);
	somaY = somatorio(Y, n);
	somaXX = somatorioXX(X, n);
	somaXY = somatorioXY(X, Y, n);
	
	a1 = (n*somaXY - somaX*somaY)/(n*somaXX - somaX*somaX);
	a0 = (somaY - a1*somaX)/n;
	
	FY_ajusteReta(Y_ajustado, a0, a1, X, n);
 	
 	mostra(a0, a1, Y_ajustado, n);
}


//AJUSTE POLINOMIO ====================================================================================================
void substituicaoProgressiva(int n, double L[][MAX], double b[], double x[]) {
    for (int i = 0; i < n; i++) {
        x[i] = b[i];
        for (int j = 0; j < i; j++) {
            x[i] -= L[i][j] * x[j];
        }
        x[i] /= L[i][i];
    }
}

void substituicaoRegressiva(int n, double U[][MAX], double y[], double x[]) {
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
}

void decomposicaoLU(int n, double A[][MAX], double L[][MAX], double U[][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j < i) {
                L[j][i] = 0;
            } else {
                L[j][i] = A[j][i];
                for (int k = 0; k < i; k++) {
                    L[j][i] -= L[j][k] * U[k][i];
                }
            }
        }
        for (int j = 0; j < n; j++) {
            if (j < i) {
                U[i][j] = 0;
            } else if (j == i) {
                U[i][j] = 1;
            } else {
                U[i][j] = A[i][j] / L[i][i];
                for (int k = 0; k < i; k++) {
                    U[i][j] -= (L[i][k] * U[k][j]) / L[i][i];
                }
            }
        }
    }
}

double CoefDeterminacao(int E, double tabela[2][MAX], double vetorY[MAX]) {
    double soma_y = 0.0, soma_y_ajustado = 0.0;
    double sqr = 0.0, sqt = 0.0;
    int i;

    for (i = 0; i < E; i++) {
        soma_y += tabela[1][i];
        soma_y_ajustado += vetorY[i];
    }

    double media_y = soma_y / E;
    for (i = 0; i < E; i++) {
        sqr += pow(tabela[1][i] - vetorY[i], 2);
        sqt += pow(tabela[1][i] - media_y, 2);
    }

    double coef_determinacao = 1 - (sqr / sqt);

    return coef_determinacao;
}

void AjustePolinomio(int E, int grau, double tabela[2][MAX], double vetorA[MAX + 1], double vetorY[MAX], double *coef_determinacao) {
    int n = grau + 1;
    double A[MAX][MAX];
    double b[MAX];

    // Monta a matriz A e o vetor b para o sistema linear
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double soma = 0.0;
            for (int k = 0; k < E; k++) {
                soma += pow(tabela[0][k], i + j);
            }
            A[i][j] = soma;
        }

        double soma = 0.0;
        for (int k = 0; k < E; k++) {
            soma += tabela[1][k] * pow(tabela[0][k], i);
        }
        b[i] = soma;
    }

    double L[MAX][MAX];
    double U[MAX][MAX];
    decomposicaoLU(n, A, L, U);

    double y[MAX];
    substituicaoProgressiva(n, L, b, y);

    substituicaoRegressiva(n, U, y, vetorA);

    for (int i = 0; i < E; i++) {
        vetorY[i] = 0.0;
        for (int j = 0; j < n; j++) {
            vetorY[i] += vetorA[j] * pow(tabela[0][i], j);
        }
    }

    *coef_determinacao = CoefDeterminacao(E, tabela, vetorY);
}


//AJUSTE CURVA ========================================================================================================
void FY_ajusteExpo (double Y_ajustado[], double a0, double a1, double X[], int  n){
	int i;
	
	for(i=0 ; i<n ; i++)
	Y_ajustado[i] = a0 + a1*X[i];
}

void mostraExpo(double a0, double a1, double Y_ajustado[], int n){
	int i;
	
	SetColor(CINZA); cout << endl << "a0 = "; SetColor(BRANCO); cout << a0 << endl;
	SetColor(CINZA); cout << "a1 = "; SetColor(BRANCO); cout << a1 << endl;
	
	SetColor(VERDE); cout << endl << endl << "Vetor Y ajusatado exponencial:" << endl;
	for(i=0 ; i<n ; i++) cout << Y_ajustado[i] << "  ";
	cout << endl;
}

void Ajuste_Expo(int n, double tabela[][MAX], double a0, double a1, double Y_ajustado[]){
	double Y[MAX], X[MAX];
	int i;
	double somaX, somaY, somaXX, somaXY;
	double a, b;
	
	//copia informacao pra vetor inves de usar matriz
	for(i=0 ; i<n ; i++) X[i] = tabela[0][i];
	
	for(i=0 ; i<n ; i++) Y[i] = log(tabela[1][i]);

	SetColor(CINZA); cout << endl << "Vetor Y:" << endl; SetColor(BRANCO);
	for(i=0 ; i<n ; i++) cout << fixed << setprecision(4) << Y[i] << "  ";
	cout << endl;
	
	somaX = somatorio(X, n);
	somaY = somatorio(Y, n);
	somaXX = somatorioXX(X, n);
	somaXY = somatorioXY(X, Y, n);

	cout << endl;
	SetColor(CINZA); cout << endl << "Soma X: "; SetColor(BRANCO); cout << somaX;
	SetColor(CINZA); cout << endl << "Soma Y: "; SetColor(BRANCO); cout << somaY;
	SetColor(CINZA); cout << endl << "Soma XX: "; SetColor(BRANCO); cout << somaXX;
	SetColor(CINZA); cout << endl << "Soma XY: "; SetColor(BRANCO); cout << somaXY << endl;	
	
	b = (n*somaXY - somaX*somaY)/(n*somaXX - somaX*somaX);
	a = (somaY - b*somaX)/n;
	
	SetColor(CINZA); cout << endl << "a = "; SetColor(BRANCO); cout << a;
	SetColor(CINZA); cout << endl << "b = "; SetColor(BRANCO); cout << b << endl;
	a0 = exp(a);
	a1 = exp(b);
	
	FY_ajusteExpo(Y_ajustado, a, b, X, n);
 	
 	mostraExpo(a0, a1, Y_ajustado, n);
	coefDeterminacao(Y, Y_ajustado, n);
}


//MAIN ================================================================================================================
int main(){
    system("color 70");
	HWND console=GetConsoleWindow();
 	RECT r;
  	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 800, 400, TRUE);
	setlocale(LC_ALL, "Portuguese_Brasil");

	bool ON=true;
	int pos;
	char selecao;
	

	//PARTE 1: PROGRAMA
	while(ON==true){
		selecao='a'; pos=1;

		while(selecao!=ENTER){ //1.0 - Controle do menu
			cursor(false);
			menuSelecao(pos);

			if(pos==6) SetColor(VERMELHO);
			else SetColor(AZUL);

			gotoxy(0, 3+pos); cout << ">";

			selecao=getch();
			if(pos!=6) if(selecao==DOWN) pos++;
			if(pos!=1) if(selecao==UP) pos--;
		}
			
		

		//PARTE 2: SELEÇÃO FEITA
		while(pos==1){ //2.1 - Polinomio interpolado por Newton
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Calcular o polinomio interpolado por Newton" << endl; SetColor(BRANCO);

			SetColor(BRANCO); cout << endl << endl << "Insira a quantidade de pontos tabelados (max. 100): ";
            n=0;
            while(n<1 || n>100){
				gotoxy(52, 3); cout << "          "; gotoxy(52, 3);
				SetColor(AZUL); cin >> n;
			}

			SetColor(BRANCO); cout << endl << "Digite os pontos tabelados no formato x y: " << endl; SetColor(AZUL);
            for(int i=0; i<2 ; i++){
                for(int j=0; j<n ; j++) cin >> tabela[i][j];
            }

            SetColor(BRANCO); cout << endl << "Digite o ponto a ser calculado: "; SetColor(AZUL);
            cin >> x;

            SetColor(CINZA); cout << endl << endl; for(int loop=0; loop<80; loop++) cout << "=";
            Newton_Dividido(n, tabela, x);

            SetColor(CINZA); cout << endl; for(int loop=0; loop<80; loop++) cout << "=";
			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==2){ //2.2 - Polinomio interpolado por Newton-Gregory
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Calcular o polinomio interpolado por Newton-Gregory"; SetColor(BRANCO);

			SetColor(BRANCO); cout << endl << endl << endl << "Insira a quantidade de pontos tabelados (max. 100): ";
            n=0;
            while(n<1 || n>100){
				gotoxy(52, 3); cout << "          "; gotoxy(52, 3);
				SetColor(AZUL); cin >> n;
			}

			SetColor(BRANCO); cout << endl << "Digite os pontos tabelados no formato x y: " << endl; SetColor(AZUL);
            for(int i=0; i<2 ; i++){
                for(int j=0; j<n ; j++) cin >> tabela[i][j];
            }

            SetColor(BRANCO); cout << endl << "Digite o ponto a ser calculado: "; SetColor(AZUL);
            cin >> x;

            SetColor(CINZA); cout << endl << endl; for(int loop=0; loop<80; loop++) cout << "=";
			h=intervalo(tabela, n);
			SetColor(CINZA); cout << endl << "Valor h: "; SetColor(BRANCO); cout << h << endl << endl;
            Newton_Gregory(n, tabela, h, x);


            SetColor(CINZA); cout << endl; for(int loop=0; loop<80; loop++) cout << "=";
			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==3){ //2.3 - Ajuste de ponto à reta
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Ajustar os pontos tabelados a uma reta" << endl; SetColor(BRANCO);

			SetColor(BRANCO); cout << endl << endl << "Insira a quantidade de pontos tabelados (max. 100): ";
            n=0;
            while(n<1 || n>100){
				gotoxy(52, 3); cout << "          "; gotoxy(52, 3);
				SetColor(AZUL); cin >> n;
			}

			SetColor(BRANCO); cout << endl << "Digite os pontos tabelados no formato x y: " << endl; SetColor(AZUL);
            for(int i=0; i<2 ; i++){
                for(int j=0; j<n ; j++) cin >> tabela[i][j];
            }

			double a0=0, a1=0;
            SetColor(CINZA); cout << endl << endl; for(int loop=0; loop<80; loop++) cout << "=";
            Ajuste_reta(n, tabela, a0, a1, Y_ajustado);

            SetColor(CINZA); cout << endl; for(int loop=0; loop<80; loop++) cout << "=";
			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==4){ //2.4 - Ajuste de ponto ao polinomio
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Ajuste de pontos tabelados a um polinomio de grau desejado" << endl; SetColor(BRANCO);

			SetColor(BRANCO); cout << endl << "Insira a quantidade de pontos tabelados (max. 100): ";
            n=0;
            while(n<1 || n>100){
				gotoxy(52, 3); cout << "          "; gotoxy(52, 3);
				SetColor(AZUL); cin >> n;
			}

			SetColor(BRANCO); cout << endl << "Insira o grau do polinomio desejado (max. 100): ";
            grau=0;
            while(grau<1 || grau>100){
				gotoxy(48, 5); cout << "          "; gotoxy(48, 5);
				SetColor(AZUL); cin >> grau;
			}

			SetColor(BRANCO); cout << endl << "Digite os pontos tabelados no formato x y: " << endl; SetColor(AZUL);
            for(int i=0; i<2 ; i++){
                for(int j=0; j<n ; j++) cin >> tabela[i][j];
            }

            double vetorA[grau + 1];     // Coeficientes do polinômio ajustado
			double vetorY[n];            // Valores Y ajustados
			double coef_determinacao;    // Coeficiente de determinação

            SetColor(CINZA); cout << endl << endl; for(int loop=0; loop<80; loop++) cout << "=";
			AjustePolinomio(n, grau, tabela, vetorA, vetorY, &coef_determinacao);

			// Imprime os coeficientes do polinômio ajustado
			SetColor(CINZA); cout << endl << "Coeficientes do polinomio ajustado: " << endl; SetColor(BRANCO);
			for(int i=0; i<=grau; i++) cout << "a" << i << " = " << fixed << setprecision(3) << vetorA[i] << endl;

			// Imprime os valores Y ajustados
			SetColor(CINZA); cout << endl << "Valores de Y ajustados: " << endl; SetColor(BRANCO);
			for(int i=0; i<=grau; i++) cout << vetorY[i] << "  ";
			cout << endl << endl << endl;

			// Imprime o coeficiente de determinação
			SetColor(VERDE); cout << "Coeficiente de determinacao: " << coef_determinacao << endl;

            SetColor(CINZA); cout << endl; for(int loop=0; loop<80; loop++) cout << "=";
			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==5){ //2.5 - Ajuste de ponto à curva
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Ajustar os pontos tabelados a uma curva exponencial" << endl; SetColor(BRANCO);

			double a0=0, a1=0;
			SetColor(BRANCO); cout << endl << endl << "Insira a quantidade de pontos tabelados (max. 100): ";
            n=0;
            while(n<1 || n>100){
				gotoxy(52, 3); cout << "          "; gotoxy(52, 3);
				SetColor(AZUL); cin >> n;
			}

			SetColor(BRANCO); cout << endl << "Digite os pontos tabelados no formato x y: " << endl; SetColor(AZUL);
            for(int i=0; i<2 ; i++){
                for(int j=0; j<n ; j++) cin >> tabela[i][j];
            }

			SetColor(CINZA); cout << endl << endl; for(int loop=0; loop<80; loop++) cout << "=";
            Ajuste_Expo(n, tabela, a0, a1, Y_ajustado);

            SetColor(CINZA); cout << endl; for(int loop=0; loop<80; loop++) cout << "=";
			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		
		if(pos==6){ //2.6 - SAIR
			SetColor(AZUL); cout << "\n\nAgradecemos por ver o nosso trabalho. Espero que tenha gostado :)\n";
			ON=false;
			system("pause");
		}
	}
}
