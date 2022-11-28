#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <wait.h>
#include <semaphore.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int buff[10] = {0};  // 10个元素得到缓冲区
sem_t sem;  // 信号量
sem_t space; // 缓冲区空间
int indexp = 0;
int indexc = 0;

void* producter(void* arg)
{
    while (1) 
    {
        sem_wait(&space); // 缓冲区有空间才能产生物品
        int val = *(int *)(arg);
        pthread_mutex_lock(&mutex);
        buff[indexp % 10] = rand() % 1000 + val; // [val, val + 1000)
        float sTime = (float)((rand() % 900 + 100) * 1.0) / 1000;
        printf("product %d in index %d, sleep %lf\n", buff[indexp % 10], indexp % 10, sTime);
        sleep(sTime); // [100, 1000) ms
        indexp++;
        pthread_mutex_unlock(&mutex);
        sem_post(&sem);  // 产品数+1
    }
}

void* consumer()
{
    while (1)
    {
        sem_wait(&sem);  // 有产品才开始消费
        pthread_mutex_lock(&mutex);
        float sTime = (float)((rand() % 900 + 100) * 1.0) / 1000;
        printf("consum %d in index %d, sleep %lf\n", buff[indexc % 10], indexc % 10, sTime);
        buff[indexc % 10] = 0; // 消费数据
        sleep(sTime);
        indexc++;
        pthread_mutex_unlock(&mutex);
        sem_post(&space); // 空间增大
    }
}

int main()
{
    sem_init(&sem, 0, 0);
    sem_init(&space, 0, 9);
    
    pthread_t producter_thread_1, producter_thread_2;
    pthread_t consumer_thread_1, consumer_thread_2, consumer_thread_3;

    int a = 1000;
    pthread_create(&consumer_thread_1, NULL, consumer, NULL);
    pthread_create(&consumer_thread_2, NULL, consumer, NULL);
    pthread_create(&consumer_thread_3, NULL, consumer, NULL);
    pthread_create(&producter_thread_1, NULL, producter, (void *)(&a));
    a = 2000;
    pthread_create(&producter_thread_2, NULL, producter, (void *)(&a));

    pthread_join(producter_thread_1,NULL);
	pthread_join(producter_thread_2,NULL);
	pthread_join(consumer_thread_1,NULL);
	pthread_join(consumer_thread_2,NULL);
	pthread_join(consumer_thread_3,NULL);
    
    return 0;
}