/*

  NOISESPH.C, Plots a noise-sphere of the file.

  The original version of this program was written in Turbo Pascal by
  Rob Rothenburg Walking-Owl <WlkngOwl@unix.asb.com>. It was converted
  to Borland C++ by James Pate Williams, Jr. <pate@mindspring.com>,
  then (back) to vanilla C with added options by Rob Walking-Owl.

  This program is public domain.  No copyright is claimed.

  Usage: noisesph file [-3 -b|w -x n -y n -z n -m n -s n -c n]

  This program reads a file of random or pseudo-random data and plots
  a noise sphere of the data. Poor RNGs or sampling methods will show
  clear patterns (definite splotches or spirals).

  The theory behind this is to get a set of 3D polar coordinates from
  the RNG and plot them.  An array is kept of the values, which is
  rotated each time a new byte is read (see the code in the main
  procedure).

  Rather than plot one sphere which can be rotated around any axis,
  it was easier to plot the sphere from three different angles.

  This program is based on a description from the article below.  It
  was proposed as a means of testing pseudo-RNGs:

  Pickover, Clifford A. 1995. "Random number generators: pretty good
    ones are easy to find."  The Visual Computer (1005) 11:369-377.

  See also Pickover, nd., "Keys to Infinity." Chapter 31.


  gcc noisesph.c -o noisesph -lgraph -lm

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159267
#endif

//#define STAT

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

struct Cartesian C;
struct Polar P;


/* Initialize the graphics screen (Borland C specific)  and sets the
   midpoints and scale for the screen */
int InitScreen(void)
{
    int GraphMode, GraphDriver;
    GraphDriver = VGA;
    GraphMode = VGAHI;
    detectgraph(&GraphDriver, &GraphMode);
    initgraph(&GraphDriver, &GraphMode, "");
    return 1 ; // graphresult();
}

void InitPoints(void)
{
    Scale = getmaxx() / 2;
    MidA = Scale;
    MidY = getmaxy() / 2;

    if (MidY < Scale)
        Scale = MidY;

    Scale = 150;
}

/* Convert degrees to radians */
#define rads(x) (((double)(x * 2)) * M_PI / 360.0)

/* This could be rewritten to scale a number between -1.0 and 1.0 to
   a grayscale or RBG map, depending on the system one is plotting on.
   (Perhaps setting RGB values based on X, Y and Z independently?) */

// #define ScaleColor(x) (defcolor)
unsigned ScaleColor()
{

    /* random int between 0 and 19 */
    unsigned r = rand() % 20;

    return r;
}
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
        C->x = x;
        C->y = y;
    }
    if (RX)
    {
        x = rads(RX);
        y = (C->y * cos(x)) + (C->z * sin(x));
        z = (C->z * cos(x)) - (C->y * sin(x));
        C->z = z;
        C->y = y;
    }
    if (RY)
    {
        y = rads(RY);
        x = (C->x * cos(y)) + (C->z * sin(y));
        z = (C->z * cos(y)) - (C->x * sin(y));
        C->z = z;
        C->x = x;
    }
}

#define project(x) (ceil(Scale * x))

/* Projects 3d coordinates to a 2d screen */
void Plot(struct Cartesian C)
{
    rotate(&C);

    // putpixel(MidA + project(C.x), MidY - project(C.y), C.Color);

    int x1, y1, x2, y2;
    x1 = MidA + project(C.x);
    y1 = MidY - project(C.y);
    x2 = x1 + 2;
    y2 = y1 + 2;

    setcolor(C.Color);
    setlinestyle(0, 1, 1);

    rectangle(x1, y1, x2, y2);

//    if (triple)
//    {
//        putpixel(MidB + project(C.y), MidY - project(C.z), C.Color);
//        putpixel(MidC + project(C.z), (3 * MidY) - project(C.x), C.Color);
//    }
}

