#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>

int main() {
    time_t max_time = (time_t)-1;
    printf("Максимальне значення time_t: %ld\n", (long)max_time);
    printf("Дата переповнення: %s", ctime(&max_time));

    printf("Розмір time_t: %zu байт\n", sizeof(time_t));

    if (sizeof(void*) == 4) {
        printf("Система 32-бітна.\n");
    } else if (sizeof(void*) == 8) {
        printf("Система 64-бітна.\n");
    } else {
        printf("Невідома архітектура.\n");
    }
    return 0;
}
