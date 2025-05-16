#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    if (setuid(0) == -1) {
        perror("setuid");
        return 1;
    }
    printf("Executing command as root...\n");
    system("whoami"); 
    return 0;
}