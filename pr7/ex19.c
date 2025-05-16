#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>

#define MAX_FILES 4096
#define MAX_PIDS  128

typedef struct {
    char filename[PATH_MAX];
    pid_t pids[MAX_PIDS];
    int pid_count;
} FileUsage;

FileUsage files[MAX_FILES];
int file_count = 0;

int find_file(const char *filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].filename, filename) == 0)
            return i;
    }
    return -1;
}

void add_usage(const char *filename, pid_t pid) {
    int idx = find_file(filename);
    if (idx == -1) {
        if (file_count >= MAX_FILES) return;
        strncpy(files[file_count].filename, filename, PATH_MAX-1);
        files[file_count].filename[PATH_MAX-1] = '\0';
        files[file_count].pids[0] = pid;
        files[file_count].pid_count = 1;
        file_count++;
    } else {
        for (int i = 0; i < files[idx].pid_count; i++)
            if (files[idx].pids[i] == pid) return;
        if (files[idx].pid_count < MAX_PIDS)
            files[idx].pids[files[idx].pid_count++] = pid;
    }
}

int main(void) {
    DIR *proc = opendir("/proc");
    if (!proc) {
        perror("opendir /proc");
        return 1;
    }
    struct dirent *dent;
    while ((dent = readdir(proc)) != NULL) {
        if (dent->d_type != DT_DIR) continue;
        pid_t pid = atoi(dent->d_name);
        if (pid <= 0) continue;

        char fd_dir[PATH_MAX];
        snprintf(fd_dir, sizeof(fd_dir), "/proc/%d/fd", pid);
        DIR *fd = opendir(fd_dir);
        if (!fd) continue;

        struct dirent *fdent;
        while ((fdent = readdir(fd)) != NULL) {
            if (strcmp(fdent->d_name, ".") == 0 || strcmp(fdent->d_name, "..") == 0)
                continue;
            char link_path[PATH_MAX], file_path[PATH_MAX];
            snprintf(link_path, sizeof(link_path), "%s/%s", fd_dir, fdent->d_name);
            ssize_t len = readlink(link_path, file_path, sizeof(file_path)-1);
            if (len > 0) {
                file_path[len] = '\0';

                if (strncmp(file_path, "/", 1) == 0)
                    add_usage(file_path, pid);
            }
        }
        closedir(fd);
    }
    closedir(proc);

    printf("Files opened by multiple processes:\n");
    for (int i = 0; i < file_count; i++) {
        if (files[i].pid_count > 1) {
            printf("%s :", files[i].filename);
            for (int j = 0; j < files[i].pid_count; j++)
                printf(" %d", files[i].pids[j]);
            printf("\n");
        }
    }
    return 0;
}