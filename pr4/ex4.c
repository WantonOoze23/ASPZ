#include <stdio.h>
#include <stdlib.h>

void *ptr = NULL;
while (<some-condition-is-true>) {
    if (!ptr) {
        ptr = malloc(n);
        if (!ptr) {
            break;
        }
    }
    free(ptr);
    ptr = NULL; 
}
