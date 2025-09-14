// file_operations.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "file_operations.h"

int create_and_write_file(const char *filename, const char *content) {
    // Declared integer fd
    int fd;
    // Declared variable bytes_written
    ssize_t bytes_written;

    // Prints which file is being created
    printf("Creating file: %s\n", filename);
    // Prints what content
    printf("Content to write: %s\n", content);

    // Opens file, uses flags and permissions, prints error if needed
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    // Prints file descriptor value.
    printf("File descriptor: %d\n", fd);

    // Writes content to the file, uses content length as the size, prints error if needed
    bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return -1;
    }

    // Prints success message
    printf("Successfully wrote %zd bytes to '%s'\n", bytes_written, filename);

    // Closes the file, prints error if needed
    if (close(fd) == -1) {
        perror("close");
        return -1;
    }

    // Prints the file was closed
    printf("File closed successfully\n");
    return 0;
}

int read_file_contents(const char *filename) {
    // Declares integer fd
    int fd;
    // Declares buffer array
    char buffer[1024];
    // Declares variable bytes_read
    ssize_t bytes_read;

    // Prints which file is being read
    printf("Reading file: %s\n", filename);

    // Opens the file, uses O_RDONLY flag, prints error if needed
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    // Prints descriptor value.
    printf("File descriptor: %d\n", fd);
    // Prints header
    printf("\n--- Contents of '%s' ---\n", filename);

    // Reads the file contents, null terminates buffer after reads, prints the contents, continues until 0
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    // prints error and returns -1 if needed
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return -1;
    }

    // prints footer
    printf("\n--- End of file ---\n");

    // closes the file, prints error if needed
    if (close(fd) == -1) {
        perror("close");
        return -1;
    }

    // Prints file closed
    printf("File closed successfully\n");
    return 0;
}

