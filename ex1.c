// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>

// int part = 0;
// long count[3] = {0};
// void *letCount(void *param);

// int main(int argc, char *argv[])
// {
//     pthread_t tid[3];

//     for (int i = 0; i < 4; i++)
//     {
//         pthread_create(&tid[i], NULL, letCount, atoi(argv[1]) / 4);
//     }
//     for (int i = 0; i < 4; i++)
//     {
//         pthread_join(tid[i], NULL);
//     }
//     int total = 0;
//     for (int i = 0; i < 4; i++)
//     {
//         total += count[i];
//     }
//     printf("%d\n", 4 * total / (atoi(argv[1])));
//     return 0;
// }

// void *letCount(void *param)
// {
//     int k = part++;
//     srand(time);
//     int n = atoi(param);
//     for (int i = 0; i < n; i++)
//     {
//         double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
//         double y = (double)rand() / RAND_MAX * 2.0 - 1.0;
//         if ((double)sqrt(pow(x, 2) + pow(y, 2)) <= 1.0)
//             count[k]++;
//     }
//     pthread_exit(0);
// }
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <assert.h>
#include <stdio.h>

#define NUM_THREAD 8

void* calPI(void *param);

pthread_t tID[NUM_THREAD] = {0}; // Thread IDs
uint64_t  count[NUM_THREAD] = {0}; // Points count
uint64_t  sumPoint = 0, range, totalPoint;      // Shared data

int main(int argc, char const *argv[])
{
    if(argc > 2)  {
        printf("The Number Of Arguments Is Wrong");
    } 
    if(atoll(argv[1]) < 0) printf("Argument must be >= 0");

    // Set test range
    totalPoint = atoll(argv[1]);
    range = totalPoint/NUM_THREAD;
    srand(time(NULL));

    for(uint8_t i = 0; i< NUM_THREAD; i++) {
        pthread_create(&tID[i], NULL, calPI, &count[i]);
    }

    for(uint8_t i = 0; i < NUM_THREAD; i++) {
        pthread_join(tID[i], NULL);
        sumPoint += count[i];
    }

    for(uint64_t i = 0; i < totalPoint % NUM_THREAD; ++i) {
        double x = (double)rand()/(double)RAND_MAX*2 - 1;
        double y = (double)rand()/(double)RAND_MAX*2 - 1;
        double r = sqrt(x*x + y*y);
        if(r <= 1) sumPoint = sumPoint + 1;
    }


    double pi = 4.0*(double)sumPoint/totalPoint;
    printf("%.10lf\n", pi);  // Print PI Number
    
    pthread_exit(EXIT_SUCCESS);

}

void* calPI(void *param) {

    uint64_t* pcount = (uint64_t*)param;
    double x,y,r;

    for(uint64_t i = 0; i < range; ++i) {
        x = (double)rand()/(double)RAND_MAX*2 - 1;
        y = (double)rand()/(double)RAND_MAX*2 - 1;
        r = sqrt(x*x + y*y);
        if(r <= 1) *pcount = *pcount + 1;
    }

    pthread_exit(EXIT_SUCCESS);
}