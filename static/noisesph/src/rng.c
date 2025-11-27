#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void GenerateRandomNumbers(int maxPts) {
    int n;
    double x, xi;
    x = 0.1; /* seed */

    for (n=0; n<maxPts; n++) {
        x = 100 * log(x);
        xi = trunc(x);
        x = fabs(x-xi);
        printf("%.16f\n",x);
    }
}

int main(int argc, char* argv[])
{
    long n, num;
    double x, xi;
    x = 0.1;
    num = 100;

    if (argc > 1) {
        int input = atoi(argv[1]);
        /* printf("input %d",input); */
        num = input;
    }

    GenerateRandomNumbers(num);

    return 0;
}
