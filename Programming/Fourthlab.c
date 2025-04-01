#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {

    if (argc < 3) {
        const char usage_msg[] = "Usage: ./program <filename> <text1> <text2> ...\n";
        write(STDERR_FILENO, usage_msg, sizeof(usage_msg) - 1);
        return 1;
    }


    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file for writing");
        return 1;
    }

    for (int i = 2; i < argc; i++) {
        if (write(fd, argv[i], strlen(argv[i])) == -1) {
            perror("Error writing to file");
            close(fd);
            return 1;
        }
        

        if (i < argc - 1 && write(fd, "\n", 1) == -1) {
            perror("Error writing newline");
            close(fd);
            return 1;
        }
    }


    if (close(fd) == -1) {
        perror("Error closing file after writing");
        return 1;
    }


    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    printf("File contents:\n");
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0'; 
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        return 1;
    }

    if (close(fd) == -1) {
        perror("Error closing file after reading");
        return 1;
    }

    return 0;
}