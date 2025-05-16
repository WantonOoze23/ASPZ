#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if (fcntl(pipefd[1], F_SETFL, O_NONBLOCK) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }

    char buffer[128 * 1024];
    memset(buffer, 'A', sizeof(buffer));

    close(pipefd[0]);

    ssize_t count = write(pipefd[1], buffer, sizeof(buffer));
    if (count == -1) {
        perror("write");
    } else if (count < sizeof(buffer)) {
        printf("Requested to write %zu bytes, actually wrote only %zd bytes\n", sizeof(buffer), count);
    } else {
        printf("Requested to write %zu bytes, wrote all %zd bytes\n", sizeof(buffer), count);
    }

    close(pipefd[1]);
    return 0;
}
