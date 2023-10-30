#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "main.h"

#define ELF_MAGIC_SIZE 16

/**
 * print_error_and_exit - Print an error message to stderr and exit with status code 98.
 * @message: The error message to print.
 */
void print_error_and_exit(const char *message)
{
    dprintf(2, "%s\n", message);
    exit(98);
}

/**
 * print_elf_header - Print the ELF header information.
 * @header: Pointer to the ELF header structure.
 */
void print_elf_header(Elf64_Ehdr *header)
{
    int i;

    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (i = 0; i < ELF_MAGIC_SIZE; i++)
        printf("%02x ", header->e_ident[i]);
    printf("\n");
    printf("  Class:                             ELF%d\n", header->e_ident[EI_CLASS]);
    printf("  Data:                              2's complement, %s endian\n", (header->e_ident[EI_DATA] == ELFDATA2LSB) ? "little" : "big");
    printf("  Version:                           %d (current)\n", header->e_ident[EI_VERSION]);
    printf("  OS/ABI:                            ");
    switch (header->e_ident[EI_OSABI])
    {
        case ELFOSABI_SYSV:
            printf("UNIX - System V\n");
            break;
        case ELFOSABI_HPUX:
            printf("HP-UX\n");
            break;
        case ELFOSABI_NETBSD:
            printf("NetBSD\n");
            break;
        case ELFOSABI_LINUX:
            printf("Linux\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("Solaris\n");
            break;
        case ELFOSABI_IRIX:
            printf("IRIX\n");
            break;
        case ELFOSABI_FREEBSD:
            printf("FreeBSD\n");
            break;
        case ELFOSABI_TRU64:
            printf("Tru64\n");
            break;
        case ELFOSABI_ARM:
            printf("ARM\n");
            break;
        case ELFOSABI_STANDALONE:
            printf("Standalone (embedded) application\n");
            break;
        default:
            printf("<unknown: %d>\n", header->e_ident[EI_OSABI]);
            break;
    }
    printf("  ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);
    printf("  Type:                              ");
    switch (header->e_type)
    {
        case ET_NONE:
            printf("NONE (Unknown type)\n");
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
            printf("<unknown: %d>\n", header->e_type);
            break;
    }
    printf("  Entry point address:               0x%lx\n", header->e_entry);
}

int main(int argc, char **argv)
{
    int fd;
    Elf64_Ehdr elf_header;

    if (argc != 2)
        print_error_and_exit("Usage: elf_header elf_filename");

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        print_error_and_exit("Error: Can't open file");

    if (read(fd, &elf_header, sizeof(elf_header)) != sizeof(elf_header))
        print_error_and_exit("Error: Can't read file");

    if (lseek(fd, 0, SEEK_SET) == -1)
        print_error_and_exit("Error: Can't reset file offset");

    print_elf_header(&elf_header);

    close(fd);
    return (0);
}

