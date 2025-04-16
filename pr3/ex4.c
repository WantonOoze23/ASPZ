#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_CPU_TIME 2  

void lottery_draw() {
    int numbers_1_49[49];
    int numbers_1_36[36];
    srand(time(NULL));

    for (int i = 0; i < 49; i++) {
        numbers_1_49[i] = i + 1;
    }

    for (int i = 0; i < 36; i++) {
        numbers_1_36[i] = i + 1;
    }

    for (int i = 0; i < 49; i++) {
        int j = rand() % 49;
        int temp = numbers_1_49[i];
        numbers_1_49[i] = numbers_1_49[j];
        numbers_1_49[j] = temp;
    }

    for (int i = 0; i < 36; i++) {
        int j = rand() % 36;
        int temp = numbers_1_36[i];
        numbers_1_36[i] = numbers_1_36[j];
        numbers_1_36[j] = temp;
    }

    printf("7 numbers from 1-49: ");
    for (int i = 0; i < 7; i++) {
        printf("%d ", numbers_1_49[i]);
    }

    printf("\n6 numbers from 1-36: ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", numbers_1_36[i]);
    }
    printf("\n");
}

int main() {
    time_t start_time = time(NULL);

    while (1) {
        if (difftime(time(NULL), start_time) >= MAX_CPU_TIME) {
            printf("CPU time limit exceeded\n");
            return 1;
        }
        lottery_draw();
        sleep(1);  
    }
    return 0;
}
