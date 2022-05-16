#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int is = 0;
    #pragma omp parallel for reduction(+:is)
    for (int j=1; j<=1000; j++)
        is += j;

    printf("%d\n", is);
}
