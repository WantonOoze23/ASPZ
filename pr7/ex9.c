#include <stdio.h>
#include <time.h>

int main(void) {
    clock_t start, end;
    double elapsed_ms;

    start = clock();

    volatile long sum = 0;
    for (long i = 0; i < 10000000; i++) {
        sum += i;
    }

    end = clock();

    elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Execution time: %.3f ms\n", elapsed_ms);

    return 0;
}