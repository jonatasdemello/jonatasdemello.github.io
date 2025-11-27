/************************************************************************** 
	PROGRAMA: JONATAS.cpp 
	DESCRICAO: Desenha 'JONATAS' em 3D;
		  Efetua movimentos em todos os planos;
		  Usa alocacao dinamica de memoria.
	DATA: 23/07/94
	PROGRAMADOR: Jonatas de Mello No. 42 - CIENCIA DA COMPUTACAO
**************************************************************************/

# include <graphics.h>
# include <stdlib.h>
# include <conio.h>
# include <stdio.h>
# include <dos.h>
# include <math.h>
# define NumLetras 7

typedef float Ponto[4];
typedef int Aresta[2];
typedef struct tagLETRA{
		char letra;
		int npts,nart;
		Ponto* pts;
		Aresta* art;
}LETRA;

typedef float Mat[4][4];

int cont = 0;
 
void DesenhaReta (Ponto p1, Ponto p2, int cor);
void DesenhaLinha(int startx, int starty, int endx, int endy, int cor);
void DesenhaLetra(LETRA l, int cor);
void MultMat (Mat M1, Mat M2, Mat M3);
void MultPtoMat (Ponto P, Mat M, Ponto P1);
void CriaMov (Mat MM, float tx, float ty, float tz, float ex, float ey, float ez, float rx, float ry, float rz);
void EfetuaMov (LETRA * l);
void MoveRot(LETRA * l, float rx, float ry, float rz);
void MoveEsc(LETRA * l, float ex, float ey, float ez);
void TransladaPonto(Ponto p, float tx, float ty, float tz);
void TransladaLetra(LETRA* c, float tx, float ty, float tz);
void EscalaLetra(LETRA* c, float ex, float ey, float ez);
void EscalaPonto(Ponto p, float ex, float ey, float ez);
void RotacionaPonto(Ponto p, float rx, float ry, float rz);
void RotacionaLetra(LETRA* c, float rx, float ry, float rz);
void AlocaEspaco(LETRA* l);
void AlocaEspTodasLetras(LETRA * lts);
void * Malloc(int size);
void Free(void * ptr);
void LiberaEspaco(LETRA* l);
void LibEspTodasLetras(LETRA * lts);
void InicJ(LETRA* l);
void InicO(LETRA * l);
void InicN(LETRA * l);
void InicA(LETRA * l);
void InicT(LETRA * l);
void InicS(LETRA * l);
void InicArt1(LETRA * l);
void InicArt2(LETRA * l);

void EfetuaMov(LETRA* l)
{
	int d=50; 
	float i;
//move jota para esq
	for (i=0; i<7; i=i+0.1)
	  {
		 DesenhaLetra(l[0],0);
		 TransladaLetra(&l[0],-i,0,0);
		 DesenhaLetra(l[0],15);
		 delay(d);
	  }
//move oo para esq
	for (i=0; i<6; i=i+0.1)
	  {
		 DesenhaLetra(l[1],0);
		 TransladaLetra(&l[1],-i,0,0);
		 DesenhaLetra(l[1],15);
		 delay(d);
	  }
//move ene para esq
	for (i=0; i<4.8; i=i+0.1)
	  {
		 DesenhaLetra(l[2],0);
		 TransladaLetra(&l[2],-i,0,0);
		 DesenhaLetra(l[2],15);
		 delay(d);
	  }
//move aha para esq
	for (i=0; i<3.2; i=i+0.1)
	  {
		 DesenhaLetra(l[3],0);
		 TransladaLetra(&l[3],-i,0,0);
		 DesenhaLetra(l[3],15);
		 delay(d);
	  }
//move te para dir
	for (i=0; i<1.7; i=i+0.1)
	  {
		 DesenhaLetra(l[4],0);
		 TransladaLetra(&l[4],i,0,0);
		 DesenhaLetra(l[4],15);
		 DesenhaLetra(l[3],15);
		 delay(d);
	  }
//move ah para dir
	for (i=0; i<4; i=i+0.1)
	  {
		 DesenhaLetra(l[5],0);
		 TransladaLetra(&l[5],i,0,0);
		 DesenhaLetra(l[5],15);
		 DesenhaLetra(l[4],15);
		 DesenhaLetra(l[3],15);
		 delay(d);
	  }
//move esse para dir
	for (i=0; i<5.4; i=i+0.1)
	  {
		 DesenhaLetra(l[6],0);
		 TransladaLetra(&l[6],i,0,0);
		 DesenhaLetra(l[5],15);
		 DesenhaLetra(l[6],15);
		 DesenhaLetra(l[4],15);
		 DesenhaLetra(l[3],15);
		 delay(d);
	  }
// rotaciona
	for (i=0; i<5; i=i+0.1)
		MoveRot(l,i,i,i);
// escala +
	for (i=0; i<10; i++)
		MoveEsc(l,1.5,1.5,1.5);
// escala -
	for (i=0; i<10; i++)
		MoveEsc(l,0.5,0.5,0.5);
}

