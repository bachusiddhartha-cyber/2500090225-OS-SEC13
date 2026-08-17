#include <stdio.h>
#include <string.h>

#define MAX_INPUT 100

int main() {
    char input[MAX_INPUT];
    int running = 1;

    printf("=== Interactive Command Program ===\n");
    printf("Type 'help' for commands.\n");
    printf("Type 'exit' to quit.\n\n");

    while (running) {

        // Display prompt
        printf(">> ");

        // Read user input
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            break;
        }

        // Remove newline added by fgets
        input[strcspn(input, "\n")] = '\0';

        // Check for empty input
        if (strlen(input) == 0) {
            printf("Please enter a command.\n");
            continue;
        }

        // Handle commands
        if (strcmp(input, "exit") == 0) {
            printf("Exiting program...\n");
            running = 0;
        }

        else if (strcmp(input, "help") == 0) {
            printf("\nAvailable commands:\n");
            printf("help  - Display available commands\n");
            printf("hello - Display greeting\n");
            printf("clear - Clear screen\n");
            printf("exit  - Exit program\n\n");
        }

        else if (strcmp(input, "hello") == 0) {
            printf("Hello! Welcome to the interactive program.\n");
        }

        else if (strcmp(input, "clear") == 0) {
            printf("\033[2J\033[H");
        }

        else {
            printf("Unknown command: %s\n", input);
        }
    }

    return 0;
}
