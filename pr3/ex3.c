#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILE_SIZE 1048576 

void write_rolls_to_file(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Cannot open file for writing");
        return;
    }

    // Перевіряємо розмір файлу
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size >= MAX_FILE_SIZE) {
        printf("File size limit exceeded\n");
        fclose(file);
        return;
    }

    srand(time(NULL));  

    for (int i = 0; i < 10; i++) {
        int roll = (rand() % 6) + 1;  
        fprintf(file, "%d\n", roll);   
    }

    fclose(file);
}

int main() {
    write_rolls_to_file("dice_rolls.txt");
    return 0;
}
