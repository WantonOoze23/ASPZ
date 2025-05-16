#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[] = "Hello, World!";
    ssize_t nbytes = strlen(buffer);
    ssize_t count = write(fd, buffer, nbytes);

    if (count == -1) {
        perror("write");
    } else {
        printf("Requested %ld bytes, wrote %ld bytes\n", nbytes, count);
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    char large_buffer[100000];
    nbytes = sizeof(large_buffer);
    count = write(pipefd[1], large_buffer, nbytes);

    if (count == -1) {
        perror("write to pipe");
    } else {
        printf("Requested %ld bytes, wrote %ld bytes to pipe\n", nbytes, count);
    }

    close(fd);
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}