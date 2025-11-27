/*
  * * * Note: modified version to increase readability * * *

  XNOISESPH.C, Plots a noise-sphere of the file.

  Based on
  NOISESPH.PAS, A Noise Sphere plotter written in Turbo Pascal (23-Mar-96)
  Robert Rothenburg Walking-Owl <WlkngOwl@unix.asb.com>
  No copyright is claimed.	No guarantees made.

  Compiled on Linux with:
	cc -o xnoisesph xnoisesph.c -L /usr/X11R6/lib -lX11 -lm

  Usage: xnoisesph file

  This program reads a file of random or pseudo-random data and plots
  a noise sphere of the data. Poor RNGs or sampling methods will show
  clear patterns (definite splotches or spirals).

  The theory behind this is to get a set of 3D polar coordinates from
  the RNG and plot them.  An array is kept of the values, which is
  rotated each time a new byte is read (see the code in the main procedure).

  Rather than plot one sphere which can be rotated around any axis,
  it was easier to plot the sphere from three different angles.

  This program is based on a description from the article below.
  It was proposed as a means of testing pseudo-RNGs:

  Pickover, Clifford A. 1995.
  "Random number generators: pretty good ones are easy to find."
  The Visual Computer (1005) 11:369-377.

  See also Pickover, nd., "Keys to Infinity." Chapter 31.
*/

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <unistd.h>

#define MATH_PI 3.14159265358979323846

/* types and structures */
typedef struct _Cartesian {
	double x, y, z;
	unsigned Color;
} Cartesian;

typedef struct _Polar {
	double r, theta, phi;
} Polar;


/* function prototypes  */
double ByteToReal(unsigned char);
unsigned int ScaleColor(double);
int Round(double);
void Plot(Cartesian *);
void PolarToCartesian(Polar *, Cartesian *);


/* global variables */
int MidA, MidB, MidC, MidY, Scale;
int width, height, bwidth, depth, wx, wy;

FILE *inputFile;

/* Xlib variables */
Window w;
Display *d;
GC gc;
Window root;
XEvent event;
/* XExposeEvent *ee = (XExposeEvent *)&event; */


/* function definitions */

double ByteToReal(unsigned char b)
{
	/* note that there will be some gaps since we're only using the equivalent of an 8-bit decimal here*/
	return  b / 256.0;
}

unsigned int ScaleColor(double x)
{
	return 0;
}

int Round(double x)
{
	return (int) (x + 0.5);
}

/* Projects 3d coordinates to a 2d screen */
int ProjectPoint(double x) {
	return Round(Scale * x);
}

/* Projects 3d coordinates to a 2d screen */
void Plot(Cartesian *C)
{
	XDrawPoint(d, w, gc, MidA + ProjectPoint(C->y), MidY - ProjectPoint(C->z));
	XDrawPoint(d, w, gc, MidB + ProjectPoint(C->x), MidY - ProjectPoint(C->y));
	XDrawPoint(d, w, gc, MidC + ProjectPoint(C->z), MidY - ProjectPoint(C->x));
}

/* Converts 3-d polar coordinates to cartesian coordinates */
void PolarToCartesian(Polar *P, Cartesian *C)
{
	/*
	Spherical Coordinates: https://mathworld.wolfram.com/SphericalCoordinates.html
	spherical coordinates (r,theta,phi) are related to the Cartesian coordinates (x,y,z) by:
		x =	r * cos theta * sin phi
		y =	r * sin theta * sin phi
		z =	r * cos phi
	*/

	C->x = P->r * sin(P->phi) * cos(P->theta);
	C->y = P->r * sin(P->phi) * sin(P->theta);
	C->z = P->r * cos(P->phi);

	/* We can assign colors based
	  on x, y, z,
	  or r, theta / pi
	  or phi / (2 * pi) */
	C->Color = ScaleColor(C->y);
}

void InitializeGraphics()
{
	/* initialize display */
	if (!(d = XOpenDisplay(NULL)))
	{
		printf("Can't open display\n");
		exit(1);
	}

	w = XCreateSimpleWindow(d,
		RootWindow(d, DefaultScreen(d)),
		0, 0, 640, 480, 0,
		BlackPixel(d, DefaultScreen(d)),
		BlackPixel(d, DefaultScreen(d)));

	XSelectInput(d, w, ExposureMask | KeyPressMask);

	gc = XCreateGC(d, w, 0L, NULL);
	XSetBackground(d, gc, BlackPixel(d, DefaultScreen(d)));
	XSetForeground(d, gc, WhitePixel(d, DefaultScreen(d)));

	XMapRaised(d, w);

	while (XNextEvent(d, &event), event.type != Expose);

	/* * Get the window's actual width and height. */
	XGetGeometry(d, w, &root, &wx, &wy, &width, &height, &bwidth, &depth);
}

void AdjustScale() {

	Scale = width / 6;
	MidA = Scale;
	MidB = 3 * Scale;
	MidC = 5 * Scale;
	MidY = height / 2;
	if (MidY < Scale) {
		Scale = MidY;
	}
}

/* read the next number from input file */
double ReadFromFile(){
	int byte;
	double result;

	byte = getc(inputFile);
	if (byte == EOF) {
		return -1;
	}
	result = ByteToReal((unsigned char) byte);
	return result;
}

void process()
{
	double X[3];
	int i, n = 0;
	Cartesian C;
	Polar P;
	double val;

	AdjustScale();

	/* read the first 3 points from input file */
	for (i = 0; i < 3; i++) {
		val = ReadFromFile();
		if (val < 0)
			break;
		X[i] = val;
	}

	/* read the remaining points from input file */
	n = 0;
	while (1) {
		/*
		Noise Sphere: https://mathworld.wolfram.com/NoiseSphere.html
		A mapping of random number triples to points in spherical coordinates according to:
			radial distance: r     = sqrt( X[n+2] )
			polar angle:     theta = PI * X[n+1]
			azimuthal angle: phi   = 2 * PI * X[n]
		*/

		/* rotate n: (0,1,2) => (1,2,0) => (2,0,1) => (0,1,2) */
		int p0 = n;
		int p1 = (n + 1) % 3;
		int p2 = (n + 2) % 3;

		/* get the next point */
		P.r = sqrt(X[p2]); /* pt 2 */
		P.theta = MATH_PI * X[p1]; /* pt 1 */
		P.phi = 2 * MATH_PI * X[p0]; /* pt 0 */

		PolarToCartesian(&P, &C);

		Plot(&C);

		/* read the next point from input file */
		val = ReadFromFile();
		if (val < 0)
			break;
		X[n] = val;

		/* rotate n: (0,1,2) => (1,2,0) => (2,0,1) => (0,1,2) */
		/* n becomes the next value in the array*/
		n = (n + 1) % 3; /* pt 1 */
	}
	/* printf("done"); */
}

/* main function */
int main(int argc, char *argv[])
{
	char *fname;
	char *pgm;

	/* check parameters and input file */
	pgm = argv[0]; // program name
	if (argc != 2) {
		printf("Usage: %s [file]\n", pgm);
		exit(1);
	}
	if (argc == 2) {
		fname = argv[1];
		if ((inputFile = fopen(fname, "rb")) == NULL) {
			printf("Can't open file %s \n", argv[1]);
			exit(1);
		}
	}

	/* Initialize X11 stuff */
	InitializeGraphics();

	/* * Initialization done, window on screen; time for real work. */
	process();

	/* * Now hang out.  Let the window manager kill us. */
	while (1) {
		XNextEvent(d, &event);
		if (event.type == KeyPress)
			break;
	}
	XCloseDisplay(d);

	exit(0);
}
