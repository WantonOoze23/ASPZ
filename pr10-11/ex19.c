#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("dumbsh> ");
    int count = 0;
    while (1) {
        pid_t pid = fork();
        if (pid < 0) {
            // fork() не вдалось
            break;
        }
        if (pid == 0) {
            // Дочірній процес виходить, щоб не створювати нові процеси
            _exit(0);
        }
        count++;
    }
    printf("Вдалося створити %d процесів\n", count);
    return 0;
}