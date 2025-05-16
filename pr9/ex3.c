#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main() {
    FILE *fp;
    char *filename = "/tmp/userfile.txt";
    char *copyname = "/home/%s/userfile_copy.txt";
    char usercopy[256];
    struct passwd *pw = getpwuid(getuid());

    fp = fopen(filename, "w");
    if (!fp) {
        perror("Failed to create file");
        return 1;
    }
    fprintf(fp, "This file was created by a regular user.\n");
    fclose(fp);
    printf("File %s created by regular user.\n", filename);

    snprintf(usercopy, sizeof(usercopy), copyname, pw->pw_name);
    if (system("whoami | grep root > /dev/null") == 0) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "cp %s %s", filename, usercopy);
        if (system(cmd) != 0) {
            printf("Error copying file as root.\n");
            return 1;
        }
        printf("Root copied the file to %s\n", usercopy);
    } else {
        printf("Root privileges are required to copy the file to the home directory.\n");
        printf("Try running the program with sudo.\n");
        return 1;
    }

    printf("Attempting to modify the file as a regular user...\n");
    fp = fopen(usercopy, "a");
    if (!fp) {
        perror("Regular user cannot modify the file");
    } else {
        fprintf(fp, "Line added by regular user.\n");
        fclose(fp);
        printf("File successfully modified by regular user.\n");
    }

    printf("Attempting to delete the file as a regular user...\n");
    if (remove(usercopy) == 0) {
        printf("File successfully deleted by regular user.\n");
    } else {
        perror("Regular user cannot delete the file");
    }

    remove(filename);

    return 0;
}