#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char line[1024];

    fp = popen("sudo cat /etc", "r");
    if (fp == NULL) {
        perror("Failed to execute sudo cat /etc/shadow");
        return 1;
    }

    printf("/etc/shadow:\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    pclose(fp);
    return 0;
}