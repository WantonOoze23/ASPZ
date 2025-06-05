#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t got_sigusr2 = 0;
volatile sig_atomic_t got_sigusr1 = 0;

void sigusr1_handler(int sig) {
    got_sigusr1 = 1;
}

void sigusr2_handler(int sig) {
    got_sigusr2 = 1;
}

int main() {
    pid_t child = fork();

    if (child == 0) {
        // Дочірній процес
        signal(SIGUSR1, sigusr1_handler);
        while (!got_sigusr1) pause();
        printf("Child: отримав SIGUSR1\n");
        kill(getppid(), SIGUSR2);
        exit(0);
    } else {
        // Батьківський процес
        signal(SIGUSR2, sigusr2_handler);
        sleep(1); // Таймаут
        kill(child, SIGUSR1);
        while (!got_sigusr2) pause();
        printf("Parent: отримав SIGUSR2\n");
        wait(NULL);
    }
    return 0;
}