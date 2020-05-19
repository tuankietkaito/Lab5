#include <pthread.h>
#include <stdio.h>
#include <math.h>

int count;
void *letCount(void *param);

int main(int argc, char *argv[])
{
    pthread_t tid[3];
    
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&tid[i], NULL, letCount, atoi(argv[1]) / 4);
    }
    for (int i = 0; i < 4; i++)
    {
        pthread_join(tid[i], NULL);
    }
    printf("%d\n", count);
    return 0;
}

void *letCount(void *param)
{
    srand(time);
    int n = atoi(param);
    for (int i = 0; i < n; i++)
    {
        double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand() / RAND_MAX * 2.0 - 1.0;
        if ((double)sqrt(pow(x, 2) + pow(y, 2)) <= 1.0)
            count++;
    }
    pthread_exit(0);
}