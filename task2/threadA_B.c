#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* thread_A_Fun()
{
    for (int i = 1; i <= 1000; i++)
    {
        printf("thread A: %d\n", i);
        sleep(0.5);
    }
}

void* thread_B_Fun()
{
    for (int i = 1000; i >= 1; i--)
    {
        printf("thread B: %d\n", i);
        sleep(0.5);
    }
}

int main()
{
    pthread_t threadA;
    pthread_t threadB;
    
    pthread_create(&threadA, NULL, thread_A_Fun, NULL);
    pthread_create(&threadB, NULL, thread_B_Fun, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    return 0;
}