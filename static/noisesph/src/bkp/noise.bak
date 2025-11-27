#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <graphics.h>

#ifndef M_PI
#define M_PI 3.14159267
#endif

int
  defcolor = LIGHTGRAY,
  triple = 0,
  RZ = 0, RX = 0, RY = 0;

struct Cartesian
{
	double x, y, z;
	unsigned Color;
};

struct Polar
{
	double r, theta, phi;
};

int MidA, MidB, MidC, MidY, Scale;

double X[3];
int error, ScreenInit = 1;
long int size = -1;  // if size>0, plot only size points

int pointSize = 2; 

struct Cartesian C;
struct Polar P;

// ----------------------------------------------------------------------------
#define MAX 3500

float numbers[MAX];

double trunc(double d)
{
  return (d>0) ? floor(d) : ceil(d);
}

void RNG()
{
	long num;
    double x, xi;
    x = 0.1; // seed
    num = MAX;
    int i;

    for (i=0; i<num; i++)
	{
		x = 100 * log(x);
		xi = trunc(x);
		x = fabs(x-xi);
		//printf("%.16f\n",x);
		numbers[i] = x;
    }
    //getchar();
}

/* Initialize the graphics screen (Borland C specific)  and sets the midpoints and scale for the screen */
int InitScreen(void)
{
	int GraphMode, GraphDriver;	
	GraphDriver = VGA;
	GraphMode = VGAHI;
	detectgraph(&GraphDriver, &GraphMode);
	initgraph(&GraphDriver, &GraphMode, "\\TURBOC3\\BGI");
	return graphresult();
}

void InitPoints(void) 
{
	if (triple)
	{
		/* Changed to plot in quadrants, since the resolution is slightly larger */
		Scale = getmaxx() / 4;
		MidA = MidC = Scale, MidB = 3 * Scale;
		MidY = getmaxy() / 4;
	} 
	else
	{
		Scale = getmaxx() / 2;
		MidA = Scale;
		MidY = getmaxy() / 2;
	}
	if (MidY < Scale) 
		Scale = MidY;
}

/* Convert degrees to radians */
#define rads(x) (((double)(x * 2)) * M_PI / 360.0)

/* This could be rewritten to scale a number between -1.0 and 1.0 to
   a grayscale or RBG map, depending on the system one is plotting on.
   (Perhaps setting RGB values based on X, Y and Z independently?) */

#define ScaleColor(x) (defcolor)

/*
unsigned int ScaleColor(double x)
{
  if (x<0) return(LIGHTGRAY); else return(WHITE);
}
*/

/* Rotate C along X, Y and Z axes */
void rotate(struct Cartesian *C)
{
	double x,y,z;
	if (RZ)
	{
	    z = rads(RZ);
	    x = (C->x * cos(z)) + (C->y * sin(z));
	    y = (C->y * cos(z)) - (C->x * sin(z));
	    C->x = x; C->y = y;
	}
	if (RX)
	{
	    x = rads(RX);
	    y = (C->y * cos(x)) + (C->z * sin(x));
	    z = (C->z * cos(x)) - (C->y * sin(x));
	    C->z = z; C->y = y;
	}
	if (RY)
	{
	    y = rads(RY);
	    x = (C->x * cos(y)) + (C->z * sin(y));
	    z = (C->z * cos(y)) - (C->x * sin(y));
	    C->z = z; C->x = x;
	}
}

#define project(x) (ceil(Scale * x))

/* Projects 3d coordinates to a 2d screen */
void Plot(struct Cartesian C)
{
	rotate(&C);
	
	putpixel(MidA + project(C.x), MidY - project(C.y), C.Color);
	
	int left,top,right,bottom;
	left = MidA + project(C.x);
	top = MidY - project(C.y);
	right = left + pointSize;
	bottom = top + pointSize;
	
	rectangle(left,top,right,bottom);
	
	if (triple)
	{
		putpixel(MidB + project(C.y), MidY - project(C.z), C.Color);
		putpixel(MidC + project(C.z), (3 * MidY) - project(C.x), C.Color);
	}
}

/* Converts 3-d polar coordinates to cartesian coordinates */
void PolarToCartesian(struct Polar P, struct Cartesian *C)
{
	/* No rotation was added. Instead we plot from three angles... */
	C->x = P.r * sin(P.phi) * cos(P.theta);
	C->y = P.r * sin(P.phi) * sin(P.theta);
	C->z = P.r * cos(P.phi);
	/* We can assign colors based on C.x, C.y, C.z, or P.r, P.theta / pi or P.phi / (2 * pi) */
	C->Color = ScaleColor(C->z);
}

int plot_file()
{
	int i, j, k;
	int n = 0;

	RNG(); // generate numbers numbers

	InitPoints();

	if (ScreenInit != 0)
	{
		closegraph();     /* shut down graphics system */
		exit(EXIT_FAILURE);
	}

	for(k = 0; k < MAX; ) // all numbers points
	{
		// read the first 3 values
		for (i = 0; i < 3; i++)
		{
			X[i] = numbers[k];
			k++;
		}
		P.r = sqrt(X[(n + 2) % 3]);
		P.theta = M_PI * X[(n + 1) % 3];
		P.phi = 2 * M_PI * X[n];

		n = ++n % 3;

		PolarToCartesian(P, &C);

		Plot(C);
	}
	//getchar();
	//return(kbhit());
	return 1;
}

//int main(int argc, char* argv[])
int main()
{
	if (ScreenInit)
	{
		error = InitScreen();
		if (error != grOk)
		{
			fprintf(stderr, "%s\n", grapherrormsg(error));
			//exit(EXIT_FAILURE);
			return -1;
		}
		ScreenInit = 0;
	}
	plot_file();
	
	getch();  /* gets a char from the keyboard without echoing */
	closegraph();     /* shut down graphics system */
 
	//exit(EXIT_SUCCESS);
	return 0;
}
