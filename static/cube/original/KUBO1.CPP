/*==============================
	Programa que desenha um cubo em 3D
	==============================*/

#include <stdio.h>
#include <graph.h>
#include <conio.h>
#include <dos.h>
#include <math.h>
#include <stdlib.h>
                     
/* Criacao de variaveis globais */

typedef double PONTO[4];
typedef PONTO CUBO[8];
typedef double MAT[4][4];
CUBO cubo = {{45,45,45,1},   // P1
	     {45,45,-45,1},  // P2
	     {45,-45,-45,1},  // P3
	     {45,-45,45,1},   // P4
	     {-45,45,45,1},   // P5
	     {-45,45,-45,1},  // P6
	     {-45,-45,-45,1},  // P7
	     {-45,-45,45,1}};  // P8


// declaracao das funcoes

void MultPtoMat(PONTO P,MAT M,PONTO P1);
void TransladaPonto(PONTO P,int DX,int DY,int DZ,PONTO P1);
void TransladaCubo(CUBO CB,int DX,int DY,int DZ,CUBO CB1);
void EscalaPonto(PONTO P,int S,PONTO P1);
void EscalaCubo(CUBO C,int S,CUBO C1);
void MultMat(MAT M1,MAT M2,MAT M3);
void CriaMX(MAT M,double angulo);
void CriaMY(MAT M,double angulo);
void CriaMZ(MAT M,double angulo);
void RotacionaCubo(CUBO CB,double RX,double RY,double RZ,CUBO CB1);
void linha(double x, double y, double x1, double y1);
void DesenhaCubo(CUBO C,int cor);

// definicao das Funcoes

void linha(double x, double y, double x1, double y1)
{                   
	_moveto( (int) x+320, (int) 240-y);
	_lineto( (int) x1+320, (int) 240-y1);
}

void MultPtoMat(PONTO P, MAT M,PONTO P1)
{
     PONTO AUX;
     double AUX2;
     int J,K;
     for(J=0; J<4; J++)
     {
	AUX2=0;
	for(K=0; K<4; K++)
	   AUX2=AUX2+(P[K]*M[K][J]);
	AUX[J] = AUX2;
     }
     for(J=0; J<4; J++)
       P1[J] = AUX[J];

}

void TransladaPonto(PONTO P,int DX,int DY,int DZ,PONTO P1)
{
     MAT MT={{1,0,0,0},{0,1,0,0},{0,0,1,0},{DX,DY,DZ,1}};
     MultPtoMat(P,MT,P1);
}

void TransladaCubo(CUBO CB,int DX,int DY,int DZ,CUBO CB1)
{
     int PTO;
     for(PTO=0; PTO<8; PTO++)
	TransladaPonto(CB[PTO],DX,DY,DZ,CB1[PTO]);
}

void EscalaPonto(PONTO P,int S,PONTO P1)
{
     MAT MTZ={{S,0,0,0},{0,S,0,0},{0,0,S,0},{0,0,0,1}};
     MultPtoMat(P,MTZ,P1);
}

void EscalaCubo(CUBO C,int S,CUBO C1)
{
    int PONT;
    for(PONT=0; PONT<8; PONT++)
	EscalaPonto(C[PONT],S,C1[PONT]);
}

void MultMat(MAT M1,MAT M2,MAT M3)
{
     MAT AUX;
     int I,J,K;
     for(I=0; I<4; I++)
     for(J=0; J<4; J++)
     {
	AUX[I][J]=0;
	 for(K=0; K<4; K++)
	   AUX[I][J]=AUX[I][J]+(M1[I][K]*M2[K][J]);
     }
     for(I=0; I<4; I++)
       for(J=0; J<4; J++)
	 M3[I][J] = AUX[I][J];

}

void CriaMX(MAT M,double angulo)
{
     M[0][0]=1;
     M[0][1]=0;
     M[0][2]=0;
     M[0][3]=0;
     M[1][0]=0;
     M[1][1]=cos(angulo);
     M[1][2]=sin(angulo);
     M[1][3]=0;
     M[2][0]=0;
     M[2][1]=-sin(angulo);
     M[2][2]=cos(angulo);
     M[2][3]=0;
     M[3][0]=0;
     M[3][1]=0;
     M[3][2]=0;
     M[3][3]=1;
}

