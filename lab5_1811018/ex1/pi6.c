#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long nThreads;
pthread_t tid[20];
static volatile long count = 0;
pthread_mutex_t lock;
void *letCount(void *param);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Please enter nPoints!\n");
        return -1;
    }
    
    double nPoints = atoll(argv[1]); 
    if (nPoints <= 0)
    {
        printf("nPoints must be greater than 0\n");
        return -1;
    }

    pthread_mutex_init(&lock, NULL);
    srand(time(NULL));
    nThreads = nPoints / 20;
    for (int i = 0; i < 20; ++i)
        pthread_create(&tid[i], NULL, letCount, NULL);

    for (int i = 0; i < 20; ++i)
        pthread_join(tid[i], NULL);

    // Deal with the remaining cases
    if ((int)nPoints % 20 > 0)
        for (int i = 0; i < ((int)nPoints % 20); i++)
        {
            double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
            double y = (double)rand() / RAND_MAX * 2.0 - 1.0;
            if (x * x + y * y <= 1.0)
                count++;
        }

    printf("%5lf\n", 4.0 * count / nPoints);
    return 0;
}

void *letCount(void *param)
{
    for (int i = 0; i < nThreads; i++)
    {
        pthread_mutex_lock(&lock);
        double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand() / RAND_MAX * 2.0 - 1.0;
        if (x * x + y * y <= 1.0)
            count += 1;
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(0);
}