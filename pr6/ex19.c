#include <stdio.h>

int *create_array() {
    int array[100]; 
    for (int i = 0; i < 100; i++) {
        array[i] = i;
    }
    return array; 
}

int main() {
    int *ptr = create_array();
    printf("Value: %d\n", ptr[42]); 
    return 0;
}