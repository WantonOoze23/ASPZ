#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define FILE_PATH "testfile.txt"

int main() {
    int fd;
    char *buffer;
    ssize_t bytes_written;
    size_t total_written = 0;

    fd = open(FILE_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("malloc");
        close(fd);
        exit(EXIT_FAILURE);
    }
    memset(buffer, 'A', BUFFER_SIZE);

    printf("Starting to write to file...\n");

    while (1) {
        bytes_written = write(fd, buffer, BUFFER_SIZE);
        if (bytes_written == -1) {
            fprintf(stderr, "write() error: %s (errno=%d)\n", strerror(errno), errno);
            if (errno == ENOSPC) {
                printf("Disk space is full (ENOSPC).\n");
            }
            break;
        }

        total_written += bytes_written;
        printf("Written %zd bytes, total: %zu bytes\n", bytes_written, total_written);

        memset(buffer, 'B', BUFFER_SIZE); 
    }

    if (close(fd) == -1) {
        perror("close");
    }
    free(buffer);

    printf("Program finished.\n");
    return 0;
}