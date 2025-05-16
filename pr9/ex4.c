#include <stdio.h>
#include <stdlib.h>

int main() {
    char line[256];
    FILE *fp;

    printf("Result of whoami:\n");
    fp = popen("whoami", "r");
    if (fp == NULL) {
        perror("Failed to execute whoami");
        return 1;
    }
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    pclose(fp);

    printf("\nResult of id:\n");
    fp = popen("id", "r");
    if (fp == NULL) {
        perror("Failed to execute id");
        return 1;
    }
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    pclose(fp);

    return 0;
}