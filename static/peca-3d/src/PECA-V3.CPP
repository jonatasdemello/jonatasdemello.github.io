/*
   Programa em 3D que desenha uma peca
   Autor : Jonatas de Mello
   data: 1994-09-01
*/

#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<graphics.h>

// Estruturas de dados e Variaveis

#define nv 48
#define na 72

float xt[nv], yt[nv]; // X, Y tela
float xv, yv, zv; // X, Y, Z view

float X[nv], Y[nv], Z[nv];
float XT[nv], YT[nv];
int V1[na], V2[na];

int lines[na][5]; // 72 lines, 4 pontos (x1, y1 - x2, y2), 1 cor

float pontos[nv][3] = 	{ // 48 vertices (X, Y, Z)
	{0  , 0  , 0}, {10 , 0  , 0}, {10 , 6  , 0}, {0  , 6  , 0}, {0  , 0  , 1}, {10 , 0  , 1}, {10 , 6  , 1}, {0  , 6  , 1},
	{4.3, 1.2, 1}, {5.7, 1.2, 1}, {6.8, 2.2, 1}, {6.8, 3.8, 1}, {5.7, 4.8, 1}, {4.3, 4.8, 1}, {3.2, 3.8, 1}, {3.2, 2.2, 1},
	{4.5, 1.8, 1}, {5.5, 1.8, 1}, {6.2, 2.5, 1}, {6.2, 3.5, 1}, {5.5, 4.2, 1}, {4.5, 4.2, 1}, {3.8, 3.5, 1}, {3.8, 2.5, 1},
	{4.3, 1.2, 5}, {5.7, 1.2, 5}, {6.8, 2.2, 5}, {6.8, 3.8, 5}, {5.7, 4.8, 5}, {4.3, 4.8, 5}, {3.2, 3.8, 5}, {3.2, 2.2, 5},
	{4.5, 1.8, 5}, {5.5, 1.8, 5}, {6.2, 2.5, 5}, {6.2, 3.5, 5}, {5.5, 4.2, 5}, {4.5, 4.2, 5}, {3.8, 3.5, 5}, {3.8, 2.5, 5},
	{1.7, 2.2, 1}, {8.3, 2.2, 1}, {8.3, 3.8, 1}, {1.7, 3.8, 1}, {3.2, 2.2, 3}, {6.8, 2.2, 3}, {6.8, 3.8, 3}, {3.2, 3.8, 3}
};

int vertices[na][3] = {  // 72 arestas (p1,  p2,  cor)
	{0 , 1 , 2}, {1 , 2 , 2}, {2 , 3 , 2}, {3 , 0 , 2}, {4 , 5 , 2}, {5 , 6 , 2}, {6 , 7 , 2}, {7 , 4 , 2},
	{0 , 4 , 2}, {1 , 5 , 2}, {2 , 6 , 2}, {3 , 7 , 2}, {8 , 9 , 3}, {9 , 10, 3}, {10, 11, 3}, {11, 12, 3},
	{12, 13, 3}, {13, 14, 3}, {14, 15, 3}, {15, 8 , 3}, {24, 25, 3}, {25, 26, 3}, {26, 27, 3}, {27, 28, 3},
	{28, 29, 3}, {29, 30, 3}, {30, 31, 3}, {31, 24, 3}, {8 , 24, 3}, {9 , 25, 3}, {10, 26, 3}, {11, 27, 3},
	{12, 28, 3}, {13, 29, 3}, {14, 30, 3}, {15, 31, 3}, {16, 17, 3}, {17, 18, 3}, {18, 19, 3}, {19, 20, 3},
	{20, 21, 3}, {21, 22, 3}, {22, 23, 3}, {23, 16, 3}, {32, 33, 3}, {33, 34, 3}, {34, 35, 3}, {35, 36, 3},
	{36, 37, 3}, {37, 38, 3}, {38, 39, 3}, {39, 32, 3}, {16, 32, 3}, {17, 33, 3}, {18, 34, 3}, {19, 35, 3},
	{20, 36, 3}, {21, 37, 3}, {22, 38, 3}, {23, 39, 3}, {40, 15, 1}, {10, 41, 1}, {41, 42, 1}, {42, 11, 1},
	{14, 43, 1}, {43, 40, 1}, {40, 44, 1}, {41, 45, 1}, {42, 46, 1}, {43, 47, 1}, {47, 44, 1}, {45, 46, 1}
};

void inicializa()
{
	int i;
	for (i = 0; i < nv; i++)
	{
		X[i] = pontos[i][0];
		Y[i] = pontos[i][1];
		Z[i] = pontos[i][2];
	}
	for (i = 0; i < na; i++)
	{
		V1[i] = vertices[i][0];
		V2[i] = vertices[i][1];
	}
	xv = yv = zv = 10;
}

