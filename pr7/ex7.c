#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int is_executable(const struct stat *st) {
    // Файл є регулярним і має виконуваний біт для власника
    return S_ISREG(st->st_mode) && (st->st_mode & S_IXUSR);
}

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
        if (stat(entry->d_name, &st) == 0 && is_executable(&st)) {
            printf("Файл: %s\n", entry->d_name);
            printf("Надати дозвіл на читання для інших? (y/n): ");
            if (fgets(answer, sizeof(answer), stdin)) {
                if (answer[0] == 'y' || answer[0] == 'Y') {
                    mode_t new_mode = st.st_mode | S_IROTH;
                    if (chmod(entry->d_name, new_mode) == 0) {
                        printf("Дозвіл надано.\n");
                    } else {
                        perror("chmod");
                    }
                }
            }
        }
    }
    closedir(dir);
    return 0;
}