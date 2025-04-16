#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t size = 1024 * 1024 * 1024;
    void *ptr;

    while (1) {
        ptr = malloc(size);
        if (ptr == NULL) {
            perror("Memory allocation failed");
            break;
        } else {
            printf("Successfully allocated %zu bytes\n", size);
        }
    }

    return 0;
}
