//*************************************************************************** 
//	PROGRAMA: LETRAS.CPP
//	DESCRICAO: Le um string do teclado, de ate 15 caracteres,
//		  desenha as letras na tela, em 3D;
//		  Usa alocacao dinamica de memoria;
//		  O arquivo de dados e' LETRAS.DAT;
//	DATA: primeira versao: 23/07/94  atualizacao: 19/11/94
//	PROGRAMADOR: Jonatas de Mello No. 42 - CIENCIA DA COMPUTACAO
//***************************************************************************

// INCLUDE'S
# include <graphics.h>
# include <stdlib.h>
# include <conio.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <ctype.h>
# define NumLetras 26

// ESTRUTURAS DE DADOS
typedef float Ponto[4];
typedef int Aresta[2];
typedef float Mat[4][4];
typedef struct tagLETRA{
		int pos;
		int npts,nart;
		Ponto* pts;
		Aresta* art;
}LETRA;
typedef struct tagNO{
		int rf, npts, nart;
}NO;

int cont = 0;  // contador de Memoria Dinamica Alocada
 
// PROTOTYPE'S
void DesenhaReta (Ponto p1, Ponto p2, int cor);
void DesenhaLinha(int startx, int starty, int endx, int endy, int cor);
void DesenhaLetra(LETRA l, int cor);
void MultMat (Mat M1, Mat M2, Mat M3);
void MultPtoMat (Ponto P, Mat M, Ponto P1);
void CriaMov (Mat MM, float tx, float ty, float tz, float ex, float ey, float ez, float rx, float ry, float rz);
void EfetuaMov (LETRA * l, int comp);
void MoveRot(LETRA * l, float rx, float ry, float rz, int comp);
void MoveEsc(LETRA * l, float ex, float ey, float ez, int comp);
void MoveTrans(LETRA * l, float tx, float ty, float tz, int comp);
void TransladaPonto(Ponto p, float tx, float ty, float tz);
void TransladaLetra(LETRA* c, float tx, float ty, float tz);
void EscalaLetra(LETRA* c, float ex, float ey, float ez);
void EscalaPonto(Ponto p, float ex, float ey, float ez);
void RotacionaPonto(Ponto p, float rx, float ry, float rz);
void RotacionaLetra(LETRA* c, float rx, float ry, float rz);
void * Malloc(int size);
void Free(void * ptr);
void LiberaEspaco(LETRA* l);
void LeLetra(FILE * f, LETRA * l, int RF);
void MoveLetra(LETRA * l);
void CalcDesl(LETRA * l, int comp);
void LePalavra(char * Palavra); 
int GetKey(void);

// FUNCOES
int Getkey(void)
{
	int key;
	key = getch();
	if (key==0)
		key = 256 * getch();
	return(key);
}

void EfetuaMov(LETRA* l, int comp)
{
	int ch;
	float x=0.0872; // em radiano vale 5 graus

//desenha todas as letras
	for (ch=0; ch<comp; ch++)
		DesenhaLetra(l[ch],15);

	do {
		ch=Getkey();
		switch (ch)	{
		case 69: 	// escala +
			MoveEsc(l,1.1,1.1,1.1,comp);
			break;
		case 101:	// escala -
			MoveEsc(l,0.9,0.9,0.9,comp);
			break;
	// rotaciona:
		case 88: 	//   x_cima
			MoveRot(l,x,0,0,comp);
			break;
		case 120: 	//   x_baixo
			MoveRot(l,-x,0,0,comp);
			break;
		case 89: 	//   y_cima
			MoveRot(l,0,x,0,comp);
			break;
		case 121: 	//   y_baixo
			MoveRot(l,0,-x,0,comp);
			break;
		case 90: 	//   z_cima
			MoveRot(l,0,0,x,comp);
			break;
		case 122: 	//   z_baixo
			MoveRot(l,0,0,-x,comp);
			break;
	// translada
		case 18432: 	//   cima
			MoveTrans(l,0,5,0,comp);
			break;
		case 20480: 	//   baixo
			MoveTrans(l,0,-5,0,comp);
			break;
		case 19200: 	//   esq
			MoveTrans(l,-5,0,0,comp);
			break;
		case 19712: 	//   dir
			MoveTrans(l,5,0,0,comp);
			break;
		};
	} while (ch != 27);   // ESC - sai
}

void MoveRot(LETRA * l, float rx, float ry, float rz, int comp)
{
	 int x;
	 for (x=0; x<comp; x++)
		 DesenhaLetra(l[x],0);
	 for (x=0; x<comp; x++)
		 RotacionaLetra(&l[x],rx,ry,rz);
	 for (x=0; x<comp; x++)
		 DesenhaLetra(l[x],15);
}

