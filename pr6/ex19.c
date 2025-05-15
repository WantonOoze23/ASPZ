#include <stdio.h>

char* get_buffer() {
    char buffer[16];
    sprintf(buffer, "Hello, world!");
    return buffer; 
}

int main() {
    char* ptr = get_buffer();
    printf("%s\n", ptr); 
    return 0;
}