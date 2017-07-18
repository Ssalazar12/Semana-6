#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/*
Soluciona la ecuacion de onda en 1 dimension con condiciones iniciales u0=0
y du/dt e t=0 es 0
*/

#define  SIZE 1000	//cantidad de puntos de posicion
#define TIME 350 //intervalo de tiempo

float x[SIZE];	//puntos en x
float u0[SIZE];	//Onda en tiempo t=0
float u1[SIZE]; // onda en t=0+dt. Primera iteracion
float u[SIZE];

float c;	//velocidad
float dx; //unidad de x
float dt; //uniddad de t
float gamm; //(c*dt/dx)^2

int n_t; //iteraciones totales

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

void create_u1(){
	/*calcula el primer paso de u */
	int i;
	for(i=1;i<SIZE;i++){
		u1[i]=0.5*gamm*(u0[i-1]-2*u0[i]+u0[i+1]) + u0[i];
	}		
}	

copy(float *old, float *copy){
	/* Recibe 2 pointers y copia el data de uno a otro */
        int i; 
	for(i=0;i<SIZE;i++){
		copy[i]=old[i];
	}
}	


void calculate_u(){
	/* Soluciona la ecuacion hasta un tiempo TIME*/
	int t;
	int i;
	float *past; //pointer al pasado
	float *present;//pointer al presente

	past =malloc(SIZE*sizeof(float));
	present= malloc(sizeof(float)*SIZE);
	copy(u0, past);
	copy(u1, present);
      
	for(t=0;t<TIME;t++){
		for(i=0;i<SIZE-1;i++){
			u[i]=2*(1-gamm)*present[i]- past[i] + gamm*(present[i+1]+ present[i-1]);
		}
		
	       copy(present, past); //vuelvo pasado--> presente
	       copy(u, present); //vuelvo presente--> u
	}
}

void files(){
	/*Crea archivos csv con los resultados para ser graficados en python*/
	FILE *fu0;
	FILE *fu1;
	FILE *fu;
	fu0 = fopen("u0.csv", "w+"); //opens the stream
	fu1 = fopen("u1.csv", "w+");
	fu = fopen("u.csv", "w+");
	int i;
	
	for(i=0; i<SIZE; i++){
		fprintf(fu0, "%f %f \n" ,x[i], u0[i]);
		fprintf(fu1, "%f %f \n" ,x[i], u1[i]);
		fprintf(fu, "%f %f \n" ,x[i], u[i]);	
	}
	
	fclose(fu0); //closes the stream
	fclose(fu1);
	fclose(fu);
		
}
	
int main() {

//inicializa las variables principales
create_x();
dx=0.001;
dt=0.0005;
c=1.0;
gamm=pow(c*dt/dx , 2);

//incia las condiciones iniciales
create_u0();
create_u1();
//calcula u
calculate_u();

files();

	
}