void MoveRot(LETRA * l, float rx, float ry, float rz)
{
	 int x;
	 for (x=0; x<7; x++)
		 DesenhaLetra(l[x],0);
	 for (x=0; x<7; x++)
		 RotacionaLetra(&l[x],rx,ry,rz);
	 for (x=0; x<7; x++)
		 DesenhaLetra(l[x],15);
	 delay(200);
}

void MoveEsc(LETRA * l, float ex, float ey, float ez)
{
	 int x;
	 for (x=0; x<7; x++)
		 DesenhaLetra(l[x],0);
	 for (x=0; x<7; x++)
		 EscalaLetra(&l[x],ex,ey,ez);
	 for (x=0; x<7; x++)
		 DesenhaLetra(l[x],15);
	 delay(150);
}

void MultMat (Mat M1, Mat M2, Mat M3)
{
	int x, y, z;
	Mat Maux;

	for (x=0; x<4; x=x+1)
		for (y=0; y<4; y=y+1)
			{
				Maux[x][y] = 0;
				for (z=0; z<4; z=z+1)
					 Maux[x][y] = Maux[x][y] + M1[z][x] * M2[y][z];
			};
	for (x=0; x<4; x=x+1)
		for (y=0; y<4; y=y+1)
			M3[x][y] = Maux[x][y];
}

void MultPtoMat (Ponto P, Mat M)
{
	int j, k;
	Ponto aux;

	for (j=0; j<4; j=j+1)
	{
		aux[j] = 0;
		for (k=0; k<4; k=k+1)
			aux[j] = aux[j] + P[k] * M[k][j];
	}
	for (j=0; j<4; j=j+1)
		 P[j] = aux[j];
}

void TransladaPonto(Ponto p, float tx, float ty, float tz)
{
  Mat MT={{1,0,0,0},{0,1,0,0},{0,0,1,0},{tx,ty,tz,1}};
  MultPtoMat(p,MT);
}

void TransladaLetra(LETRA* l, float tx, float ty, float tz)
{
 int pto;
 for(pto=0; pto<l->npts; pto++)
	 TransladaPonto(l->pts[pto],tx,ty,tz);
}

void EscalaLetra(LETRA* l, float ex, float ey, float ez)
{
 int pto;
 for(pto=0; pto<l->npts; pto++)
	EscalaPonto(l->pts[pto],ex,ey,ez);
}

void EscalaPonto(Ponto p, float ex, float ey, float ez)
{
 Mat Me={{ex,0,0,0},{0,ey,0,0},{0,0,ez,0},{0,0,0,1}};
 MultPtoMat(p,Me);
}

void RotacionaPonto(Ponto p, float rx, float ry, float rz)
{
 Mat MRx={{1,0,0,0},{0,cos(rx),sin(rx),0},{0,-sin(rx),cos(rx),0},{0,0,0,1}};
 Mat MRy={{cos(ry),0,sin(ry),0},{0,1,0,0},{-sin(ry),0,cos(ry),0},{0,0,0,1}};
 Mat MRz={{cos(rz),-sin(rz),0,0},{sin(rz),cos(rz),0,0},{0,0,1,0},{0,0,0,1}};
 MultPtoMat(p,MRx);
 MultPtoMat(p,MRy);
 MultPtoMat(p,MRz);
}

