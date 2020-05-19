#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
    srand(time(NULL));
    printf("%lf\n",(double)sin(rand()));
    printf("%lf\n",(double)sin(rand()));
    printf("%lf\n",(double)sin(rand()));
    printf("%lf\n",(double)sin(rand()));

    return 0;
}