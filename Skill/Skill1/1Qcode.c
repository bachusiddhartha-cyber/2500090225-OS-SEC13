#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        // Child Process
        printf("Child Process\n");
        printf("Child PID: %d\n", getpid());

        // Replace child process with 'ls -l'
        execl("/bin/ls", "ls", "-l", NULL);

        // Executes only if execl() fails
        perror("execl failed");
    }
    else {
        // Parent Process
        printf("Parent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        wait(NULL);

        printf("Child process completed.\n");
    }

    return 0;
}