void RotacionaLetra(LETRA* l, float rx, float ry, float rz)
{
 int pto;
 for(pto=0; pto<l->npts; pto++)
	 RotacionaPonto(l->pts[pto],rx,ry,rz);
}

void DesenhaReta(Ponto p1, Ponto p2, int cor)
{
  int startx, starty, endx, endy;

  startx= 300 + (int) p1[0];
  starty= 200 - (int) p1[1];
  endx= 300 + (int) p2[0];
  endy= 200 - (int) p2[1];

  setcolor(cor);
  line(startx,starty,endx,endy);
}

void * Malloc(int size)
{
 cont = cont+1;
 return malloc(size);
}

void Free(void * ptr)
{
 cont=cont-1;
 free(ptr);
}

void AlocaEspaco(LETRA* l)
{
	l->pts = (Ponto * ) Malloc(l->npts * sizeof(Ponto));
	l->art = (Aresta * ) Malloc(l->nart * sizeof(Aresta));
}

void AlocaEspTodasLetras(LETRA * lts)
{ 
	int i;
	for (i=0; i<NumLetras; i++)
		AlocaEspaco(&lts[i]);
}

void LiberaEspaco(LETRA* l)
{
	Free(l->pts); // = (Ponto * ) Free(l->npts * sizeof(Ponto));
	Free(l->art); // = (Aresta * ) Free(l->nart * sizeof(Aresta));
}

void LibEspTodasLetras(LETRA * lts)
{ 
	int i;
	for (i=0; i<NumLetras; i++)
		LiberaEspaco(&lts[i]);
}

void DesenhaLetra(LETRA l, int cor)
{
	int i;
	for (i=0; i<l.nart; i++)
		DesenhaReta(l.pts[l.art[i][0]], l.pts[l.art[i][1]], cor);
}

void InicGeral(LETRA * l)
{
	int i;
// inicializa os ptos de normalizacao e z do 1o. e 2o. planos
		for (i=0; i<l->npts; i++) 
			 l->pts[i][3] = 1; // normalizacao
		for (i=0; i<(l->npts/2); i++)
			 l->pts[i][2] = 0; // z do 1o. plano
		for (i=(l->npts/2); i<l->npts; i++)
			 l->pts[i][2] = 20; // z do 2o. plano
// copia os ptos da 1a. face para a segunda		
		for (i=(l->npts/2); i<l->npts; i++)
		  {
			l->pts[i][0] = l->pts[i-(l->npts/2)][0];
			l->pts[i][1] = l->pts[i-(l->npts/2)][1];
		  }
}

void InicArt1(LETRA * l)
{
	int i,s,t;

	t = (l->nart / 3);
	s = (l->nart - t);

// inicializa as arestas
// 1a. face
		for (i=0; i < (t-1); i++)
		  {
			l->art[i][0] = i;
			l->art[i][1] = i+1;
		  }
		l->art[t-1][0] = t-1;
		l->art[t-1][1] = 0;
// 2a. face
		for (i=t; i < (s-1); i++)
		  {
			l->art[i][0] = i;
			l->art[i][1] = i+1;
		  }
		l->art[s-1][0] = s-1;
		l->art[s-1][1] = t;
// profundidade
		for (i=s; i < (l->nart); i++)
		  {
			l->art[i][0] = i-s;
			l->art[i][1] = i-(s/2);
		  } 
}

void InicArt2(LETRA * l)
{
	int i,r,s,t,u;
	r = l->nart / 3;
	t = r - 4;
	u = r + t;
	s = u + 4;

// inicializa as arestas
// 1a. face
		for (i=0; i < (t-1); i++)
		  {
			l->art[i][0] = i;
			l->art[i][1] = i+1;
		  }
		l->art[t-1][0] = t-1;
		l->art[t-1][1] = 0;

		for (i=t; i < (r-1); i++)
		  {
			l->art[i][0] = i;
			l->art[i][1] = i+1;
		  }
		l->art[r-1][0] = r-1;
		l->art[r-1][1] = t;
// 2a. face
		for (i=r; i < (u-1); i++)
		  {
			l->art[i][0] = i;
			l->art[i][1] = i+1;
		  }
		l->art[u-1][0] = u-1;
		l->art[u-1][1] = r;

		for (i=u; i < (s-1); i++)
		  {
			l->art[i][0] = i;
			l->art[i][1] = i+1;
		  }
		l->art[s-1][0] = s-1;
		l->art[s-1][1] = u;
// profundidade
		for (i=s; i < (l->nart); i++)
		  {
			l->art[i][0] = i-s;
			l->art[i][1] = i-(s/2);
		  } 
}

