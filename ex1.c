#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long range;
long count[8] = {0};
void *letCount(void *param);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t tid[8];
    range = atoll(argv[1]) / 8;

    if (argc != 2)
    {
        printf("The Number Of Arguments Is Wrong\n");
        return -1;
    }

    if (atoll(argv[1]) < 0)
    {
        printf("Argument must be >= 0\n");
        return -1;
    }

    for (int i = 0; i < 8; i++)
        pthread_create(&tid[i], NULL, letCount, &count[i]);

    for (int i = 0; i < 8; i++)
        pthread_join(tid[i], NULL);

    // Total number of inside-circle points
    int total = 0;
    for (int i = 0; i < 8; i++)
        total += count[i];

    // Random the remain cases
    if (atoll(argv[1]) % 8 > 0)
        for (int i = 0; i < atoll(argv[1]) % 8; i++)
        {
            double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
            double y = (double)rand() / RAND_MAX * 2.0 - 1.0;
            if (x * x + y * y <= 1.0)
                total++;
        }

    printf("%llu\n", 4 * total / (atoll(argv[1])));
    return 0;
}

void *letCount(void *param)
{
    unsigned long long *n = (unsigned long long *)param;
    for (int i = 0; i < range; i++)
    {
        double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand() / RAND_MAX * 2.0 - 1.0;
        if (x * x + y * y <= 1.0)
            *n += 1;
    }
    pthread_exit(0);
}