void MoveEsc(LETRA * l, float ex, float ey, float ez, int comp)
{
	 int x;
	 for (x=0; x<comp; x++)
		 DesenhaLetra(l[x],0);
	 for (x=0; x<comp; x++)
		 EscalaLetra(&l[x],ex,ey,ez);
	 for (x=0; x<comp; x++)
		 DesenhaLetra(l[x],15);
}

void MoveTrans(LETRA * l, float tx, float ty, float tz, int comp)
{
	 int x;
	 for (x=0; x<comp; x++)
		 DesenhaLetra(l[x],0);
	 for (x=0; x<comp; x++)
		 TransladaLetra(&l[x],tx,ty,tz);
	 for (x=0; x<comp; x++)
		 DesenhaLetra(l[x],15);
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
		}
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

void CalcDesl(LETRA * l, int comp)
{
	int i,j=0;
	for(i=0; i<comp; i++)
	{
		l[i].pos= -comp + j;
		j+=2;
	}
}

void MoveLetra(LETRA * l)
{
	int x,n_desl;
	if(l->pos > 0) n_desl = l->pos;
		else n_desl = - l->pos;

	for(x=0; x<n_desl; x++)    // numero de deslocamentos
		{
		if(l->pos > 0)
				TransladaLetra(l,40,0,0);     // um desl. dir
		else
				TransladaLetra(l,-40,0,0);    // um desl. esq
		}
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

void LiberaEspaco(LETRA* l)
{
	Free(l->pts);
	Free(l->art);
}

void DesenhaLetra(LETRA l, int cor)
{
	int i;
	for (i=0; i<l.nart; i++)
		DesenhaReta(l.pts[l.art[i][0]], l.pts[l.art[i][1]], cor);
}

void LePalavra(char * Palavra) 
{
// Le o string, verifica sua consistencia e apresenta a tela inicial
	int i,comp;
	clrscr();
	printf(" O tamanho maximo e de 15 letras!!! \n\n");
	printf("Digite a palavra: ");
	gets(Palavra);
	printf("\n\n\t:INFORMACOES:\n\n");
	printf("Use as seguintes teclas para movimentar a palavra\n\n");
	printf("E = escala + \t e = escala - \t Setas = translada\n");
	printf("X = rotaciona no eixo X + \t x = rotaciona no eixo X -\n");
	printf("Y = rotaciona no eixo Y + \t y = rotaciona no eixo Y -\n");
	printf("Z = rotaciona no eixo Z + \t z = rotaciona no eixo Z -\n");
	printf("\nESC = sai \n\n Tecle algo para continuar\n");
	comp=strlen(Palavra);
	if (comp>15) 
	{
		Palavra[15] = '\0';
		comp = strlen(Palavra);
	}
	for (i=0; i<comp; i++)
		Palavra[i] = toupper(Palavra[i]);
	getch();
}

void LeLetra(FILE * f, LETRA * l, int RF)
{
	fseek(f,RF,SEEK_SET); 	// posiciona o ponteiro do arq.
	l->pts=(Ponto*)Malloc(l->npts*sizeof(Ponto));	// aloca memoria
	l->art=(Aresta*)Malloc(l->nart*sizeof(Aresta));	// aloca memoria
	fread(l->pts,sizeof(Ponto),l->npts,f); 			// le os pontos
	fread(l->art,sizeof(Aresta),l->nart,f);			// le as arestas
}

void main ()
{
	float lixo=sin(0);
	FILE * f;
	int gdriver, gmode;
	int i, RF, RL, comp;
	char Palavra[15];

	LETRA * letras;
	NO Cab[NumLetras];

	LePalavra(Palavra);
	comp = strlen(Palavra);

	letras = (LETRA *) Malloc(comp * sizeof(LETRA));

	f=fopen("LETRAS.DAT","rb");
	if (f == NULL)   	// ERRO ao abrir a interface
	{
		printf("\nERROR - Cannot open input file.\n");
	}
	else
	{
		fread(Cab,sizeof(NO),NumLetras,f);

		for(i=0; Palavra[i]!='\0'; i++)
		{
			RL = Palavra[i] - 'A';
			letras[i].npts=Cab[RL].npts;
			letras[i].nart=Cab[RL].nart;
			RF = Cab[Palavra[i]-'A'].rf;
			LeLetra(f,&letras[i],RF);
		}
		CalcDesl(letras,comp);

		detectgraph (&gdriver, &gmode);
//		initgraph (&gdriver, &gmode, "g:\\usr\\compila\\borlandc\\bgi");
		initgraph (&gdriver, &gmode, "");

		for(i=0; i<comp; i++)
		{	
			MoveLetra(&letras[i]);
			DesenhaLetra(letras[i],15);
		}
		EfetuaMov(letras,comp);

		cleardevice();
		closegraph ();
		fclose(f);
	}

	for(i=0; Palavra[i]!='\0'; i++)
		LiberaEspaco(&letras[i]);
	Free(letras);
	printf(" Contador de Memoria Alocada/Liberada : %d",cont);
}

// FIM DO PROGRAMA