#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/*
Soluciona la ecuacion de onda en 1 dimension con condiciones iniciales u0=0
y du/dt e t=0 es 0
*/

const int SIZE = 1000;	//cantidad de puntos de posicion
const int TIME = 350; //intervalo de tiempo

float x[SIZE];	//puntos en x
float u0[SIZE];	//Onda en tiempo t=0
float u1[SIZE]; // onda en t=0+dt. Primera iteracion

float c;	//velocidad
float dx; //unidad de x
float dt; //uniddad de t
float gamm; //c*dt/dx

void create_x(){
	/* inicializa array de puntos en x de 0 a 1*/
	int i;
	float siz=SIZE; //crea un float
	for(i=0; i<SIZE; i++){
		x[i]= (i/siz);
	}
}

void create_u0(){
	/*inicializa la condicion inicial */
	int i;
	float exponent;
	for(i=0; i<SIZE; i++){
		exponent= pow((x[i])-0.3, 2);
		u0[i]= exp(-(exponent/0.01));
	}		
}

void files(){
	/*Crea archivos csv con los resultados para ser graficados en python*/
	FILE *fp;
	fp = fopen("u0.csv", "w+"); //opens the stream
	int i;
	for(i=0; i<SIZE; i++){
		fprintf(fp, "%f %f \n" ,x[i], u0[i]);	
	}
	fclose(fp); //closes the stream
	
}
	
int main() {


create_x();
create_u0();
files();

	
}