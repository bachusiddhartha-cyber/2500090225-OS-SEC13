#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main()
{
    int source, destination;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    char sourceFile[100], destinationFile[100];

    printf("Enter source file name: ");
    scanf("%s", sourceFile);

    printf("Enter destination file name: ");
    scanf("%s", destinationFile);

    source = open(sourceFile, O_RDONLY);

    if (source < 0)
    {
        printf("Unable to open source file.\n");
        return 1;
    }

    destination = open(destinationFile,
                       O_WRONLY | O_CREAT | O_TRUNC,
                       0644);

    if (destination < 0)
    {
        printf("Unable to create destination file.\n");
        close(source);
        return 1;
    }

    while ((bytesRead = read(source, buffer, BUFFER_SIZE)) > 0)
    {
        write(destination, buffer, bytesRead);
    }

    close(source);
    close(destination);

    printf("File copied successfully.\n");

    return 0;
}
