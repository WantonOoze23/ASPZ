#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    printf("PID = %d\n", pid);

    return 0;
}