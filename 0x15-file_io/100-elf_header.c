#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void elfCheckElf(unsigned char *e_ident);
void elfDisplayAll(Elf64_Ehdr *header);
void elfCloseFile(int fileDescriptor);
int elfOpenFile(char *filename);
Elf64_Ehdr *elfReadHeader(int fileDescriptor);

void elfCheckElf(unsigned char *e_ident)
{
	if (e_ident[0] != 0x7f || e_ident[1] != 'E' ||
	    e_ident[2] != 'L' || e_ident[3] != 'F')
	{
		dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
		exit(98);
	}
}

/**
 * getType - Gets the type of the ELF file
 * @type: The type of the ELF file
 * Return: The string representation of the type
 */
const char *getType(int type)
{
    switch (type)
    {
        case ET_NONE: return "NONE (None)";
        case ET_REL: return "REL (Relocatable file)";
        case ET_EXEC: return "EXEC (Executable file)";
        case ET_DYN: return "DYN (Shared object file)";
        case ET_CORE: return "CORE (Core file)";
        default: return "<unknown>";
    }
}

/**
 * getOSABI - Gets the OS/ABI of the ELF file
 * @osabi: The OS/ABI of the ELF file
 * Return: The string representation of the OS/ABI
 */
const char *getOSABI(int osabi)
{
    switch (osabi)
    {
        case ELFOSABI_NONE: return "UNIX - System V";
        case ELFOSABI_HPUX: return "UNIX - HP-UX";
        case ELFOSABI_NETBSD: return "UNIX - NetBSD";
        case ELFOSABI_GNU: return "UNIX - GNU";
        case ELFOSABI_SOLARIS: return "UNIX - Solaris";
        default: return "<unknown>";
    }
}

/**
 * elfDisplayAll - Displays all information of the ELF header
 * @header: The ELF header
 */
void elfDisplayAll(Elf64_Ehdr *header)
{
    int index;

    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (index = 0; index < EI_NIDENT; index++)
        printf("%02x ", header->e_ident[index]);
    printf("\n");

    printf("  Class:                             ");
    printf(header->e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32\n" : "ELF64\n");

    printf("  Data:                              ");
    printf(header->e_ident[EI_DATA] == ELFDATA2LSB ?
           "2's complement, little endian\n" : "2's complement, big endian\n");

    printf("  Version:                           %d (current)\n",
           header->e_ident[EI_VERSION]);
    printf("  OS/ABI:                            %s\n",
           getOSABI(header->e_ident[EI_OSABI]));
    printf("  ABI Version:                       %d\n",
           header->e_ident[EI_ABIVERSION]);
    printf("  Type:                              %s\n", getType(header->e_type));
    printf("  Entry point address:               %lx\n", header->e_entry);
}

/**
 * elfOpenFile - Opens the ELF file
 * @filename: The name of the ELF file
 * Return: The file descriptor of the opened file
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
 * elfReadHeader - Reads the header of the ELF file
 * @fileDescriptor: The file descriptor of the ELF file
 * Return: The ELF header
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

/**
 * elfCloseFile - Closes the ELF file
 * @fileDescriptor: The file descriptor of the ELF file
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
 * main - Entry point
 * @argc: The number of arguments
 * @argv: The arguments
 * Return: 0 on success, otherwise an error code
 */
int main(int argc, char *argv[])
{
	int fileDescriptor;
	Elf64_Ehdr *header;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: %s <elf_file>\n", argv[0]);
		return (98);
	}

	fileDescriptor = elfOpenFile(argv[1]);
	header = elfReadHeader(fileDescriptor);
	elfCheckElf(header->e_ident);
	elfDisplayAll(header);
	free(header);
	elfCloseFile(fileDescriptor);
	return (0);
}
