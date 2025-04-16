#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int a;
    int b;
};

int main() {
    struct sbar *ptr, *newptr;
    ptr = calloc(1000, sizeof(struct sbar));
    if (ptr == NULL) {
        printf("Initial allocation failed\n");
        return 1;
    }

    newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (newptr == NULL) {
        printf("Reallocation failed\n");
        free(ptr);
        return 1;
    }

    printf("Memory reallocated successfully\n");
    free(newptr);
    return 0;
}