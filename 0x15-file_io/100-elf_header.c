#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void elfCheckElf(unsigned char *e_ident);
void elfDisplayAll(Elf64_Ehdr *header);
void elfCloseFile(int fileDescriptor);
int elfOpenFile(char *filename);
Elf64_Ehdr *elfReadHeader(int fileDescriptor);

/**
 * elfCheckElf - checks if a file is an ELF file
 * @e_ident: ELF identification bytes
 */
void elfCheckElf(unsigned char *e_ident)
{
    if (e_ident[0] != 0x7f || e_ident[1] != 'E' || e_ident[2] != 'L' || e_ident[3] != 'F')
    {
        dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
        exit(98);
    }
}

/**
 * elfDisplayAll - display all relevant ELF header information
 * @e_ident: ELF identification bytes
 */
void elfDisplayAll(Elf64_Ehdr *header)
{
    printf("  Magic:   ");
    for (int index = 0; index < EI_NIDENT; index++)
    {
        printf("%02x ", header->e_ident[index]);
    }
    printf("\n");

    printf("  Class:                             ");
    switch (header->e_ident[EI_CLASS])
    {
    case ELFCLASS32:
        printf("ELF32\n");
        break;
    case ELFCLASS64:
        printf("ELF64\n");
        break;
    default:
        printf("<unknown: %x>\n", header->e_ident[EI_CLASS]);
        break;
    }

    printf("  Data:                              ");
    switch (header->e_ident[EI_DATA])
    {
    case ELFDATA2LSB:
        printf("2's complement, little endian\n");
        break;
    case ELFDATA2MSB:
        printf("2's complement, big endian\n");
        break;
    default:
        printf("<unknown: %x>\n", header->e_ident[EI_DATA]);
        break;
    }

    printf("  Version:                           %d\n", header->e_ident[EI_VERSION]);
    printf("  OS/ABI:                            ");
    switch (header->e_ident[EI_OSABI])
    {
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
        printf("<unknown: %x>\n", header->e_ident[EI_OSABI]);
        break;
    }

    printf("  ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);
    printf("  Type:                              %d\n", header->e_type);
    printf("  Entry point address:               %lx\n", header->e_entry);
}

/**
 * elfCloseFile - close a file descriptor
 * @fileDescriptor: file descriptor to close
 */
void elfCloseFile(int fileDescriptor)
{
    if (close(fileDescriptor) == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fileDescriptor);
        exit(98);
    }
}

/**
 * elfOpenFile - open an ELF file
 * @filename: name of the file to open
 * Return: file descriptor of the opened file
 */
int elfOpenFile(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", filename);
        exit(98);
    }
    return fd;
}

/**
 * elfReadIdent - read the ELF identification bytes
 * @fileDescriptor: file descriptor to read from
 * Return: pointer to ELF identification bytes
 */
Elf64_Ehdr *elfReadHeader(int fileDescriptor)
{
    Elf64_Ehdr *header = malloc(sizeof(Elf64_Ehdr));
    if (!header)
    {
        dprintf(STDERR_FILENO, "Error: Can't allocate memory for ELF header\n");
        exit(98);
    }
    if (read(fileDescriptor, header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
    {
        free(header);
        dprintf(STDERR_FILENO, "Error reading ELF header\n");
        exit(98);
    }
    return header;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        dprintf(STDERR_FILENO, "Usage: %s <elf_file>\n", argv[0]);
        exit(98);
    }

    int fileDescriptor = elfOpenFile(argv[1]);
    Elf64_Ehdr *header = elfReadHeader(fileDescriptor);

    elfCheckElf(header->e_ident);
    printf("ELF Header:\n");
    elfDisplayAll(header);

    free(header);
    elfCloseFile(fileDescriptor);
    return 0;
}