/* Converts 3-d polar coordinates to cartesian coordinates */
void PolarToCartesian(struct Polar P, struct Cartesian *C)
{
    C->x = P.r * sin(P.phi) * cos(P.theta);
    C->y = P.r * sin(P.phi) * sin(P.theta);
    C->z = P.r * cos(P.phi);
    /* We can assign colors based on C.x, C.y, C.z,
       or P.r, P.theta / pi or P.phi / (2 * pi) */
    C->Color = ScaleColor(C->z);
}

int plot_file(char* name)
{
    FILE *inpu;
    int i;
    int n = 0;
    double myVar;

    InitPoints();

    if (!(inpu = fopen(name, "r")))
    {
        if (!ScreenInit) closegraph();     /* shut down graphics system */
        fprintf(stderr, "Cannot open file %s\n", name);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 3; i++)
    {
        fscanf(inpu, "%lf", &myVar);
        X[i] = myVar;
        // printf("read: %f\n", X[i]);
    }
    while (!feof(inpu))
    {
        #ifdef STAT
        printf("x0: %f x1: %f x2: %f \n", X[0], X[1], X[2]);
        #endif // STAT

        P.r = sqrt(X[(n + 2) % 3]);
        P.theta = M_PI * X[(n + 1) % 3];
        P.phi = 2 * M_PI * X[n];

        #ifdef STAT
        printf("P.r: %f P.t: %f P.p: %f \n", P.r, P.theta, P.phi);
        #endif // STAT

        PolarToCartesian(P, &C);

        #ifdef STAT
        printf("C.r: %f C.y.: %f C.z: %f C.Color: %d \n", C.x, C.y, C.z, C.Color);
        #endif // STAT

        Plot(C);

        // read next point
        fscanf(inpu, "%lf", &myVar);
        X[n] = myVar;
        #ifdef STAT
        printf("read: %f\n", X[n]);
        #endif // STAT

        n = (n + 1) % 3;
        //n = ++n % 3;
    }
    fclose(inpu);
    return(1);
}

void usage(void)
{
    if (!ScreenInit) closegraph();     /* shut down graphics system */
    fprintf(stderr, "usage: noisesph [-3 -b|w -x n -y n -z n -m n -s n] file [[opts] file...]\n" \
            "Plots a noise sphere based on the data in file.\n" \
            "-3\tplot projections along (x,y), (z,y) and (x,z) planes\n" \
            "-b\tfile contains 8-bit samples (default)\n" \
            "-w\tfile contains 16-bit samples\n" \
            "-x n\trotate around x-axis n degrees\n" \
            "-y n\trotate around y-axis n degrees\n" \
            "-z n\trotate around z-axis n degrees\n" \
            "-m n\tplot only the first n samples in file\n" \
            "-s n\tplot only every nth point\n" \
            "-c n\tplot in color n (system specific)\n" \
            "-l n\tlag = n (discard every nth sample)\n" \
           );
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    int i;

    if (argc < 2)
    {
        usage();
    }
    if (ScreenInit)
    {
        error = InitScreen();
        if (error != 1)
        {
            // fprintf(stderr, "%s\n", grapherrormsg(error));
            exit(EXIT_FAILURE);
        }
        ScreenInit = 0;
    }
    if (argc > 1)
    {
        for (i = 1; ((i<argc)); i++)
        {
            if (argv[i][0] != '-') plot_file(argv[i]);
            else if (strcmp(argv[i], "-x") == 0) RX = atoi(argv[++i]);
            else if (strcmp(argv[i], "-y") == 0) RY = atoi(argv[++i]);
            else if (strcmp(argv[i], "-z") == 0) RZ = atoi(argv[++i]);
            else if (strcmp(argv[i], "-c") == 0) defcolor = atol(argv[++i]);
            else
            {
                if (!ScreenInit)
                {
                    closegraph();
                    ScreenInit = 1;
                }
                printf("Unrecognized option: %s\n", argv[i]);
                usage();
            }
        }
    }
    // getch();  /* gets a char from the keyboard without echoing */
    getchar();
    closegraph();     /* shut down graphics system */

    exit(EXIT_SUCCESS);
}
