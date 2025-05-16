#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int count = 10;
    double n = 1.0; 

    if (argc > 1) {
        n = atof(argv[1]);
        if (n <= 0.0) n = 1.0;
    }
    if (argc > 2) {
        count = atoi(argv[2]);
        if (count <= 0) count = 10;
    }

    srand((unsigned int)(time(NULL) ^ (uintptr_t)&n));

    printf("Random numbers in the range [0.0; %.3f]:\n", n);
    for (int i = 0; i < count; i++) {
        double r = ((double)rand() / RAND_MAX) * n;
        printf("%.6f\n", r);
    }

    return 0;
}