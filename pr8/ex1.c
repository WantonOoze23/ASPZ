#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {
    int pipefd[2];
    char buffer[4096];
    memset(buffer, 'A', sizeof(buffer));

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);

    ssize_t count = write(pipefd[1], buffer, sizeof(buffer));
    if (count < 0) {
        perror("write");
    } else {
        printf("write() записав %zd байт із %zu\n", count, sizeof(buffer));
    }

    close(pipefd[1]);
    return 0;
}
