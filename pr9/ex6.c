#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int try_read(const char *fname) {
    FILE *fp = fopen(fname, "r");
    if (fp) {
        fclose(fp);
        return 1;
    }
    return 0;
}

int try_write(const char *fname) {
    FILE *fp = fopen(fname, "a");
    if (fp) {
        fclose(fp);
        return 1;
    }
    return 0;
}

int try_exec(const char *fname) {
    return access(fname, X_OK) == 0;
}

int main() {
    char *home = getenv("HOME");
    if (!home) home = "/tmp";
    printf("Contents of home directory (%s):\n", home);
    system("ls -l $HOME");

    printf("\nContents of /usr/bin:\n");
    system("ls -l /usr/bin | head -10");

    printf("\nContents of /etc:\n");
    system("ls -l /etc | head -10");

    const char *test_files[] = {
        "/etc/passwd",
        "/etc/shadow",
        "/usr/bin/ls",
        "/usr/bin/sudo",
        "/etc/hosts",
        "/etc/ssh/sshd_config",
        NULL
    };

    printf("\nChecking access to some files:\n");
    for (int i = 0; test_files[i]; ++i) {
        printf("File: %s ", test_files[i]);
        printf(" Read: %s ", try_read(test_files[i]) ? "A" : "D");
        printf(" Write:   %s ", try_write(test_files[i]) ? "A" : "D");
        printf(" Execute: %s \n", try_exec(test_files[i]) ? "A" : "D");
    }

    return 0;
}