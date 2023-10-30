#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void elfCheckElf(unsigned char *e_ident);
void elfDisplayAll(unsigned char *e_ident, unsigned int e_type, unsigned long int e_entry);
void elfCloseFile(int fileDescriptor);
int elfOpenFile(char *filename);
unsigned char* elfReadIdent(int fileDescriptor);

void elfCheckElf(unsigned char *e_ident) {
    int index;
    for (index = 0; index < 4; index++) {
        if (e_ident[index] != 127 &&
            e_ident[index] != 'E' &&
            e_ident[index] != 'L' &&
            e_ident[index] != 'F') {
            dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
            exit(98);
        }
    }
}

void elfDisplayAll(unsigned char *e_ident) {
    int index;

    printf("  Magic:   ");
    for (index = 0; index < EI_NIDENT; index++) {
        printf("%02x", e_ident[index]);
        if (index == EI_NIDENT - 1)
            printf("\n");
        else
            printf(" ");
    }

    printf("  Class:                             ");
    switch (e_ident[EI_CLASS]) {
        case ELFCLASSNONE: printf("none\n"); break;
        case ELFCLASS32: printf("ELF32\n"); break;
        case ELFCLASS64: printf("ELF64\n"); break;
        default: printf("<unknown: %x>\n", e_ident[EI_CLASS]);
    }

    printf("  Data:                              ");
    switch (e_ident[EI_DATA]) {
        case ELFDATANONE: printf("none\n"); break;
        case ELFDATA2LSB: printf("2's complement, little endian\n"); break;
        case ELFDATA2MSB: printf("2's complement, big endian\n"); break;
        default: printf("<unknown: %x>\n", e_ident[EI_DATA]);
    }

    printf("  Version:                           %d", e_ident[EI_VERSION]);
    if (e_ident[EI_VERSION] == EV_CURRENT) {
        printf(" (current)\n");
    } else {
        printf("\n");
    }

    printf("  OS/ABI:                            ");
    switch (e_ident[EI_OSABI]) {
        case ELFOSABI_NONE: printf("UNIX - System V\n"); break;
        case ELFOSABI_HPUX: printf("UNIX - HP-UX\n"); break;
        case ELFOSABI_NETBSD: printf("UNIX - NetBSD\n"); break;
        case ELFOSABI_LINUX: printf("UNIX - Linux\n"); break;
        case ELFOSABI_SOLARIS: printf("UNIX - Solaris\n"); break;
        case ELFOSABI_IRIX: printf("UNIX - IRIX\n"); break;
        case ELFOSABI_FREEBSD: printf("UNIX - FreeBSD\n"); break;
        case ELFOSABI_TRU64: printf("UNIX - TRU64\n"); break;
        case ELFOSABI_ARM: printf("ARM\n"); break;
        case ELFOSABI_STANDALONE: printf("Standalone App\n"); break;
        default: printf("<unknown: %x>\n", e_ident[EI_OSABI]);
    }

    printf("  ABI Version:                       %d\n", e_ident[EI_ABIVERSION]);
}

void elfCloseFile(int fileDescriptor) {
    if (close(fileDescriptor) == -1) {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fileDescriptor);
        exit(98);
    }
}

int elfOpenFile(char *filename) {
    int fileDescriptor = open(filename, O_RDONLY);
    if (fileDescriptor == -1) {
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", filename);
        exit(98);
    }
    return fileDescriptor;
}

unsigned char* elfReadIdent(int fileDescriptor) {
    unsigned char *e_ident = malloc(EI_NIDENT);
    if (e_ident == NULL) {
        dprintf(STDERR_FILENO, "Error: Can't allocate memory for ELF identification\n");
        exit(98);
    }

    int bytesRead = read(fileDescriptor, e_ident, EI_NIDENT);
    if (bytesRead == -1) {
        free(e_ident);
        dprintf(STDERR_FILENO, "Error reading ELF identification\n");
        exit(98);
    }

    return e_ident;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        dprintf(STDERR_FILENO, "Usage: %s <elf_file>\n", argv[0]);
        exit(98);
    }

    int fileDescriptor = elfOpenFile(argv[1]);
    unsigned char *e_ident = elfReadIdent(fileDescriptor);

    elfCheckElf(e_ident);
    printf("ELF Header:\n");
    elfDisplayAll(e_ident, 0, 0);

    free(e_ident);
    elfCloseFile(fileDescriptor);
    return 0;
}
