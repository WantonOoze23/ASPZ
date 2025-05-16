#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#define MAX_PIDS 128
#define MAX_ENTRIES 4096

typedef struct {
    ino_t inode;
    char filepath[PATH_MAX];
    pid_t pids[MAX_PIDS];
    int pid_count;
} FileEntry;

FileEntry file_entries[MAX_ENTRIES];
int entry_count = 0;

int is_number(const char *s) {
    while (*s) {
        if (!isdigit(*s++)) return 0;
    }
    return 1;
}

int find_or_create_entry(ino_t inode, const char *filepath) {
    for (int i = 0; i < entry_count; ++i) {
        if (file_entries[i].inode == inode &&
            strcmp(file_entries[i].filepath, filepath) == 0) {
            return i;
        }
    }
    if (entry_count >= MAX_ENTRIES) {
        fprintf(stderr, "Too many unique files\n");
        exit(1);
    }
    file_entries[entry_count].inode = inode;
    strncpy(file_entries[entry_count].filepath, filepath, PATH_MAX);
    file_entries[entry_count].pid_count = 0;
    return entry_count++;
}

void scan_proc() {
    DIR *proc = opendir("/proc");
    if (!proc) {
        perror("opendir /proc");
        exit(1);
    }

    struct dirent *entry;
    while ((entry = readdir(proc)) != NULL) {
        if (!is_number(entry->d_name)) continue;
        pid_t pid = atoi(entry->d_name);

        char fd_path[64];
        snprintf(fd_path, sizeof(fd_path), "/proc/%d/fd", pid);
        DIR *fd_dir = opendir(fd_path);
        if (!fd_dir) continue;

        struct dirent *fd_entry;
        while ((fd_entry = readdir(fd_dir)) != NULL) {
            if (strcmp(fd_entry->d_name, ".") == 0 || strcmp(fd_entry->d_name, "..") == 0)
                continue;

            char link_path[128];
            snprintf(link_path, sizeof(link_path), "%s/%s", fd_path, fd_entry->d_name);

            char real_path[PATH_MAX];
            ssize_t len = readlink(link_path, real_path, sizeof(real_path) - 1);
            if (len == -1) continue;
            real_path[len] = '\0';

            struct stat st;
            if (stat(real_path, &st) == -1) continue;

            int index = find_or_create_entry(st.st_ino, real_path);
            if (file_entries[index].pid_count < MAX_PIDS) {
                file_entries[index].pids[file_entries[index].pid_count++] = pid;
            }
        }
        closedir(fd_dir);
    }
    closedir(proc);
}

void print_shared_files() {
    printf("Files opened with few proceses:\n");
    printf("=====================================\n");

    for (int i = 0; i < en#include <dirent.h>tr#include <string.h>].#include <unistd.h>%s (inode: %lu)\n", file_entries[i].filepath, file_entries[i].inode);
            printf("  Процеси: ");
            for (int j = 0; j < file_ent#include <ctype.h>rin"#define MAX_PIDS 128
#define MAX_ENTRIES 4096  c(typedef struct {      ino_t inode;print_shared_files();
    return 0;
}
