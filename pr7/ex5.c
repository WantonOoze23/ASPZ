#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_files(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror(path);
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Пропускаємо . і ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[4096];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == -1) {
            perror(fullpath);
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            // Рекурсивно обходимо підкаталог
            list_files(fullpath);
        } else if (S_ISREG(st.st_mode)) {
            printf("%s\n", fullpath);
        }
    }
    closedir(dir);
}

int main(void) {
    list_files(".");
    return 0;
}