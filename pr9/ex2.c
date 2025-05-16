#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char line[1024];

    // Використовуємо sudo для отримання доступу до /etc/shadow
    fp = popen("sudo cat /etc/shadow", "r");
    if (fp == NULL) {
        perror("Не вдалося виконати sudo cat /etc/shadow");
        return 1;
    }

    printf("Вміст /etc/shadow:\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    pclose(fp);
    return 0;
}