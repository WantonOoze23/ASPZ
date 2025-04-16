#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = -10000;
    int xb = 20000;
    size_t num = (size_t)(xa * xb); // Перемножуємо від'ємні та додатні числа
    
    printf("Result: %zu\n", num);
    void *ptr = malloc(num); // malloc з величезним значенням
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
    } else {
        printf("Memory allocated successfully\n");
        free(ptr);
    }
    return 0;
}