int calcula()
{
	// xv, yv, zv, => coordenadas do observador.
	float a, b, c, k1, k2, k3, k4, k5;
	float kx, ky, k;
	float x, y, z, la;
	float xin, xax, yin, yax;
	// float xmed, ymed;

	int i;
	int xmax, ymax;
	xmax = 640;
	ymax = 480;

	// Calculo das constantes (Geometria Analitica)
	a = sqrt(xv * xv + yv * yv);
	b = sqrt(xv * xv + yv * yv + zv * zv);
	c = a * b;
	k1 = -yv / a;
	k2 = xv / a;
	k3 = -xv * zv / c;
	k4 = -yv * zv / c;
	k5 = a / b;

	// Calculo para projecao na tela
	for (i = 0; i < nv; i++)
	{
		la = a * a + 1 / (xv * (X[i] - xv) + yv * (Y[i] - yv) + zv * (Z[i] - zv));

		x = xv + la * (X[i] - xv);
		y = yv + la * (Y[i] - yv);
		z = zv + la * (Z[i] - zv);

		xt[i] = (k1 * x + k2 * y);
		yt[i] = (k3 * x + k4 * y + k5 * z);
	}

	// ajustar ao tamanho da tela
	xin = X[0];
	xax = X[0];
	yin = Y[0];
	yax = Y[0];

	for (i = 0; i < nv; i++)
	{
		if (xin > xt[i])
			xin = xt[i];
		if (xax < xt[i])
			xax = xt[i];
		if (yin > yt[i])
			yin = yt[i];
		if (yax < yt[i])
			yax = yt[i];
	}

	// xmed = (xax + xin) / 2;
	// ymed = (yax + yin) / 2;

	kx = xmax / (xax - xin);
	ky = ymax / (yax - yin);

	k = ky;
	if (kx < ky) {
		k = kx; 
	}
	x = (xmax - (xax - xin) * k) / 2;

	// ajuste horizontal e vertical
	for (i = 0; i < nv; i++)
	{
		xt[i] = (xt[i] - xin) * k + x;
		yt[i] = ymax - (yt[i] - yin) * k;
	}
	return 0;
}

int linhas()
{
	int i=0;
	int x1, x2, y1, y2, cor;
	
	// add the result points to an array:
	//lines = new int[na, 5]; // 72 arestas x 4 pontos (x1, y1 - x2, y2) x cor

	for (i = 0; i < na; i++)
	{
		x1 = (int) xt[V1[i]];
		y1 = (int) yt[V1[i]];
		x2 = (int) xt[V2[i]];
		y2 = (int) yt[V2[i]];

		cor = vertices[i][2];

		lines[i][0] = x1;
		lines[i][1] = y1;
		lines[i][2] = x2;
		lines[i][3] = y2;
		lines[i][4] = cor;
	}
	return 0;
}

int desenha()
{
	// use graphics library
	int i=0;
	int x1, x2, y1, y2, cor;

	for (i = 0; i < na; i++)
	{
		x1 = lines[i][0];
		y1 = lines[i][1];
		x2 = lines[i][2];
		y2 = lines[i][3];
		cor = lines[i][4];

		setcolor(cor);
		line(x1, y1, x2, y2);
	}
	return 0;
}

int read_input()
{
	int inc = 5;
	int c;

	puts("Q,A, W,S E,D X-END: ");
	c = getch();

	if (c == 65 || c == 113) xv = xv + inc; // A$ = "Q" THEN XV = XV + 10
	if (c == 81 || c == 97 ) xv = xv - inc; // A$ = "A" THEN XV = XV - 10
	if (c == 87 || c == 119) yv = yv + inc; // A$ = "W" THEN YV = YV + 10
	if (c == 83 || c == 115) yv = yv - inc; // A$ = "S" THEN YV = YV - 10
	if (c == 69 || c == 101) zv = zv + inc; // A$ = "E" THEN ZV = ZV + 10
	if (c == 68 || c == 100) zv = zv - inc; // A$ = "D" THEN ZV = ZV - 10
	if (c == 88 || c == 120) return 0; // A$ = "X" THEN END
	return 1;
}

int main(void)
{
	int resp = 1;

	int driver, modo;
	detectgraph(&driver, &modo);
	initgraph(&driver, &modo,"c:\\tc\\bgi");

	inicializa();
	xv=10; yv=10; zv=10;
	do
	{
		cleardevice();
		calcula();
		linhas();
		desenha();
		resp = read_input();
	} while (resp != 0);
	
	getch();
	closegraph();
	return 0;
}

