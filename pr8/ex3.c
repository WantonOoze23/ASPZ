#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void generate_sorted(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
}

void generate_reverse_sorted(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i - 1;
}

void generate_identical(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = 42;
}

void generate_random(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % n;
}

void test_qsort_performance(int n) {
    int *arr = malloc(n * sizeof(int));
    clock_t start, end;
    double time_spent;

    printf("Array size: %d\n", n);

    // Test 1: Sorted array
    generate_sorted(arr, n);
    start = clock();
    qsort(arr, n, sizeof(int), compare_int);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Sorted: %.6f sec\n", time_spent);

    // Test 2: Reverse sorted array
    generate_reverse_sorted(arr, n);
    start = clock();
    qsort(arr, n, sizeof(int), compare_int);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Reverse sorted: %.6f sec\n", time_spent);

    // Test 3: Identical elements
    generate_identical(arr, n);
    start = clock();
    qsort(arr, n, sizeof(int), compare_int);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Identical elements: %.6f sec\n", time_spent);

    // Test 4: Random array
    generate_random(arr, n);
    start = clock();
    qsort(arr, n, sizeof(int), compare_int);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Random: %.6f sec\n", time_spent);

    free(arr);
}

int is_sorted(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i-1]) return 0;
    }
    return 1;
}

void run_qsort_tests() {
    int n = 10000;
    int *arr = malloc(n * sizeof(int));

    printf("\nQsort correctness tests:\n");

    generate_sorted(arr, n);
    qsort(arr, n, sizeof(int), compare_int);
    printf("Sorted array: %s\n", is_sorted(arr, n) ? "OK" : "Error");

    generate_reverse_sorted(arr, n);
    qsort(arr, n, sizeof(int), compare_int);
    printf("Reverse sorted array: %s\n", is_sorted(arr, n) ? "OK" : "Error");

    generate_identical(arr, n);
    qsort(arr, n, sizeof(int), compare_int);
    printf("Identical elements: %s\n", is_sorted(arr, n) ? "OK" : "Error");

    generate_random(arr, n);
    qsort(arr, n, sizeof(int), compare_int);
    printf("Random array: %s\n", is_sorted(arr, n) ? "OK" : "Error");

    free(arr);
}

int main() {
    srand(time(NULL));

    printf("Qsort performance tests:\n");
    test_qsort_performance(10000);
    test_qsort_performance(100000);

    run_qsort_tests();

    return 0;
}