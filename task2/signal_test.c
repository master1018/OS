#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

#include<sys/types.h>

#define SIGNAL_DIE 16

void my_fun()
{
    printf("Byte, World!\n");
    kill(getpid(), SIGKILL);
}

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
        while (1)
        {
            signal(SIGNAL_DIE, my_fun);
            printf("I am Child Process, alive !\n");
            sleep(2);
        }
    }
    else
    {
        while (1)
        {
            printf("To terminate Child Process. Yes or No? \n");
            char opt = '0';
            opt = getchar();
            getchar();
            if (opt == 'N')
                sleep(2);
            else if (opt == 'Y')
            {
                kill(fpid, SIGNAL_DIE);
                sleep(2);
                break;
            }
        }
    }
    printf("parent over\n");
    return 0;
}