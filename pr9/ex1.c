#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UID_MIN 1000 

int main() {
    FILE *fp;
    char line[1024];
    char *username;
    int uid;
    char *myname = getlogin();

    fp = popen("getent passwd", "r");
    if (fp == NULL) {
        perror("Failed to execute getent passwd");
        return 1;
    }

    printf("Regular users (UID > %d), except current (%s):\n", UID_MIN, myname);

    while (fgets(line, sizeof(line), fp)) {
        char *saveptr;
        char *fields[7];
        char *token = strtok_r(line, ":\n", &saveptr);
        int i = 0;
        while (token && i < 7) {
            fields[i++] = token;
            token = strtok_r(NULL, ":\n", &saveptr);
        }
        if (i < 3) continue;

        username = fields[0];
        uid = atoi(fields[2]);

        if (uid > UID_MIN && strcmp(username, myname) != 0) {
            printf("User: %s (UID: %d)\n", username, uid);
        }
    }

    pclose(fp);
    return 0;
}