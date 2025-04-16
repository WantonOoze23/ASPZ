#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    ptr = realloc(ptr, 0); 
    if (ptr == NULL) {
        printf("Memory freed\n");
    }

    ptr = realloc(NULL, 100); 
    if (ptr != NULL) {
        printf("Memory allocated\n");
        free(ptr);
    }
    return 0;
}
