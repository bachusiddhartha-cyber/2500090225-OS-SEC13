#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    char command[100];
    pid_t pid;

    printf("Enter a Linux command: ");
    scanf("%s", command);

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("\nChild Process\n");
        printf("Child PID : %d\n", getpid());

        execlp(command, command, NULL);

        printf("Command execution failed!\n");
    }
    else
    {
        printf("\nParent Process\n");
        printf("Parent PID : %d\n", getpid());

        wait(NULL);

        printf("Child process completed.\n");
    }

    return 0;
}dont message anything
