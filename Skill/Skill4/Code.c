#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 50
#define MAX_LENGTH 100

struct Token {
    char value[MAX_LENGTH];
};

int main(void) {
    char input[MAX_LENGTH];
    struct Token tokens[MAX_TOKENS];
    int count = 0;

    printf("Enter a command: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    /* Remove newline character */
    input[strcspn(input, "\n")] = '\0';

    /* Split input using space and tab */
    char *token = strtok(input, " \t");

    while (token != NULL && count < MAX_TOKENS) {

        /* Copy token safely */
        strncpy(tokens[count].value, token, MAX_LENGTH - 1);
        tokens[count].value[MAX_LENGTH - 1] = '\0';

        count++;

        token = strtok(NULL, " \t");
    }

    /* Display tokens */
    printf("\nTokens:\n");

    for (int i = 0; i < count; i++) {
        printf("Token %d: %s\n", i + 1, tokens[i].value);
    }

    /* Validate token stream */
    if (count == 0) {
        printf("\nInvalid input: No tokens found.\n");
    } else {
        printf("\nToken stream is valid.\n");
    }

    /* Debug output */
    printf("\nDebug Parsing Output:\n");

    for (int i = 0; i < count; i++) {
        printf("[%d] -> %s\n", i, tokens[i].value);
    }

    return 0;
}
