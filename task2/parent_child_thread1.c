#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int main()
{
    pid_t fpid;
    fpid = fork();
    if (fpid < 0)
    {
        printf("error!\n");
        exit(0);
    }
    else if (fpid == 0)
    {
        for (int i = 1; i <= 50; i++)
        {
            printf("child thread ID: %d\n", getpid());
            sleep(1);
        }
        printf("end of child thread\n");
    }
    else
    {
        printf("parent thread ID: %d\n", getpid());
        sleep(10);
        printf("end of parent thread\n");
    }
    exit(1);
}