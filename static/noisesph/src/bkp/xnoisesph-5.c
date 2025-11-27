/*
  * * * Note: modified version to increase readability * * *

  XNOISESPH.C, Plots a noise-sphere of the file.

  Based on
  NOISESPH.PAS, A Noise Sphere plotter written in Turbo Pascal (23-Mar-96)
  Robert Rothenburg Walking-Owl <WlkngOwl@unix.asb.com>
  No copyright is claimed.	No guarantees made.

  Compiled on Linux with:
	cc -o xnoisesph xnoisesph.c -L /usr/X11R6/lib -lX11 -lm
	
	gcc -Wall -g  xnoisesph.c  -L/usr/lib/i386-linux-gnu -lX11 -o xnoisesph

  Usage: xnoisesph file
  Or:	 xnoisesph <file

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

/* Xlib variables */
Window w;
Display *d;
GC gc;

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
void Plot(Cartesian *C)
{
	XDrawPoint(d, w, gc, MidA + Round(Scale * C->y), MidY - Round(Scale * C->z));
	XDrawPoint(d, w, gc, MidB + Round(Scale * C->x), MidY - Round(Scale * C->y));
	XDrawPoint(d, w, gc, MidC + Round(Scale * C->z), MidY - Round(Scale * C->x));
}

/* Converts 3-d polar coordinates to cartesian coordinates */
void PolarToCartesian(Polar *P, Cartesian *C)
{
	/* No rotation was added. Instead we plot from three angles... */
	C->x = P->r * sin(P->phi) * cos(P->theta);
	C->y = P->r * sin(P->phi) * sin(P->theta);
	C->z = P->r * cos(P->phi);

	/* We can assign colors based
	  on x, y, z,
	  or r, theta / pi
	  or phi / (2 * pi) */
	C->Color = ScaleColor(C->y);
}

/* main function */
void main(int ac, char **av)
{
	char *fname;
	FILE *inp;
	XEvent event;
	XExposeEvent *ee = (XExposeEvent *)&event;
	int width, height, bwidth, depth, wx, wy;
	Window root;
	char *pgm;

	/* check parameters and input file */
	pgm = basename(*av);
	if (ac > 2) {
		fprintf(stderr, "Usage: %s [file]\n", pgm);
		exit(1);
	}

	if (ac == 2) {
		fname = av[1];
		if ((inp = fopen(fname, "rb")) == NULL) {
			fprintf(stderr, "%s: Can't open %s - %s\n", pgm, av[1], strerror(errno));
			exit(1);
		}
	}
	else {
		inp = stdin;
		fname = "(stdin)";
	}

	/* initialize display */
	if (!(d = XOpenDisplay(NULL)))
	{
		fprintf(stderr, "%s: Can't open display\n", pgm);
		exit(1);
	}

	w = XCreateSimpleWindow(d,
		RootWindow(d, DefaultScreen(d)),
		0, 0, 640, 480, 0,
		BlackPixel(d, DefaultScreen(d)),
		BlackPixel(d, DefaultScreen(d)));

	XSelectInput(d, w, ExposureMask);

	gc = XCreateGC(d, w, 0L, NULL);
	XSetBackground(d, gc, BlackPixel(d, DefaultScreen(d)));
	XSetForeground(d, gc, WhitePixel(d, DefaultScreen(d)));

	XMapRaised(d, w);

	while (XNextEvent(d, &event), event.type != Expose)
		;

	/* * Get the window's actual width and height. */
	XGetGeometry(d, w, &root, &wx, &wy, &width, &height, &bwidth, &depth);

	/* * Initialization done, window on screen; time for real work. */
	{
		double X[3];
		int i, n = 0;
		int byte;
		Cartesian C;
		Polar P;

		Scale = width / 6;
		MidA = Scale;
		MidB = 3 * Scale;
		MidC = 5 * Scale;
		MidY = height / 2;
		if (MidY < Scale)
			Scale = MidY;

		/* read the first 3 points from input file */
		for (i = 0; i < 3; i++) {
			if ((byte = getc(inp)) == EOF) {
				fprintf(stderr, "%s: Early EOF on %s\n", pgm, fname);
				exit(1);
			}
			X[i] = ByteToReal((unsigned char) byte);
		}

		/* read the remaining points from input file */
		while (1) {
			/* get the next point */
			P.r = sqrt(X[(n + 2) % 3]); /* pt 2 */
			P.theta = MATH_PI * X[(n + 1) % 3]; /* pt 1 */
			P.phi = 2 * MATH_PI * X[n]; /* pt 0 */

			PolarToCartesian(&P, &C);
			Plot(&C);

			if ((byte = getc(inp)) == EOF)
				break;

			X[n] = ByteToReal((unsigned char) byte);
			n = (n + 1) % 3;
		}
	}

	/* * Now hang out.  Let the window manager kill us. */
	while (1)
		XNextEvent(d, &event);

	exit(0);
}
