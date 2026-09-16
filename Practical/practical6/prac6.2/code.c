#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        printf("\nSIGINT received! Ctrl+C was pressed.\n");
    }
    else if (sig == SIGTERM)
    {
        printf("\nSIGTERM received! Terminating process...\n");
        exit(0);
    }
    else if (sig == SIGUSR1)
    {
        printf("\nSIGUSR1 received! User-defined signal handled.\n");
    }
}

int main(void)
{
    // Register signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGUSR1, signal_handler);

    printf("Process started.\n");
    printf("Process ID (PID): %d\n", getpid());
    printf("Waiting for signals...\n");

    while (1)
    {
        printf("Process is running...\n");
        sleep(3);
    }

    return 0;
}
