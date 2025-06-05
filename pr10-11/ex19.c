#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    int count = 0;

    while (1) {
        pid_t pid = fork();
        if (pid < 0) {
            // fork() повернув помилку
            perror("fork");
            break;
        }
        if (pid == 0) {
            // дитячий процес — виходить відразу
            exit(0);
        }
        count++;
    }

    printf("Створено процесів: %d\n", count);
    return 0;
}