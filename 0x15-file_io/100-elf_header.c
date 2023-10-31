#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * elfCheckElf - checks if the file is an ELF file.
 * @e_ident: A pointer to the ELF identifier.
 */
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
 * getType - returns the string description of e_type.
 * @type: The e_type value.
 * Return: String description.
 */
const char *getType(int type)
{
	switch (type)
	{
		case ET_NONE: return ("NONE (None)");
		case ET_REL: return ("REL (Relocatable file)");
		case ET_EXEC: return ("EXEC (Executable file)");
		case ET_DYN: return ("DYN (Shared object file)");
		case ET_CORE: return ("CORE (Core file)");
		default: return ("<unknown>");
	}
}

/**
 * getOSABI - returns the string description of EI_OSABI.
 * @osabi: The EI_OSABI value.
 * Return: String description.
 */
const char *getOSABI(int osabi)
{
	switch (osabi)
	{
		case ELFOSABI_NONE: return ("UNIX - System V");
		case ELFOSABI_HPUX: return ("UNIX - HP-UX");
		case ELFOSABI_NETBSD: return ("UNIX - NetBSD");
		case ELFOSABI_GNU: return ("UNIX - GNU");
		case ELFOSABI_SOLARIS: return ("UNIX - Solaris");
		default: return ("<unknown>");
	}
}

/**
 * displayHeader - displays the ELF header.
 * @header: A pointer to the ELF header.
 */
void displayHeader(Elf64_Ehdr *header)
{
	int index;

	printf("ELF Header:\n");
	printf("  Magic:   ");
	for (index = 0; index < EI_NIDENT; index++)
	{
		printf("%02x ", header->e_ident[index]);
		if (index == EI_NIDENT - 1)
			printf("\n");
	}

	printf("  Class:                             ");
	printf("%s\n", header->e_ident[EI_CLASS] == ELFCLASS32 ?
	       "ELF32" : "ELF64");

	printf("  Data:                              ");
	printf("%s\n", header->e_ident[EI_DATA] == ELFDATA2LSB ?
	       "2's complement, little endian" :
	       "2's complement, big endian");

	printf("  Version:                           %d (current)\n",
	       header->e_ident[EI_VERSION]);
	printf("  OS/ABI:                            %s\n",
	       getOSABI(header->e_ident[EI_OSABI]));
	printf("  ABI Version:                       %d\n",
	       header->e_ident[EI_ABIVERSION]);
	printf("  Type:                              %s\n",
	       getType(header->e_type));
	printf("  Entry point address:               %#lx\n",
	       header->e_entry);
}

/**
 * main - Entry point.
 * @argc: Argument count.
 * @argv: Argument vector.
 * Return: 0 on success, 98 on failure.
 */
int main(int argc, char *argv[])
{
	int fd;
	Elf64_Ehdr *header;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: %s <elf_file>\n", argv[0]);
		return (98);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		return (98);
	}

	header = malloc(sizeof(Elf64_Ehdr));
	if (!header)
	{
		dprintf(STDERR_FILENO, "Error: Can't allocate memory\n");
		close(fd);
		return (98);
	}

	if (read(fd, header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
	{
		free(header);
		close(fd);
		dprintf(STDERR_FILENO, "Error reading ELF header\n");
		return (98);
	}

	elfCheckElf(header->e_ident);
	displayHeader(header);

	free(header);
	close(fd);
	return (0);
}
