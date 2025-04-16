#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_SIZE 1048576  // максимальний розмір файлу в байтах (1 MB)

void copy_file(const char *src, const char *dst) {
    FILE *src_file = fopen(src, "rb");
    if (src_file == NULL) {
        printf("Cannot open file %s for reading\n", src);
        return;
    }

    fseek(src_file, 0, SEEK_END);
    long src_size = ftell(src_file);
    if (src_size > MAX_FILE_SIZE) {
        printf("File size limit exceeded\n");
        fclose(src_file);
        return;
    }
    rewind(src_file);

    FILE *dst_file = fopen(dst, "wb");
    if (dst_file == NULL) {
        printf("Cannot open file %s for writing\n", dst);
        fclose(src_file);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytes, dst_file);
    }

    fclose(src_file);
    fclose(dst_file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program needs two arguments\n");
        return 1;
    }

    copy_file(argv[1], argv[2]);
    return 0;
}
