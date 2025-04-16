#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_CPU_TIME 5
#define MAX_MEMORY_USAGE 2000000000 

void cpu_load() {
    while (1) {
        volatile int x = rand(); // volatile, щоб запобігти оптимізації компілятором 
    }
}

void memory_load() {
    int *large_array = (int *)malloc(MAX_MEMORY_USAGE);
    if (large_array == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < MAX_MEMORY_USAGE / sizeof(int); i++) {
        large_array[i] = rand();
    }

    // Не звільняємо пам'ять для тестування ліміту пам'яті
    // free(large_array);
}

int main() {
    time_t start_time = time(NULL);

    if (fork() == 0) {
        cpu_load(); 
    }
    if (fork() == 0) {
        memory_load();  
    }

    while (1) {
        if (difftime(time(NULL), start_time) >= MAX_CPU_TIME) {
            printf("CPU time limit exceeded\n");
            exit(0);
        }

        sleep(1);
    }

    return 0;
}
