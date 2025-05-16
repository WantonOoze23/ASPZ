#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *fname = "/tmp/testfile_ex5.txt";
    FILE *fp;

    fp = fopen(fname, "w");
    if (!fp) {
        perror("Failed to create file");
        return 1;
    }
    fprintf(fp, "Test string\n");
    fclose(fp);
    printf("File %s created by regular user.\n", fname);

    printf("Changing owner and permissions (root required)...\n");
    printf("Execute the following commands as root in the terminal:\n");
    printf("  sudo chown root:root %s\n", fname);
    printf("  sudo chmod 600 %s\n", fname);
    printf("After that, press Enter to continue...\n");
    getchar();

    fp = fopen(fname, "r");
    if (fp) {
        printf("File read: ALLOWED\n");
        fclose(fp);
    } else {
        printf("File read: DENIED\n");
    }

    fp = fopen(fname, "a");
    if (fp) {
        printf("File write: ALLOWED\n");
        fclose(fp);
    } else {
        printf("File write: DENIED\n");
    }

    remove(fname);

    return 0;
}