#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if (!f) {
            perror(argv[i]);
            continue;
        }

        char line[1024];
        int count = 0;
        while (fgets(line, sizeof(line), f)) {
            fputs(line, stdout);
            count++;
            if (count == 20) {
                printf("--More-- (Press Enter to continue)");
                getchar();
                count = 0;
            }
        }

        fclose(f);
    }
    return 0;
}

