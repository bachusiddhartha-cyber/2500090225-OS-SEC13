#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("\n===== Child Process =====\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());

        printf("Child is Running...\n");
        sleep(5);

        printf("Child Process Finished.\n");
    }
    else
    {
        printf("\n===== Parent Process =====\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);

        printf("Parent is Waiting...\n");
        wait(NULL);

        printf("Child Terminated.\n");
        printf("Parent Process Finished.\n");
    }

    return 0;
}
