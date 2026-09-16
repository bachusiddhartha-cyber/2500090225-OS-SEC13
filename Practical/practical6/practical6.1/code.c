#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

/* ---------------------------------------------------
   SIGNAL DEMO
--------------------------------------------------- */

void signal_handler(int sig)
{
    printf("\nSignal received: %d\n", sig);
}

void signal_demo(void)
{
    printf("\n========================================\n");
    printf("             SIGNAL DEMO\n");
    printf("========================================\n");

    signal(SIGINT, signal_handler);

    printf("Signal handler installed.\n");
    printf("Press Ctrl+C to generate SIGINT.\n");
    printf("Press Ctrl+C again to terminate.\n\n");

    while (1)
    {
        pause();
    }
}

/* ---------------------------------------------------
   SERVER
--------------------------------------------------- */

void server(void)
{
    int server_fd;
    int response_fd;

    char message[100];
    char response[150];

    printf("\n========================================\n");
    printf("              FIFO SERVER\n");
    printf("========================================\n");

    /* Create FIFO files */
    if (mkfifo(FIFO1, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo FIFO1");
        exit(EXIT_FAILURE);
    }

    if (mkfifo(FIFO2, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo FIFO2");
        exit(EXIT_FAILURE);
    }

    printf("Server is waiting for client...\n\n");

    while (1)
    {
        /* Open FIFO1 for reading */
        server_fd = open(FIFO1, O_RDONLY);

        if (server_fd == -1)
        {
            perror("open FIFO1");
            exit(EXIT_FAILURE);
        }

        memset(message, 0, sizeof(message));

        ssize_t bytes_read = read(
            server_fd,
            message,
            sizeof(message) - 1
        );

        close(server_fd);

        if (bytes_read < 0)
        {
            perror("read FIFO1");
            continue;
        }

        message[bytes_read] = '\0';

        printf("Client message: %s", message);

        /* Check exit command */
        if (strcmp(message, "exit\n") == 0 ||
            strcmp(message, "exit") == 0)
        {
            printf("Client requested termination.\n");
            break;
        }

        /* Prepare response */
        snprintf(
            response,
            sizeof(response),
            "Server received: %s",
            message
        );

        /* Open FIFO2 for writing */
        response_fd = open(FIFO2, O_WRONLY);

        if (response_fd == -1)
        {
            perror("open FIFO2");
            exit(EXIT_FAILURE);
        }

        write(
            response_fd,
            response,
            strlen(response)
        );

        close(response_fd);
    }

    unlink(FIFO1);
    unlink(FIFO2);

    printf("Server terminated.\n");
}

/* ---------------------------------------------------
   CLIENT
--------------------------------------------------- */

void client(void)
{
    int client_fd;
    int response_fd;

    char message[100];
    char response[150];

    printf("\n========================================\n");
    printf("              FIFO CLIENT\n");
    printf("========================================\n");

    printf("Enter messages.\n");
    printf("Type 'exit' to stop.\n\n");

    while (1)
    {
        printf("Client: ");
        fflush(stdout);

        if (fgets(message, sizeof(message), stdin) == NULL)
        {
            printf("\nInput error.\n");
            break;
        }

        /* Open FIFO1 for writing */
        client_fd = open(FIFO1, O_WRONLY);

        if (client_fd == -1)
        {
            perror("open FIFO1");
            exit(EXIT_FAILURE);
        }

        if (write(client_fd, message, strlen(message)) == -1)
        {
            perror("write FIFO1");
            close(client_fd);
            continue;
        }

        close(client_fd);

        /* Check exit command */
        if (strcmp(message, "exit\n") == 0 ||
            strcmp(message, "exit") == 0)
        {
            break;
        }

        /* Open FIFO2 for reading */
        response_fd = open(FIFO2, O_RDONLY);

        if (response_fd == -1)
        {
            perror("open FIFO2");
            exit(EXIT_FAILURE);
        }

        memset(response, 0, sizeof(response));

        ssize_t bytes_read = read(
            response_fd,
            response,
            sizeof(response) - 1
        );

        close(response_fd);

        if (bytes_read < 0)
        {
            perror("read FIFO2");
            continue;
        }

        response[bytes_read] = '\0';

        printf("Server response: %s", response);
    }

    printf("Client terminated.\n");
}

/* ---------------------------------------------------
   MAIN
--------------------------------------------------- */

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage:\n");
        printf("  %s server\n", argv[0]);
        printf("  %s client\n", argv[0]);
        printf("  %s signal\n", argv[0]);

        return 1;
    }

    if (strcmp(argv[1], "server") == 0)
    {
        server();
    }
    else if (strcmp(argv[1], "client") == 0)
    {
        client();
    }
    else if (strcmp(argv[1], "signal") == 0)
    {
        signal_demo();
    }
    else
    {
        printf("Invalid option.\n");
        printf("Use: server, client, or signal\n");

        return 1;
    }

    return 0;
}
