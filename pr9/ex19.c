#include <unistd.h>
#include <stdio.h>

int main() {
    if (setuid(0) == -1) {
        perror("setuid");
        return 1;
    }
    printf("Виконую команду як root...\n");
    system("whoami"); // Виконує команду
    return 0;
}