#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

#define TARGET_USERNAME "root" 
#define TARGET_GROUPNAME "student" 
#define MEMORY_SIZE 1024 

int main() {
    char *buffer = (char *)malloc(MEMORY_SIZE * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Не вдалося виділити пам’ять\n");
        return 1;
    }

    for (int i = 0; i < MEMORY_SIZE; i++) {
        buffer[i] = 'A';
    }

    struct passwd *pw = getpwuid(getuid());
    const char *username = pw ? pw->pw_name : "unknown";

    struct group *gr = getgrgid(getgid());
    const char *groupname = gr ? gr->gr_name : "unknown";

    if (strcmp(username, TARGET_USERNAME) == 0 || strcmp(groupname, TARGET_GROUPNAME) == 0) {
        printf("Memory is NOT freed (User: %s, group: %s)\n", username, groupname);
    } else {
        printf("Memory is freed (User: %s, group: %s)\n", username, groupname);
        free(buffer);
    }

    return 0;
}