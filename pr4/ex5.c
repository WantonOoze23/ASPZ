#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = malloc(100);
    if (ptr == NULL) {
        printf("Initial allocation failed\n");
        return 1;
    }

    void *new_ptr = realloc(ptr, 10000000000); // Важко виділити таку пам'ять
    if (new_ptr == NULL) {
        printf("Memory allocation failed\n");
    } else {
        printf("Memory allocated successfully\n");
        free(new_ptr);
    }

    return 0;
}
