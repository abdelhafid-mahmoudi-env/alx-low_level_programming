#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <string.h>
#include <error.h>

/**
 * print_elf_header - Print the ELF header information.
 * @header: Pointer to the ELF header structure.
 */
void print_elf_header(Elf64_Ehdr *header)
{
    printf("ELF Header:\n");
    printf("  Magic:   %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
           header->e_ident[EI_MAG0], header->e_ident[EI_MAG1], header->e_ident[EI_MAG2], header->e_ident[EI_MAG3],
           header->e_ident[EI_MAG4], header->e_ident[EI_MAG5], header->e_ident[EI_MAG6], header->e_ident[EI_MAG7],
           header->e_ident[EI_MAG8], header->e_ident[EI_MAG9], header->e_ident[EI_MAG10], header->e_ident[EI_MAG11],
           header->e_ident[EI_MAG12], header->e_ident[EI_MAG13], header->e_ident[EI_MAG14], header->e_ident[EI_MAG15]);
    printf("  Class:                             %s\n", header->e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32" : "ELF64");
    printf("  Data:                              %s\n", header->e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
    printf("  Version:                           %d (current)\n", header->e_ident[EI_VERSION]);
    printf("  OS/ABI:                            %s\n", header->e_ident[EI_OSABI] == ELFOSABI_SYSV ? "UNIX - System V" : "Other");
    printf("  ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);
    printf("  Type:                              %s\n", header->e_type == ET_EXEC ? "EXEC (Executable file)" : "Other");
    printf("  Entry point address:               0x%lx\n", (unsigned long)header->e_entry);
}

/**
 * main - Entry point of the program.
 * @ac: Argument count.
 * @av: Argument vector.
 * Return: 0 on success, or the exit code on failure.
 */
int main(int ac, char **av)
{
    int fd;
    Elf64_Ehdr header;

    if (ac != 2)
    {
        dprintf(STDERR_FILENO, "Usage: %s elf_filename\n", av[0]);
        return (EXIT_FAILURE);
    }

    fd = open(av[1], O_RDONLY);
    if (fd == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
        return (98);
    }

    if (read(fd, &header, sizeof(header)) != sizeof(header))
    {
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", av[1]);
        close(fd);
        return (98);
    }

    close(fd);

    if (header.e_ident[EI_MAG0] != ELFMAG0 ||
        header.e_ident[EI_MAG1] != ELFMAG1 ||
        header.e_ident[EI_MAG2] != ELFMAG2 ||
        header.e_ident[EI_MAG3] != ELFMAG3)
    {
        dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
        return (98);
    }

    print_elf_header(&header);

    return (EXIT_SUCCESS);
}

