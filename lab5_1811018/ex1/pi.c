#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long nThreads;
pthread_t tid[20];
long count[20] = {0};
void *letCount(void *param);

int main(int argc, char *argv[])
{
    double nPoints = atoll(argv[1]);
    srand(time(NULL));
    nThreads = nPoints / 20;

    if (argc != 2)
    {
        printf("Please enter nPoints!\n");
        return -1;
    }

    if (nPoints <= 0)
    {
        printf("nPoints must be greater than 0\n");
        return -1;
    }

    for (int i = 0; i < 20; ++i)
        pthread_create(&tid[i], NULL, letCount, &count[i]);

    long total = 0;
    for (int i = 0; i < 20; ++i)
    {
        pthread_join(tid[i], NULL);
        total += count[i];
    }

    // Deal with the remaining cases
    if ((int)nPoints % 20 > 0)
        for (int i = 0; i < ((int)nPoints % 20); i++)
        {
            double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
            double y = (double)rand() / RAND_MAX * 2.0 - 1.0;
            if (x * x + y * y <= 1.0)
                total++;
        }

    printf("%5lf\n", 4.0 * total / nPoints);
    return 0;
}

void *letCount(void *param)
{
    long *n = (long *)param;
    for (int i = 0; i < nThreads; i++)
    {
        double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand() / RAND_MAX * 2.0 - 1.0;
        if (x * x + y * y <= 1.0)
            *n += 1;
    }
    pthread_exit(0);
}