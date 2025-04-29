#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

int is_elf(Elf64_Ehdr *ehdr) {
    if (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
        ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
        ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
        ehdr->e_ident[EI_MAG3] != ELFMAG3) {
        return 0;
    }
    return 1;
}

void print_elf_info(Elf64_Ehdr *ehdr) {
    printf("ELF Header:\n");
    printf("  Class:                             %s\n", 
           ehdr->e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32" : 
           ehdr->e_ident[EI_CLASS] == ELFCLASS64 ? "ELF64" : "Invalid");
    
    printf("  Data:                              %s\n", 
           ehdr->e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : 
           ehdr->e_ident[EI_DATA] == ELFDATA2MSB ? "2's complement, big endian" : "Invalid");
    
    printf("  Version:                           %d\n", ehdr->e_ident[EI_VERSION]);
    
    printf("  OS/ABI:                            ");
    switch (ehdr->e_ident[EI_OSABI]) {
        case ELFOSABI_SYSV: printf("UNIX - System V\n"); break;
        case ELFOSABI_HPUX: printf("HP-UX\n"); break;
        case ELFOSABI_NETBSD: printf("NetBSD\n"); break;
        case ELFOSABI_LINUX: printf("Linux\n"); break;
        case ELFOSABI_SOLARIS: printf("Solaris\n"); break;
        case ELFOSABI_FREEBSD: printf("FreeBSD\n"); break;
        default: printf("Unknown\n");
    }
    
    printf("  Type:                              ");
    switch (ehdr->e_type) {
        case ET_NONE: printf("NONE (Unknown type)\n"); break;
        case ET_REL: printf("REL (Relocatable file)\n"); break;
        case ET_EXEC: printf("EXEC (Executable file)\n"); break;
        case ET_DYN: printf("DYN (Shared object file)\n"); break;
        case ET_CORE: printf("CORE (Core file)\n"); break;
        default: printf("Unknown\n");
    }
    
    printf("  Machine:                           ");
    switch (ehdr->e_machine) {
        case EM_X86_64: printf("AMD x86-64\n"); break;
        case EM_386: printf("Intel 80386\n"); break;
        case EM_ARM: printf("ARM\n"); break;
        case EM_AARCH64: printf("AArch64\n"); break;
        default: printf("Unknown\n");
    }
    
    printf("  Entry point address:               0x%lx\n", (unsigned long)ehdr->e_entry);
    printf("  Start of program headers:          %lu (bytes into file)\n", (unsigned long)ehdr->e_phoff);
    printf("  Start of section headers:          %lu (bytes into file)\n", (unsigned long)ehdr->e_shoff);
    printf("  Number of program headers:         %d\n", ehdr->e_phnum);
    printf("  Number of section headers:         %d\n", ehdr->e_shnum);
    printf("  Section header string table index: %d\n", ehdr->e_shstrndx);
}

void print_elf_dependencies(const char *filename) {
    int fd;
    struct stat st;
    void *map;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
    Elf64_Dyn *dyn;
    char *strtab = NULL;
    size_t dynstr_idx = 0;
    size_t i, j;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return;
    }

    if (fstat(fd, &st) < 0) {
        perror("fstat");
        close(fd);
        return;
    }

    map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return;
    }

    ehdr = (Elf64_Ehdr *)map;
    if (!is_elf(ehdr)) {
        printf("%s is not an ELF file\n", filename);
        munmap(map, st.st_size);
        close(fd);
        return;
    }

    print_elf_info(ehdr);

    shdr = (Elf64_Shdr *)((char *)map + ehdr->e_shoff);
    char *shstrtab = (char *)map + shdr[ehdr->e_shstrndx].sh_offset;

    for (i = 0; i < ehdr->e_shnum; i++) {
        if (strcmp(shstrtab + shdr[i].sh_name, ".dynstr") == 0) {
            strtab = (char *)map + shdr[i].sh_offset;
            dynstr_idx = i;
            break;
        }
    }

    if (!strtab) {
        printf("No .dynstr section found\n");
        munmap(map, st.st_size);
        close(fd);
        return;
    }

    for (i = 0; i < ehdr->e_shnum; i++) {
        if (shdr[i].sh_type == SHT_DYNAMIC) {
            dyn = (Elf64_Dyn *)((char *)map + shdr[i].sh_offset);
            
            printf("\nDynamic Dependencies:\n");
            for (j = 0; dyn[j].d_tag != DT_NULL; j++) {
                if (dyn[j].d_tag == DT_NEEDED) {
                    printf("  %s\n", strtab + dyn[j].d_un.d_val);
                }
            }
            break;
        }
    }

    Elf64_Sym *symtab = NULL;
    size_t symtab_entries = 0;

    for (i = 0; i < ehdr->e_shnum; i++) {
        if (shdr[i].sh_type == SHT_DYNSYM) {
            symtab = (Elf64_Sym *)((char *)map + shdr[i].sh_offset);
            symtab_entries = shdr[i].sh_size / shdr[i].sh_entsize;
            
            printf("\nImported Symbols:\n");
            for (j = 0; j < symtab_entries; j++) {
                if (ELF64_ST_BIND(symtab[j].st_info) == STB_GLOBAL &&
                    symtab[j].st_shndx == SHN_UNDEF) {
                    printf("  %s\n", strtab + symtab[j].st_name);
                }
            }
            break;
        }
    }

    munmap(map, st.st_size);
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <elf_file1> [elf_file2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("\n=== Analyzing %s ===\n", argv[i]);
        print_elf_dependencies(argv[i]);
    }

    return 0;
}