void InicJ(LETRA* l)
{
	int i;
	if (l->letra == 'J')
	 {
// ptos da 1a. face:
		l->pts[0][0] = -10;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =  30;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  30;   // x
		l->pts[2][1] = -30;   // y

		l->pts[3][0] =  20;   // x
		l->pts[3][1] = -40;   // y

		l->pts[4][0] = -20;   // x
		l->pts[4][1] = -40;   // y

		l->pts[5][0] = -30;   // x
		l->pts[5][1] = -30;   // y

		l->pts[6][0] = -30;   // x
		l->pts[6][1] = -10;   // y

		l->pts[7][0] = -10;   // x
		l->pts[7][1] = -10;   // y

		l->pts[8][0] = -10;   // x
		l->pts[8][1] = -20;   // y

		l->pts[9][0] =  10;   // x
		l->pts[9][1] = -20;   // y

		l->pts[10][0] = 10;    // x
		l->pts[10][1] = 20;    // y

		l->pts[11][0] =-10;    // x
		l->pts[11][1] = 20;    // y

		InicGeral(l);
		InicArt1(l);
	}
}
void InicO(LETRA * l)
{
	int i;
	if (l->letra == 'O')
	{
// ptos da 1a. face:
		l->pts[0][0] = -20;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =  20;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  30;   // x
		l->pts[2][1] =  30;   // y

		l->pts[3][0] =  30;   // x
		l->pts[3][1] = -30;   // y

		l->pts[4][0] =  20;   // x
		l->pts[4][1] = -40;   // y

		l->pts[5][0] = -20;   // x
		l->pts[5][1] = -40;   // y

		l->pts[6][0] = -30;   // x
		l->pts[6][1] = -30;   // y

		l->pts[7][0] = -30;   // x
		l->pts[7][1] =  30;   // y

		l->pts[8][0] = -10;   // x
		l->pts[8][1] =  20;   // y

		l->pts[9][0] =  10;   // x
		l->pts[9][1] =  20;   // y

		l->pts[10][0] = 10;    // x
		l->pts[10][1] =-20;    // y

		l->pts[11][0] =-10;    // x
		l->pts[11][1] =-20;    // y

		InicGeral(l);
		InicArt2(l);
	}
}

void InicN(LETRA * l)
{
	int i;
	if (l->letra == 'N')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] = -10;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  10;   // x
		l->pts[2][1] = -10;   // y

		l->pts[3][0] =  10;   // x
		l->pts[3][1] =  40;   // y

		l->pts[4][0] =  30;   // x
		l->pts[4][1] =  40;   // y

		l->pts[5][0] =  30;   // x
		l->pts[5][1] = -40;   // y

		l->pts[6][0] =  10;   // x
		l->pts[6][1] = -40;   // y

		l->pts[7][0] = -10;   // x
		l->pts[7][1] =  10;   // y

		l->pts[8][0] = -10;   // x
		l->pts[8][1] = -40;   // y

		l->pts[9][0] = -30;   // x
		l->pts[9][1] = -40;   // y

		InicGeral(l);
		InicArt1(l);
	}
}
void InicA(LETRA * l)
{
	int i;
	if (l->letra == 'A' || l->letra == 'a')
	{
// ptos da 1a. face:
		l->pts[0][0] = -20;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =  20;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  30;   // x
		l->pts[2][1] =  30;   // y

		l->pts[3][0] =  30;   // x
		l->pts[3][1] = -40;   // y

		l->pts[4][0] =  10;   // x
		l->pts[4][1] = -40;   // y

		l->pts[5][0] =  10;   // x
		l->pts[5][1] = -20;   // y

		l->pts[6][0] = -10;   // x
		l->pts[6][1] = -20;   // y

		l->pts[7][0] = -10;   // x
		l->pts[7][1] = -40;   // y

		l->pts[8][0] = -30;   // x
		l->pts[8][1] = -40;   // y

		l->pts[9][0] = -30;   // x
		l->pts[9][1] =  30;   // y

		l->pts[10][0] =-10;    // x
		l->pts[10][1] = 20;    // y

		l->pts[11][0] = 10;    // x
		l->pts[11][1] = 20;    // y

		l->pts[12][0] = 10;    // x
		l->pts[12][1] =  0;    // y

		l->pts[13][0] =-10;    // x
		l->pts[13][1] =  0;    // y

		InicGeral(l);
		InicArt2(l);
	}
}

