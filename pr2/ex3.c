#include <stdio.h>
#include <stdlib.h>

int global_init = 1;          
int global_uninit;            

void* heap_ptr;

int main() {
    int stack_var = 42;       
    static int static_var = 99; 
    char *heap_var = malloc(100); 
    heap_ptr = heap_var;

    printf("Stack variable address: %p\n", &stack_var);
    printf("Heap variable address: %p\n", heap_var);
    printf("Global initialized variable address (.data): %p\n", &global_init);
    printf("Global uninitialized variable address (.bss): %p\n", &global_uninit);
    printf("Static local variable address (.data): %p\n", &static_var);
    printf("Function (code/text) address: %p\n", &main);

    free(heap_var);
    return 0;
}
