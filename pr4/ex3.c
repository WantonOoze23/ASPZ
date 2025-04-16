#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = malloc(0);
    if (ptr == NULL) {
        printf("NULL pointer returned\n");
    } else {
        printf("Non-NULL pointer returned\n");
        free(ptr);
    }
    return 0;
}
