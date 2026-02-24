//***************************************************************************
// 	PROGRAMA: GRAVA.CPP
//	DESCRICAO: Inicializa todas as letras do alfabeto
//		e grava no arquivo LETRAS.DAT;
//		Usa alocacao dinamica de memoria.
//	DATA:  primeira versao: 23/07/94  atualizacao: 19/11/94
//	PROGRAMADOR: Jonatas de Mello No. 42 - CIENCIA DA COMPUTACAO
//**************************************************************************

// INCLUDE'S
# include <conio.h>
# include <stdio.h>
# include <alloc.h>
# include <dos.h>
# include <graphics.h>
# define NumLetras 26

// ESTRUTURAS DE DADOS
typedef float Ponto[4];
typedef int Aresta[2];
typedef struct tagLETRA{
	char letra;
	int npts,nart;
	Ponto* pts;
	Aresta* art;
}LETRA;
typedef struct tagNO{
	int rf,npts,nart;
}NO;
typedef void funcao(LETRA * l);

int cont = 0;  // contador de Memoria Dinamica Alocada

// PROTOTYPE'S
void DesenhaReta (Ponto p1, Ponto p2, int cor);
void DesenhaLinha(int startx, int starty, int endx, int endy, int cor);
void DesenhaLetra(LETRA l, int cor);
void AlocaEspaco(LETRA* l);
void AlocaEspTodasLetras(LETRA * lts);
void * Malloc(int size);
void Free(void * ptr);
void LiberaEspaco(LETRA* l);
void LibEspTodasLetras(LETRA * lts);
void InicArt1(LETRA * l);
void InicArt2(LETRA * l);
void InicA(LETRA * l);
void InicB(LETRA * l);
void InicC(LETRA * l);
void InicD(LETRA * l);
void InicE(LETRA * l);
void InicF(LETRA * l);
void InicG(LETRA * l);
void InicH(LETRA * l);
void InicI(LETRA * l);
void InicJ(LETRA * l);
void InicK(LETRA * l);
void InicL(LETRA * l);
void InicM(LETRA * l);
void InicN(LETRA * l);
void InicO(LETRA * l);
void InicP(LETRA * l);
void InicQ(LETRA * l);
void InicR(LETRA * l);
void InicS(LETRA * l);
void InicT(LETRA * l);
void InicU(LETRA * l);
void InicV(LETRA * l);
void InicW(LETRA * l);
void InicX(LETRA * l);
void InicY(LETRA * l);
void InicZ(LETRA * l);

// FUNCOES
void DesenhaReta(Ponto p1, Ponto p2, int cor)
{
  int startx, starty, endx, endy;

  startx= 300 + (int) p1[0];
  starty= 200 - (int) p1[1];
  endx= 300 + (int) p2[0];
  endy= 200 - (int) p2[1];

  setcolor(cor);
  line
  (startx,starty,endx,endy);
}

