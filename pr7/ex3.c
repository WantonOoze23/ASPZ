#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <word> <file>\n", argv[0]);
        return 1;
    }

    char *word = argv[1];
    FILE *f = fopen(argv[2], "r");
    if (!f) {
        perror("fopen");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, word) != NULL) {
            fputs(line, stdout);
        }
    }

    fclose(f);
    return 0;
}
