#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    const char *fname = "/tmp/testfile_ex5.txt";
    FILE *fp;
    char command[256];
    
    fp = fopen(fname, "w");
    if (!fp) {
        perror("Failed to create file");
        return 1;
    }
    fprintf(fp, "Test string\n");
    fclose(fp);
    printf("File %s created by regular user.\n", fname);
    
    printf("Changing owner and permissions automatically...\n");
    
    snprintf(command, sizeof(command), "sudo chown root:wheel %s", fname);
    printf("Executing: %s\n", command);
    if (system(command) != 0) {
        printf("Failed to change owner. Make sure you have sudo privileges.\n");
        remove(fname);
        return 1;
    }
    
    snprintf(command, sizeof(command), "sudo chmod 600 %s", fname);
    printf("Executing: %s\n", command);
    if (system(command) != 0) {
        printf("Failed to change permissions.\n");
        remove(fname);
        return 1;
    }
    
    printf("Owner and permissions changed successfully.\n");
    
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
    
    if (remove(fname) == 0) {
        printf("File removed successfully.\n");
    } else {
        printf("Failed to remove file, may need sudo: sudo rm %s\n", fname);
        snprintf(command, sizeof(command), "sudo rm %s", fname);
        system(command);
    }
    
    return 0;
}