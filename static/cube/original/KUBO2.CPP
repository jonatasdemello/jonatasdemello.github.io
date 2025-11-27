#include <stdio.h>
//#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <math.h>
#include <stdlib.h>

/* Criacao de variaveis globais */

typedef float PONTO[4];
typedef PONTO CUBO[8];
typedef float MAT[4][4];
CUBO cubo = {{45,45,45,1},   // P1
	     {45,45,-45,1},  // P2
	     {45,-45,-45,1},  // P3
	     {45,-45,45,1},   // P4
	     {-45,45,45,1},   // P5
	     {-45,45,-45,1},  // P6
	     {-45,-45,-45,1},  // P7
	     {-45,-45,45,1}};  // P8


// declaracao das funcoes

void GOTOXY(int X,int Y);
void PUTCH(int X,int Y,int CRCT);
void MultPtoMat(PONTO P,MAT M,PONTO P1);
void TransladaPonto(PONTO P,int DX,int DY,int DZ,PONTO P1);
void TransladaCubo(CUBO CB,int DX,int DY,int DZ,CUBO CB1);
void EscalaPonto(PONTO P,int S,PONTO P1);
void EscalaCubo(CUBO C,int S,CUBO C1);
void MultMat(MAT M1,MAT M2,MAT M3);
void CriaMX(MAT M,float angulo);
void CriaMY(MAT M,float angulo);
void CriaMZ(MAT M,float angulo);
void RotacionaCubo(CUBO CB,float RX,float RY,float RZ,CUBO CB1);
void linha(int x, int y, int x1, int y1);
void DesenhaCubo(CUBO C);
//void far line (int PT1, int PT2);

// definicao das Funcoes

void linha(int x, int y, int x1, int y1)
{
int i
int j
int X = i;
int Y = j;
int X1 = i++;
int Y1 = j++;

line(X,Y,X1,Y1);
}

void GOTOXY(int X,int Y)
{
     gotoxy(X+40,24-(Y+12));
}

void PUTCH(int X,int Y,int CRCT)
{
     GOTOXY(X,Y);
     putch(CRCT);
}

void MultPtoMat(PONTO P, MAT M,PONTO P1)
{
     PONTO AUX;
     float AUX2;
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

void CriaMX(MAT M,float angulo)
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

void CriaMY(MAT M,float angulo)
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

void CriaMZ(MAT M,float angulo)
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

void RotacionaCubo(CUBO CB,float RX,float RY,float RZ,CUBO CB1)
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

void DesenhaCubo(CUBO C)
{
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
      float i;
      int gdriver = DETECT, gmode/*, errorcode*/;

	 initgraph(&gdriver, &gmode, "\\usr\\compila\\borlandc\\bgi");
//       initgraph(&gdriver, &gmode, "\\borlandc\\bgi");

	// errorcode = graphresult();
       for (i=1;i<5;i+=0.1)

      {
      RotacionaCubo(cubo,i,i,i,cubo);
      setcolor(5);
      DesenhaCubo(cubo);
      setcolor(0);
      delay(400);
      DesenhaCubo(cubo);
      }

      for (i=1;i<30;i+=5)
      {
      TransladaCubo(cubo,i,i,i,cubo);
      setcolor(5);
      DesenhaCubo(cubo);
      setcolor(0);
      delay(400);
      DesenhaCubo(cubo);
      }

      EscalaCubo(cubo,2,cubo);
      setcolor(5);
      DesenhaCubo(cubo);
      setcolor(0);
      delay(500);
      DesenhaCubo(cubo);

      for (i=1;i<5;i+=0.1)
      {
      RotacionaCubo(cubo,i,i,i,cubo);
      setcolor(5);
      DesenhaCubo(cubo);
      setcolor(0);
      delay(400);
      DesenhaCubo(cubo);
      }

}

