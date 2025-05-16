#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *rwho = popen("rwho", "r");
    if (!rwho) {
        perror("popen rwho");
        return 1;
    }

    FILE *more = popen("more", "w");
    if (!more) {
        perror("popen more");
        pclose(rwho);
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), rwho)) {
        fputs(buffer, more);
    }

    pclose(rwho);
    pclose(more);

    return 0;
}
