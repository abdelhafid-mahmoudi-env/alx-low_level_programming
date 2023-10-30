#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <elf.h>

void checkIfElfFile(unsigned char *e_ident);
void displayElfMagicNumbers(unsigned char *e_ident);
void displayElfClass(unsigned char *e_ident);
void displayElfDataFormat(unsigned char *e_ident);
void displayElfVersion(unsigned char *e_ident);
void displayElfOsAbi(unsigned char *e_ident);
void displayElfAbiVersion(unsigned char *e_ident);
void displayElfFileType(unsigned int e_type, unsigned char *e_ident);
void displayElfEntryPoint(unsigned long int e_entry, unsigned char *e_ident);
void closeElfFile(int fileDescriptor);

void checkIfElfFile(unsigned char *e_ident) {
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

void displayElfMagicNumbers(unsigned char *e_ident) {
    int index;

    printf("  ELF Magic:   ");

    for (index = 0; index < EI_NIDENT; index++) {
        printf("%02x", e_ident[index]);
        if (index == EI_NIDENT - 1)
            printf("\n");
        else
            printf(" ");
    }
}

void displayElfClass(unsigned char *e_ident) {
    printf("  ELF Class:                             ");

    switch (e_ident[EI_CLASS]) {
        case ELFCLASSNONE:
            printf("none\n");
            break;
        case ELFCLASS32:
            printf("ELF32\n");
            break;
        case ELFCLASS64:
            printf("ELF64\n");
            break;
        default:
            printf("<unknown: %x>\n", e_ident[EI_CLASS]);
    }
}

void displayElfDataFormat(unsigned char *e_ident) {
    printf("  ELF Data Format:                      ");

    switch (e_ident[EI_DATA]) {
        case ELFDATANONE:
            printf("none\n");
            break;
        case ELFDATA2LSB:
            printf("2's complement, little endian\n");
            break;
        case ELFDATA2MSB:
            printf("2's complement, big endian\n");
            break;
        default:
            printf("<unknown: %x>\n", e_ident[EI_CLASS]);
    }
}

void displayElfVersion(unsigned char *e_ident) {
    printf("  ELF Version:                          %d", e_ident[EI_VERSION]);

    switch (e_ident[EI_VERSION]) {
        case EV_CURRENT:
            printf(" (current)\n");
            break;
        default:
            printf("\n");
            break;
    }
}

void displayElfOsAbi(unsigned char *e_ident) {
    printf("  ELF OS/ABI:                           ");

    switch (e_ident[EI_OSABI]) {
        case ELFOSABI_NONE:
            printf("UNIX - System V\n");
            break;
        case ELFOSABI_HPUX:
            printf("UNIX - HP-UX\n");
            break;
        case ELFOSABI_NETBSD:
            printf("UNIX - NetBSD\n");
            break;
        case ELFOSABI_LINUX:
            printf("UNIX - Linux\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("UNIX - Solaris\n");
            break;
        case ELFOSABI_IRIX:
            printf("UNIX - IRIX\n");
            break;
        case ELFOSABI_FREEBSD:
            printf("UNIX - FreeBSD\n");
            break;
        case ELFOSABI_TRU64:
            printf("UNIX - TRU64\n");
            break;
        case ELFOSABI_ARM:
            printf("ARM\n");
            break;
        case ELFOSABI_STANDALONE:
            printf("Standalone App\n");
            break;
        default:
            printf("<unknown: %x>\n", e_ident[EI_OSABI]);
    }
}

void displayElfAbiVersion(unsigned char *e_ident) {
    printf("  ELF ABI Version:                      %d\n", e_ident[EI_ABIVERSION]);
}

void displayElfFileType(unsigned int e_type, unsigned char *e_ident) {
    if (e_ident[EI_DATA] == ELFDATA2MSB)
        e_type >>= 8;

    printf("  ELF File Type:                        ");

    switch (e_type) {
        case ET_NONE:
            printf("NONE (None)\n");
            break;
        case ET_REL:
            printf("REL (Relocatable file)\n");
            break;
        case ET_EXEC:
            printf("EXEC (Executable file)\n");
            break;
        case ET_DYN:
            printf("DYN (Shared object file)\n");
            break;
        case ET_CORE:
            printf("CORE (Core file)\n");
            break;
        default:
            printf("<unknown: %x>\n", e_type);
    }
}

void displayElfEntryPoint(unsigned long int e_entry, unsigned char *e_ident) {
    printf("  ELF Entry Point Address:              ");

    if (e_ident[EI_DATA] == ELFDATA2MSB) {
        e_entry = ((e_entry << 8) & 0xFF00FF00) |
                  ((e_entry >> 8) & 0xFF00FF);
        e_entry = (e_entry << 16) | (e_entry >> 16);
    }

    if (e_ident[EI_CLASS] == ELFCLASS32)
        printf("%#x\n", (unsigned int)e_entry);
    else
        printf("%#lx\n", e_entry);
}

void closeElfFile(int fileDescriptor) {
    if (close(fileDescriptor) == -1) {
        dprintf(STDERR_FILENO, "Error: Can't close file descriptor %d\n", fileDescriptor);
        exit(98);
    }
}

int main(int argc, char *argv[]) {
    Elf64_Ehdr *elfHeader;
    int fileDescriptor, bytesRead;

    if (argc != 2) {
        dprintf(STDERR_FILENO, "Usage: %s <elf_file>\n", argv[0]);
        exit(98);
    }

    fileDescriptor = open(argv[1], O_RDONLY);
    if (fileDescriptor == -1) {
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
        exit(98);
    }

    elfHeader = malloc(sizeof(Elf64_Ehdr));
    if (elfHeader == NULL) {
        closeElfFile(fileDescriptor);
        dprintf(STDERR_FILENO, "Error: Can't allocate memory\n");
        exit(98);
    }

    bytesRead = read(fileDescriptor, elfHeader, sizeof(Elf64_Ehdr));
    if (bytesRead == -1) {
        free(elfHeader);
        closeElfFile(fileDescriptor);
        dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
        exit(98);
    }

    checkIfElfFile(elfHeader->e_ident);
    printf("ELF Header Information:\n");
    displayElfMagicNumbers(elfHeader->e_ident);
    displayElfClass(elfHeader->e_ident);
    displayElfDataFormat(elfHeader->e_ident);
    displayElfVersion(elfHeader->e_ident);
    displayElfOsAbi(elfHeader->e_ident);
    displayElfAbiVersion(elfHeader->e_ident);
    displayElfFileType(elfHeader->e_type, elfHeader->e_ident);
    displayElfEntryPoint(elfHeader->e_entry, elfHeader->e_ident);

    free(elfHeader);
    closeElfFile(fileDescriptor);
    return 0;
}

