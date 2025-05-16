#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    struct stat st;
    char answer[16];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (stat(entry->d_name, &st) == 0 && S_ISREG(st.st_mode)) {
            printf("Delete file %s? (y/n): ", entry->d_name);
            if (fgets(answer, sizeof(answer), stdin)) {
                if (answer[0] == 'y' || answer[0] == 'Y') {
                    if (remove(entry->d_name) == 0) {
                        printf("File %s deleted.\n", entry->d_name);
                    } else {
                        perror("remove");
                    }
                }
            }
        }
    }
    closedir(dir);
    return 0;
}