void InicT(LETRA * l)
{
	int i;
	if (l->letra == 'T')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =  30;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  30;   // x
		l->pts[2][1] =  20;   // y

		l->pts[3][0] =  10;   // x
		l->pts[3][1] =  20;   // y

		l->pts[4][0] =  10;   // x
		l->pts[4][1] = -40;   // y

		l->pts[5][0] = -10;   // x
		l->pts[5][1] = -40;   // y

		l->pts[6][0] = -10;   // x
		l->pts[6][1] =  20;   // y

		l->pts[7][0] = -30;   // x
		l->pts[7][1] =  20;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicS(LETRA * l)
{
	int i;
	if (l->letra == 'S')
	{
// ptos da 1a. face:
		l->pts[0][0] = -20;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =  20;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  30;   // x
		l->pts[2][1] =  30;   // y

		l->pts[3][0] =  30;   // x
		l->pts[3][1] =  10;   // y

		l->pts[4][0] =  10;   // x
		l->pts[4][1] =  10;   // y

		l->pts[5][0] =  10;   // x
		l->pts[5][1] =  20;   // y

		l->pts[6][0] = -10;   // x
		l->pts[6][1] =  20;   // y

		l->pts[7][0] = -10;   // x
		l->pts[7][1] =  10;   // y

		l->pts[8][0] =  30;   // x
		l->pts[8][1] = -10;   // y

		l->pts[9][0] =  30;   // x
		l->pts[9][1] = -30;   // y

		l->pts[10][0] =  20;   // x
		l->pts[10][1] = -40;   // y

		l->pts[11][0] = -20;   // x
		l->pts[11][1] = -40;   // y

		l->pts[12][0] = -30;   // x
		l->pts[12][1] = -30;   // y

		l->pts[13][0] = -30;   // x
		l->pts[13][1] = -10;   // y

		l->pts[14][0] = -10;   // x
		l->pts[14][1] = -10;   // y

		l->pts[15][0] = -10;   // x
		l->pts[15][1] = -20;   // y

		l->pts[16][0] =  10;   // x
		l->pts[16][1] = -20;   // y

		l->pts[17][0] =  10;   // x
		l->pts[17][1] = -10;   // y

		l->pts[18][0] = -30;   // x
		l->pts[18][1] =  10;   // y

		l->pts[19][0] = -30;   // x
		l->pts[19][1] =  30;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void main ()
{
	 int gdriver, gmode;

	 LETRA letras[NumLetras] = {{'J',24,36,NULL,NULL},{'O',24,36,NULL,NULL},
	 {'N',20,30,NULL,NULL},{'A',28,42,NULL,NULL},{'T',16,24,NULL,NULL},
	 {'a',28,42,NULL,NULL},{'S',40,60,NULL,NULL}};

	 detectgraph (&gdriver, &gmode);
	 initgraph (&gdriver, &gmode, "\\tc\\bgi");
//   initgraph (&gdriver, &gmode, "g:\\usr\\compila\\borlandc\\bgi");

	 AlocaEspTodasLetras(letras);
	 InicJ(&letras[0]);
	 InicO(&letras[1]);
	 InicN(&letras[2]);
	 InicA(&letras[3]);
	 InicT(&letras[4]);
	 InicA(&letras[5]);
	 InicS(&letras[6]);
	 EfetuaMov(letras);
	 getch();
	 closegraph ();
	 LibEspTodasLetras(letras);
	 printf(" Cont : %d",cont);
	 getch();
}
