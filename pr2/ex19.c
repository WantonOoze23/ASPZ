#include <link.h>
#include <stdio.h>

#define _GNU_SOURCE

int callback(struct dl_phdr_info *info, size_t size, void *data) {
    if (info->dlpi_name && info->dlpi_name[0] != '\0') {
        printf("Loaded: %s\n", info->dlpi_name);
    }
    return 0;
}

int main() {
    printf("Listing loaded shared libraries:\n");
    dl_iterate_phdr(callback, NULL);
    return 0;
}
