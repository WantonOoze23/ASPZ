#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_DIRS 1024

int main(void) {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    char *dirs[MAX_DIRS];
    int count = 0;
    struct dirent *entry;
    struct stat st;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (stat(entry->d_name, &st) == 0 && S_ISDIR(st.st_mode)) {
            dirs[count] = strdup(entry->d_name);
            if (++count >= MAX_DIRS) break;
        }
    }
    closedir(dir);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(dirs[i], dirs[j]) > 0) {
                char *tmp = dirs[i];
                dirs[i] = dirs[j];
                dirs[j] = tmp;
            }
        }
    }
    
    printf("Sorted directories:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", dirs[i]);
        free(dirs[i]);
    }

    return 0;
}