void CriaMY(MAT M,double angulo)
{
     M[0][0]=cos(angulo);
     M[0][1]=0;
     M[0][2]=sin(angulo);
     M[0][3]=0;
     M[1][0]=0;
     M[1][1]=1;
     M[1][2]=0;
     M[1][3]=0;
     M[2][0]=-sin(angulo);
     M[2][1]=0;
     M[2][2]=cos(angulo);
     M[2][3]=0;
     M[3][0]=0;
     M[3][1]=0;
     M[3][2]=0;
     M[3][3]=1;
}

void CriaMZ(MAT M,double angulo)
{
     M[0][0]=cos(angulo);
     M[0][1]=-sin(angulo);
     M[0][2]=0;
     M[0][3]=0;
     M[1][0]=sin(angulo);
     M[1][1]=cos(angulo);
     M[1][2]=0;
     M[1][3]=0;
     M[2][0]=0;
     M[2][1]=0;
     M[2][2]=1;
     M[2][3]=0;
     M[3][0]=0;
     M[3][1]=0;
     M[3][2]=0;
     M[3][3]=1;
}

void RotacionaCubo(CUBO CB,double RX,double RY,double RZ,CUBO CB1)
{
     int I;
     MAT M,MX,MY,MZ;
     CriaMX(MX,RX);
     CriaMY(MY,RY);
     CriaMZ(MZ,RZ);
     MultMat(MX,MY,M);
     MultMat(M,MZ,M);
     for(I=0; I<8; I++)
	MultPtoMat(CB[I],M,CB1[I]);
}

void DesenhaCubo(CUBO C,int cor)
{                                                             
	_setcolor(cor);
	 linha(C[4][0],C[4][1],C[0][0],C[0][1]);
	 linha(C[7][0],C[7][1],C[3][0],C[3][1]);
	 linha(C[4][0],C[4][1],C[7][0],C[7][1]);
	 linha(C[0][0],C[0][1],C[3][0],C[3][1]);
	 linha(C[5][0],C[5][1],C[1][0],C[1][1]);
	 linha(C[6][0],C[6][1],C[2][0],C[2][1]);
	 linha(C[5][0],C[5][1],C[6][0],C[6][1]);
	 linha(C[1][0],C[1][1],C[2][0],C[2][1]);
	 linha(C[0][0],C[0][1],C[1][0],C[1][1]);
	 linha(C[3][0],C[3][1],C[2][0],C[2][1]);
	 linha(C[4][0],C[4][1],C[5][0],C[5][1]);
	 linha(C[7][0],C[7][1],C[6][0],C[6][1]);
 }

/*  Declaracao da funcao main() */

void main()
{            
	int x,cor;
	long tempo;
	double i;
   struct _videoconfig;
   /* Inicializa o modo grafico */
   if( !_setvideomode( _VRES16COLOR ) )
      exit( 1 );

	tempo =  32900L;
	cor = 14;
	                              
       for (i=1;i<6;i+=0.1)
      {
      	RotacionaCubo(cubo,i/30,i/30,i/30,cubo);
      	DesenhaCubo(cubo,cor);  
      	for(x=0; x<tempo;x++);
      	DesenhaCubo(cubo,0);
      }

      for (i=1;i<7;i+=1)
      {
      	TransladaCubo(cubo,i/30,i/30,0,cubo);
      	DesenhaCubo(cubo,cor);
      	for(x=0; x<tempo;x++);
      	DesenhaCubo(cubo,0);
      }

      EscalaCubo(cubo,2,cubo);
      DesenhaCubo(cubo,cor);
      for(x=0; x<tempo;x++);
      DesenhaCubo(cubo,0);

      for (i=1;i<6;i+=0.1)
      {
      	RotacionaCubo(cubo,i/30,i/30,i/30,cubo);
      	DesenhaCubo(cubo,cor);
      	for(x=0; x<tempo;x++);
      	DesenhaCubo(cubo,0);
      }
                                   
   _setvideomode( _DEFAULTMODE );
}

                                
                                  