void DesenhaLetra(LETRA l, int cor)
{
	int i;
	for (i=0; i<l.nart; i++)
		DesenhaReta(l.pts[l.art[i][0]], l.pts[l.art[i][1]], cor);
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
// incializa as arestas das letras J, N, T, S
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
// inicializa as arestas das letras A, O
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

void InicA(LETRA * l)
{
	if (l->letra == 'A')
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

void InicB(LETRA * l)
{
	int i;
	if (l->letra == 'B')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =  20;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  30;   // x
		l->pts[2][1] =  30;   // y

		l->pts[3][0] =  30;   // x
		l->pts[3][1] =  10;   // y

		l->pts[4][0] =  20;   // x
		l->pts[4][1] =   0;   // y

		l->pts[5][0] =  30;   // x
		l->pts[5][1] = -10;   // y

		l->pts[6][0] =  30;   // x
		l->pts[6][1] = -30;   // y

		l->pts[7][0] =  20;   // x
		l->pts[7][1] = -40;   // y

		l->pts[8][0] = -30;   // x
		l->pts[8][1] = -40;   // y

		l->pts[9][0] = -10;   // x
		l->pts[9][1] =  20;   // y

		l->pts[10][0] =  10;   // x
		l->pts[10][1] =  20;   // y

		l->pts[11][0] =  10;   // x
		l->pts[11][1] =  10;   // y

		l->pts[12][0] = -10;   // x
		l->pts[12][1] =  10;   // y

		l->pts[13][0] = -10;   // x
		l->pts[13][1] = -10;   // y

		l->pts[14][0] =  10;   // x
		l->pts[14][1] = -10;   // y

		l->pts[15][0] =  10;   // x
		l->pts[15][1] = -20;   // y

		l->pts[16][0] = -10;   // x
		l->pts[16][1] = -20;   // y

		InicGeral(l);
//Arestas: 1a. face
		for (i=0;i<8;i++)
		{
			l->art[i][0]=i;
			l->art[i][1]=i+1;	
		}
		l->art[8][0]=8;
		l->art[8][1]=0;
		for(i=9;i<12;i++)
		{
			l->art[i][0]=i;
			l->art[i][1]=i+1;
		}
		l->art[12][0]=12;
		l->art[12][1]=9;
		for(i=13;i<16;i++)
		{
			l->art[i][0]=i;
			l->art[i][1]=i+1;
		}
		l->art[16][0]=16;
		l->art[16][1]=13;
// 2a. face
		for(i=17;i<25;i++)
		{
			l->art[i][0]=i;
			l->art[i][1]=i+1;
		}
		l->art[25][0]=25;
		l->art[25][1]=17;
		for(i=26;i<29;i++)
		{
			l->art[i][0]=i;
			l->art[i][1]=i+1;
		}
		l->art[29][0]=29;
		l->art[29][1]=26;
		for(i=30;i<33;i++)
		{
			l->art[i][0]=i;
			l->art[i][1]=i+1;
		}
		l->art[33][0]=33;
		l->art[33][1]=30;
// prof
		for(i=34;i<51;i++)
		{
			l->art[i][0]=i-34;
			l->art[i][1]=i-17;
		}
	}
}

void InicC(LETRA * l)
{
	if (l->letra == 'C')
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
		l->pts[7][1] = -20;   // y

		l->pts[8][0] =  10;   // x
		l->pts[8][1] = -20;   // y

		l->pts[9][0] =  10;   // x
		l->pts[9][1] = -10;   // y

		l->pts[10][0] =  30;   // x
		l->pts[10][1] = -10;   // y

		l->pts[11][0] =  30;   // x
		l->pts[11][1] = -30;   // y

		l->pts[12][0] =  20;   // x
		l->pts[12][1] = -40;   // y

		l->pts[13][0] = -20;   // x
		l->pts[13][1] = -40;   // y

		l->pts[14][0] = -30;   // x
		l->pts[14][1] = -30;   // y

		l->pts[15][0] = -30;   // x
		l->pts[15][1] =  30;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicD(LETRA * l)
{  int i;
	if (l->letra == 'D')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =  10;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  30;   // x
		l->pts[2][1] =  20;   // y

		l->pts[3][0] =  30;   // x
		l->pts[3][1] = -20;   // y

		l->pts[4][0] =  10;   // x
		l->pts[4][1] = -40;   // y

		l->pts[5][0] = -30;   // x
		l->pts[5][1] = -40;   // y

		l->pts[6][0] = -10;   // x
		l->pts[6][1] =  20;   // y

		l->pts[7][0] =   0;   // x
		l->pts[7][1] =  20;   // y

		l->pts[8][0] =  10;   // x
		l->pts[8][1] =  10;   // y

		l->pts[9][0] =  10;   // x
		l->pts[9][1] = -10;   // y

		l->pts[10][0] =   0;   // x
		l->pts[10][1] = -20;   // y

		l->pts[11][0] = -10;   // x
		l->pts[11][1] = -20;   // y

		InicGeral(l);
//Arestas: 1a face
		for(i=0;i<5;i++)
		{  l->art[i][0]=i;
			l->art[i][1]=i+1;
		}
		l->art[5][0]=5;
		l->art[5][1]=0;
		for(i=6;i<11;i++)
		{  l->art[i][0]=i;
			l->art[i][1]=i+1;
		}
		l->art[11][0]=11;
		l->art[11][1]=6;
		for(i=12;i<17;i++)
		{  l->art[i][0]=i;
			l->art[i][1]=i+1;
		}
		l->art[17][0]=17;
		l->art[17][1]=12;
		for(i=18;i<23;i++)
		{  l->art[i][0]=i;
			l->art[i][1]=i+1;
		}
		l->art[23][0]=23;
		l->art[23][1]=18;
// prof
		for(i=24;i<36;i++)
		{
		l->art[i][0]=i-24;
		l->art[i][1]=i-12;
		}
	}
}

void InicE(LETRA * l)
{
	if (l->letra == 'E')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =  30;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  30;   // x
		l->pts[2][1] =  20;   // y

		l->pts[3][0] = -10;   // x
		l->pts[3][1] =  20;   // y

		l->pts[4][0] = -10;   // x
		l->pts[4][1] =  10;   // y

		l->pts[5][0] =  10;   // x
		l->pts[5][1] =  10;   // y

		l->pts[6][0] =  10;   // x
		l->pts[6][1] = -10;   // y

		l->pts[7][0] = -10;   // x
		l->pts[7][1] = -10;   // y

		l->pts[8][0] = -10;   // x
		l->pts[8][1] = -20;   // y

		l->pts[9][0] =  30;   // x
		l->pts[9][1] = -20;   // y

		l->pts[10][0] =  30;   // x
		l->pts[10][1] = -40;   // y

		l->pts[11][0] = -30;   // x
		l->pts[11][1] = -40;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicF(LETRA * l)
{
	if (l->letra == 'F')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =  30;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  30;   // x
		l->pts[2][1] =  20;   // y

		l->pts[3][0] = -10;   // x
		l->pts[3][1] =  20;   // y

		l->pts[4][0] = -10;   // x
		l->pts[4][1] =  10;   // y

		l->pts[5][0] =  10;   // x
		l->pts[5][1] =  10;   // y

		l->pts[6][0] =  10;   // x
		l->pts[6][1] = -10;   // y

		l->pts[7][0] = -10;   // x
		l->pts[7][1] = -10;   // y

		l->pts[8][0] = -10;   // x
		l->pts[8][1] = -40;   // y

		l->pts[9][0] = -30;   // x
		l->pts[9][1] = -40;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicG(LETRA * l)
{
	if (l->letra == 'G')
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
		l->pts[7][1] = -20;   // y

		l->pts[8][0] =  10;   // x
		l->pts[8][1] = -20;   // y

		l->pts[9][0] =  10;   // x
		l->pts[9][1] = -10;   // y

		l->pts[10][0] =   0;   // x
		l->pts[10][1] = -10;   // y

		l->pts[11][0] =   0;   // x
		l->pts[11][1] =   0;   // y

		l->pts[12][0] =  30;   // x
		l->pts[12][1] =   0;   // y

		l->pts[13][0] =  30;   // x
		l->pts[13][1] = -30;   // y

		l->pts[14][0] =  20;   // x
		l->pts[14][1] = -40;   // y

		l->pts[15][0] = -20;   // x
		l->pts[15][1] = -40;   // y

		l->pts[16][0] = -30;   // x
		l->pts[16][1] = -30;   // y

		l->pts[17][0] = -30;   // x
		l->pts[17][1] =  30;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicH(LETRA * l)
{
	if (l->letra == 'H')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] = -10;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] = -10;   // x
		l->pts[2][1] =  10;   // y

		l->pts[3][0] =  10;   // x
		l->pts[3][1] =  10;   // y

		l->pts[4][0] =  10;   // x
		l->pts[4][1] =  40;   // y

		l->pts[5][0] =  30;   // x
		l->pts[5][1] =  40;   // y

		l->pts[6][0] =  30;   // x
		l->pts[6][1] = -40;   // y

		l->pts[7][0] =  10;   // x
		l->pts[7][1] = -40;   // y

		l->pts[8][0] =  10;   // x
		l->pts[8][1] = -10;   // y

		l->pts[9][0] = -10;   // x
		l->pts[9][1] = -10;   // y

		l->pts[10][0] = -10;   // x
		l->pts[10][1] = -40;   // y

		l->pts[11][0] = -30;   // x
		l->pts[11][1] = -40;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicI(LETRA * l)
{
	if (l->letra == 'I')
	{
// ptos da 1a. face:
		l->pts[0][0] = -20;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =  20;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  20;   // x
		l->pts[2][1] =  20;   // y

		l->pts[3][0] =  10;   // x
		l->pts[3][1] =  20;   // y

		l->pts[4][0] =  10;   // x
		l->pts[4][1] = -20;   // y

		l->pts[5][0] =  20;   // x
		l->pts[5][1] = -20;   // y

		l->pts[6][0] =  20;   // x
		l->pts[6][1] = -40;   // y

		l->pts[7][0] = -20;   // x
		l->pts[7][1] = -40;   // y

		l->pts[8][0] = -20;   // x
		l->pts[8][1] = -20;   // y

		l->pts[9][0] = -10;   // x
		l->pts[9][1] = -20;   // y

		l->pts[10][0] = -10;   // x
		l->pts[10][1] =  20;   // y

		l->pts[11][0] = -20;   // x
		l->pts[11][1] =  20;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicJ(LETRA* l)
{
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

void InicK(LETRA * l)
{
	if (l->letra == 'K')
	{
// ptos da 1a. face:
		l->pts[0][0] = -20;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =   0;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =   0;   // x
		l->pts[2][1] =  10;   // y

		l->pts[3][0] =  20;   // x
		l->pts[3][1] =  40;   // y

		l->pts[4][0] =  40;   // x
		l->pts[4][1] =  40;   // y

		l->pts[5][0] =  10;   // x
		l->pts[5][1] =   0;   // y

		l->pts[6][0] =  40;   // x
		l->pts[6][1] = -40;   // y

		l->pts[7][0] =  20;   // x
		l->pts[7][1] = -40;   // y

		l->pts[8][0] =   0;   // x
		l->pts[8][1] = -10;   // y

		l->pts[9][0] =   0;   // x
		l->pts[9][1] = -40;   // y

		l->pts[10][0] = -20;   // x
		l->pts[10][1] = -40;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicL(LETRA * l)
{
	if (l->letra == 'L')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] = -10;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] = -10;   // x
		l->pts[2][1] = -20;   // y

		l->pts[3][0] =  30;   // x
		l->pts[3][1] = -20;   // y

		l->pts[4][0] =  30;   // x
		l->pts[4][1] = -40;   // y

		l->pts[5][0] = -30;   // x
		l->pts[5][1] = -40;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicM(LETRA * l)
{
	if (l->letra == 'M')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] = -10;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =   0;   // x
		l->pts[2][1] =  20;   // y

		l->pts[3][0] =  10;   // x
		l->pts[3][1] =  40;   // y

		l->pts[4][0] =  30;   // x
		l->pts[4][1] =  40;   // y

		l->pts[5][0] =  30;   // x
		l->pts[5][1] = -40;   // y

		l->pts[6][0] =  10;   // x
		l->pts[6][1] = -40;   // y

		l->pts[7][0] =  10;   // x
		l->pts[7][1] =  10;   // y

		l->pts[8][0] =   0;   // x
		l->pts[8][1] = -10;   // y

		l->pts[9][0] = -10;   // x
		l->pts[9][1] =  10;   // y

		l->pts[10][0] = -10;   // x
		l->pts[10][1] = -40;   // y

		l->pts[11][0] = -30;   // x
		l->pts[11][1] = -40;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicN(LETRA * l)
{
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

void InicO(LETRA * l)
{
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

void InicP(LETRA * l)
{
	if (l->letra == 'P')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =  20;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  30;   // x
		l->pts[2][1] =  30;   // y

		l->pts[3][0] =  30;   // x
		l->pts[3][1] = -10;   // y

		l->pts[4][0] =  20;   // x
		l->pts[4][1] = -20;   // y

		l->pts[5][0] = -10;   // x
		l->pts[5][1] = -20;   // y

		l->pts[6][0] = -10;   // x
		l->pts[6][1] = -40;   // y

		l->pts[7][0] = -30;   // x
		l->pts[7][1] = -40;   // y

		l->pts[8][0] = -10;   // x
		l->pts[8][1] =   0;   // y

		l->pts[9][0] =  10;   // x
		l->pts[9][1] =   0;   // y

		l->pts[10][0] =  10;   // x
		l->pts[10][1] =  20;   // y

		l->pts[11][0] = -10;   // x
		l->pts[11][1] =  20;   // y

		InicGeral(l);
		InicArt2(l);
	}
}

void InicQ(LETRA * l)
{
	int i;
	if (l->letra == 'Q')
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

		l->pts[4][0] =  30;   // x
		l->pts[4][1] = -40;   // y

		l->pts[5][0] =  20;   // x
		l->pts[5][1] = -40;   // y

		l->pts[6][0] = -20;   // x
		l->pts[6][1] = -40;   // y

		l->pts[7][0] = -30;   // x
		l->pts[7][1] = -30;   // y

		l->pts[8][0] = -30;   // x
		l->pts[8][1] =  30;   // y

		l->pts[9][0] = -10;   // x
		l->pts[9][1] =  20;   // y

		l->pts[10][0] =  10;   // x
		l->pts[10][1] =  20;   // y

		l->pts[11][0] =  10;   // x
		l->pts[11][1] = -10;   // y

		l->pts[12][0] =   0;   // x
		l->pts[12][1] = -10;   // y

		l->pts[13][0] =   0;   // x
		l->pts[13][1] = -20;   // y

		l->pts[14][0] = -10;   // x
		l->pts[14][1] = -20;   // y

		InicGeral(l);
//1a face
	l->art[0][0]=0;	l->art[0][1]=1;	l->art[1][0]=1;	l->art[1][1]=2;
	l->art[2][0]=2;	l->art[2][1]=4;	l->art[3][0]=4;	l->art[3][1]=6;
	l->art[4][0]=6;	l->art[4][1]=7;	l->art[5][0]=7;	l->art[5][1]=8;
	l->art[6][0]=8;	l->art[6][1]=0;	l->art[7][0]=9;	l->art[7][1]=10;
	l->art[8][0]=10;	l->art[8][1]=11;	l->art[9][0]=11;	l->art[9][1]=12;
	l->art[10][0]=12;	l->art[10][1]=13;	l->art[11][0]=13;	l->art[11][1]=14;
	l->art[12][0]=14;	l->art[12][1]=9;	l->art[13][0]=3;	l->art[13][1]=11;
	l->art[14][0]=5;	l->art[14][1]=13;
//2a face
	l->art[15][0]=15;	l->art[15][1]=16;	l->art[16][0]=16;	l->art[16][1]=17;
	l->art[17][0]=17;	l->art[17][1]=19;	l->art[18][0]=19; l->art[18][1]=21;
	l->art[19][0]=21;	l->art[19][1]=22;	l->art[20][0]=22;	l->art[20][1]=23;
	l->art[21][0]=23;	l->art[21][1]=15;	l->art[22][0]=24;	l->art[22][1]=25;
	l->art[23][0]=25;	l->art[23][1]=26;	l->art[24][0]=26;	l->art[24][1]=27;
	l->art[25][0]=27;	l->art[25][1]=28;	l->art[26][0]=28;	l->art[26][1]=29;
	l->art[27][0]=29;	l->art[27][1]=24;	l->art[28][0]=26;	l->art[28][1]=18;
	l->art[29][0]=28;	l->art[29][1]=26;
//prof
	for(i=30;i<45;i++)
		{
		l->art[i][0]=i-30;
		l->art[i][1]=i-15;
		}
	}
}

void InicR(LETRA * l)
{
	if (l->letra == 'R')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =  20;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  30;   // x
		l->pts[2][1] =  30;   // y

		l->pts[3][0] =  30;   // x
		l->pts[3][1] = -10;   // y

		l->pts[4][0] =  20;   // x
		l->pts[4][1] = -20;   // y

		l->pts[5][0] =  30;   // x
		l->pts[5][1] = -40;   // y

		l->pts[6][0] =   0;   // x
		l->pts[6][1] = -40;   // y

		l->pts[7][0] = -10;   // x
		l->pts[7][1] = -20;   // y

		l->pts[8][0] = -10;   // x
		l->pts[8][1] = -40;   // y

		l->pts[9][0] = -30;   // x
		l->pts[9][1] = -40;   // y

		l->pts[10][0] = -10;   // x
		l->pts[10][1] =  20;   // y

		l->pts[11][0] =  10;   // x
		l->pts[11][1] =  20;   // y

		l->pts[12][0] =  10;   // x
		l->pts[12][1] =   0;   // y

		l->pts[13][0] = -10;   // x
		l->pts[13][1] =   0;   // y

		InicGeral(l);
		InicArt2(l);
	}
}

void InicS(LETRA * l)
{
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

void InicT(LETRA * l)
{
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

void InicU(LETRA * l)
{
	if (l->letra == 'U')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] = -10;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] = -10;   // x
		l->pts[2][1] = -20;   // y

		l->pts[3][0] =  10;   // x
		l->pts[3][1] = -20;   // y

		l->pts[4][0] =  10;   // x
		l->pts[4][1] =  40;   // y

		l->pts[5][0] =  30;   // x
		l->pts[5][1] =  40;   // y

		l->pts[6][0] =  30;   // x
		l->pts[6][1] = -30;   // y

		l->pts[7][0] =  20;   // x
		l->pts[7][1] = -40;   // y

		l->pts[8][0] = -20;   // x
		l->pts[8][1] = -40;   // y

		l->pts[9][0] = -30;   // x
		l->pts[9][1] = -30;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicV(LETRA * l)
{
	if (l->letra == 'V')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] = -10;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] = -10;   // x
		l->pts[2][1] = -10;   // y

		l->pts[3][0] =  10;   // x
		l->pts[3][1] = -10;   // y

		l->pts[4][0] =  10;   // x
		l->pts[4][1] =  40;   // y

		l->pts[5][0] =  30;   // x
		l->pts[5][1] =  40;   // y

		l->pts[6][0] =  30;   // x
		l->pts[6][1] = -20;   // y

		l->pts[7][0] =  10;   // x
		l->pts[7][1] = -40;   // y

		l->pts[8][0] = -10;   // x
		l->pts[8][1] = -40;   // y

		l->pts[9][0] = -30;   // x
		l->pts[9][1] = -20;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicW(LETRA * l)
{
	if (l->letra == 'W')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] = -10;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] = -10;   // x
		l->pts[2][1] = -10;   // y

		l->pts[3][0] =   0;   // x
		l->pts[3][1] =   0;   // y

		l->pts[4][0] =  10;   // x
		l->pts[4][1] = -10;   // y

		l->pts[5][0] =  10;   // x
		l->pts[5][1] =  40;   // y

		l->pts[6][0] =  30;   // x
		l->pts[6][1] =  40;   // y

		l->pts[7][0] =  30;   // x
		l->pts[7][1] = -30;   // y

		l->pts[8][0] =  20;   // x
		l->pts[8][1] = -40;   // y

		l->pts[9][0] =  10;   // x
		l->pts[9][1] = -40;   // y

		l->pts[10][0] =   0;   // x
		l->pts[10][1] = -30;   // y

		l->pts[11][0] = -10;   // x
		l->pts[11][1] = -40;   // y

		l->pts[12][0] = -20;   // x
		l->pts[12][1] = -40;   // y

		l->pts[13][0] = -30;   // x
		l->pts[13][1] = -30;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicX(LETRA * l)
{
	if (l->letra == 'X')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] = -10;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] = -10;   // x
		l->pts[2][1] =  20;   // y

		l->pts[3][0] =   0;   // x
		l->pts[3][1] =  10;   // y

		l->pts[4][0] =  10;   // x
		l->pts[4][1] =  20;   // y

		l->pts[5][0] =  10;   // x
		l->pts[5][1] =  40;   // y

		l->pts[6][0] =  30;   // x
		l->pts[6][1] =  40;   // y

		l->pts[7][0] =  30;   // x
		l->pts[7][1] =  20;   // y

		l->pts[8][0] =  20;   // x
		l->pts[8][1] =   0;   // y

		l->pts[9][0] =  30;   // x
		l->pts[9][1] = -20;   // y

		l->pts[10][0] =  30;   // x
		l->pts[10][1] = -40;   // y

		l->pts[11][0] =  10;   // x
		l->pts[11][1] = -40;   // y

		l->pts[12][0] =  10;   // x
		l->pts[12][1] = -20;   // y

		l->pts[13][0] =   0;   // x
		l->pts[13][1] = -10;   // y

		l->pts[14][0] = -10;   // x
		l->pts[14][1] = -20;   // y

		l->pts[15][0] = -10;   // x
		l->pts[15][1] = -40;   // y

		l->pts[16][0] = -30;   // x
		l->pts[16][1] = -40;   // y

		l->pts[17][0] = -30;   // x
		l->pts[17][1] = -20;   // y

		l->pts[18][0] = -20;   // x
		l->pts[18][1] =   0;   // y

		l->pts[19][0] = -30;   // x
		l->pts[19][1] =  20;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicY(LETRA * l)
{
	if (l->letra == 'Y')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] = -10;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] = -10;   // x
		l->pts[2][1] =  20;   // y

		l->pts[3][0] =   0;   // x
		l->pts[3][1] =  10;   // y

		l->pts[4][0] =  10;   // x
		l->pts[4][1] =  20;   // y

		l->pts[5][0] =  10;   // x
		l->pts[5][1] =  40;   // y

		l->pts[6][0] =  30;   // x
		l->pts[6][1] =  40;   // y

		l->pts[7][0] =  30;   // x
		l->pts[7][1] =  20;   // y

		l->pts[8][0] =  10;   // x
		l->pts[8][1] =   0;   // y

		l->pts[9][0] =  10;   // x
		l->pts[9][1] = -40;   // y

		l->pts[10][0] = -10;   // x
		l->pts[10][1] = -40;   // y

		l->pts[11][0] = -10;   // x
		l->pts[11][1] =   0;   // y

		l->pts[12][0] = -30;   // x
		l->pts[12][1] =  20;   // y

		InicGeral(l);
		InicArt1(l);
	}
}

void InicZ(LETRA * l)
{
	if (l->letra == 'Z')
	{
// ptos da 1a. face:
		l->pts[0][0] = -30;   // x
		l->pts[0][1] =  40;   // y

		l->pts[1][0] =  30;   // x
		l->pts[1][1] =  40;   // y

		l->pts[2][0] =  30;   // x
		l->pts[2][1] =   0;   // y

		l->pts[3][0] = -10;   // x
		l->pts[3][1] = -10;   // y

		l->pts[4][0] = -10;   // x
		l->pts[4][1] = -20;   // y

		l->pts[5][0] =  30;   // x
		l->pts[5][1] = -20;   // y

		l->pts[6][0] =  30;   // x
		l->pts[6][1] = -40;   // y

		l->pts[7][0] = -30;   // x
		l->pts[7][1] = -40;   // y

		l->pts[8][0] = -30;   // x
		l->pts[8][1] = -10;   // y

		l->pts[9][0] =  10;   // x
		l->pts[9][1] =  10;   // y

		l->pts[10][0] =  10;   // x
		l->pts[10][1] =  20;   // y

		l->pts[11][0] = -30;   // x
		l->pts[11][1] =  20;   // y

		InicGeral(l);
		InicArt1(l);
	}
}


void main ()
{
	 int i, desl;
	 FILE * f;

	 LETRA letras[NumLetras] = {{'A',28,42,NULL,NULL},{'B',34,51,NULL,NULL},
	 {'C',32,48,NULL,NULL},{'D',24,36,NULL,NULL},{'E',24,36,NULL,NULL},
	 {'F',20,30,NULL,NULL},{'G',36,54,NULL,NULL},{'H',24,36,NULL,NULL},
	 {'I',24,36,NULL,NULL},{'J',24,36,NULL,NULL},{'K',22,33,NULL,NULL},
	 {'L',12,18,NULL,NULL},{'M',24,36,NULL,NULL},{'N',20,30,NULL,NULL},
	 {'O',24,36,NULL,NULL},{'P',24,36,NULL,NULL},{'Q',30,45,NULL,NULL},
	 {'R',28,42,NULL,NULL},{'S',40,60,NULL,NULL},{'T',16,24,NULL,NULL},
	 {'U',20,30,NULL,NULL},{'V',20,30,NULL,NULL},{'W',28,42,NULL,NULL},
	 {'X',40,60,NULL,NULL},{'Y',26,39,NULL,NULL},{'Z',24,36,NULL,NULL}};

	NO Cab[NumLetras];
	funcao * func[26] ={ InicA, InicB, InicC, InicD, InicE, InicF, InicG,
								InicH, InicI, InicJ, InicK, InicL, InicM, InicN,
								InicO, InicP, InicQ, InicR, InicS, InicT, InicU, 
								InicV, InicW, InicX, InicY, InicZ }; 

	AlocaEspTodasLetras(letras);
	for(i=0; i<NumLetras; i++)
		func[i] (&letras[i]);

	for(i=0;i<NumLetras;i++)
	{
		Cab[i].npts=letras[i].npts;
		Cab[i].nart=letras[i].nart;
	}
	f = fopen("LETRAS.DAT","wb");
	fseek(f,0,SEEK_SET); 			// posiciona no inicio do arq.

	Cab[0].rf=NumLetras*sizeof(NO);
	fwrite(&Cab[0].rf,sizeof(NO),1,f);	 // grava o cabecalho[0]
	for(i=1; i<NumLetras; i++)
	{
		desl=(Cab[i-1].npts*sizeof(Ponto))+(Cab[i-1].nart*sizeof(Aresta));
		Cab[i].rf = Cab[i-1].rf + desl;
		fwrite(&Cab[i],sizeof(NO),1,f);    // grava cabecalho
	}
	fseek(f,NumLetras * sizeof(NO), SEEK_SET); // posiciona apos o cabecalho
	for(i=0; i<NumLetras; i++)
	{
		fwrite(letras[i].pts, sizeof(Ponto), letras[i].npts, f);
		fwrite(letras[i].art, sizeof(Aresta), letras[i].nart, f);
	}
	fclose(f);

	getch();
	LibEspTodasLetras(letras);
	printf(" Cont : %d",cont);
}