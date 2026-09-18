#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_var = 10;
static int static_var = 20;

void code_function()
{
    printf("Code segment address     : %p\n", (void *)code_function);
}

int main()
{
    int stack_var = 30;
    static int local_static = 40;

    int *heap_var = malloc(sizeof(int));

    if (heap_var == NULL)
    {
        perror("malloc");
        return 1;
    }

    *heap_var = 50;

    printf("========================================\n");
    printf("   LINUX PROCESS MEMORY LAYOUT\n");
    printf("========================================\n");

    printf("Process PID              : %d\n\n", getpid());

    printf("Code segment address     : %p\n",
           (void *)code_function);

    printf("Global variable address  : %p\n",
           (void *)&global_var);

    printf("Static variable address  : %p\n",
           (void *)&static_var);

    printf("Local static address     : %p\n",
           (void *)&local_static);

    printf("Heap variable address    : %p\n",
           (void *)heap_var);

    printf("Stack variable address   : %p\n",
           (void *)&stack_var);

    printf("\n========================================\n");
    printf("PID: %d\n", getpid());
    printf("Keep this program running...\n");
    printf("Open another terminal and check:\n");
    printf("/proc/%d/maps\n", getpid());
    printf("========================================\n");

    /*
     * Keep process alive so that /proc/PID/maps
     * can be inspected from another terminal.
     */

    while (1)
    {
        sleep(1);
    }

    free(heap_var);

    return 0;
}
