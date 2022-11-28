#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    pid_t fpid;
    fpid = fork();
    int status = -1;
    if (fpid < 0)
    {
        printf("error!\n");
        exit(0);
    }
    else if (fpid == 0)
    {
        for (int i = 1; i <= 5; i++)
        {
            printf("child thread ID: %d\n", getpid());
            sleep(1);
        }
        printf("end of child\n");
        exit(5);
    }
    else
    {
        printf("parent thread ID: %d\n", getpid());
        wait(&status);
    }
    printf("child thread exit return value: %d\n", WEXITSTATUS(status));
    printf("end of parent thread: %d\n", getpid());
    return 0;
}