#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void elfCheckElf(unsigned char *e_ident);
void elfDisplayAll(Elf64_Ehdr *header);
void elfCloseFile(int fileDescriptor);
int elfOpenFile(char *filename);
Elf64_Ehdr *elfReadHeader(int fileDescriptor);

void elfCheckElf(unsigned char *e_ident) {
	int index;

	for (index = 0; index < 4; index++)
	{
		if (e_ident[index] != 127 &&
		    e_ident[index] != 'E' &&
		    e_ident[index] != 'L' &&
		    e_ident[index] != 'F')
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}
	}
}

/**
 * print_magic - it will print the entrancing numbers of an ELF header
 * @e_ident: this is a variable for  an array containing the ELF,
 * entrancing numbers
 *
 * Description:the entrancing  numbers will be separated by spaces
 */
void print_magic(unsigned char *e_ident)
{
	int index;

	printf(" Magic: ");

	for (index = 0; index < EI_NIDENT; index++)
	{
		printf("%02x", e_ident[index]);

		if (index == EI_NIDENT - 1)
			printf("\n");
		else
			printf(" ");
	}
}

/**
 * print_class - it will print the class of an ELF header
 * @e_ident: this is a variable for  an array containing the ELF class
 */
void print_class(unsigned char *e_ident)
{
	printf(" Class: ");

	switch (e_ident[EI_CLASS])
	{
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

/**
 * print_data - it will print the data of an ELF header
 * @e_ident: this is a variable for  an array containing the ELF class
 */
void print_data(unsigned char *e_ident)
{
	printf(" Data: ");

	switch (e_ident[EI_DATA])
	{
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

/**
 *  * print_version - it will prints the version of an ELF header
 *   * @e_ident: this is a variable for  an array containing the ELF version
 *    */
void print_version(unsigned char *e_ident)
{
	 printf(" Version: %d",
			  e_ident[EI_VERSION]);

	switch (e_ident[EI_VERSION])
	{
	case EV_CURRENT:
		printf(" (current)\n");
		break;
	default:
		printf("\n");
		break;
	}
}

/**
 * print_osabi - it will print the OS/ABI of an ELF header
 * @e_ident: this is a variable for  an array containing the ELF version
 */
void print_osabi(unsigned char *e_ident)
{
	printf(" OS/ABI: ");

	switch (e_ident[EI_OSABI])
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
		printf("<unknown: %x>\n", e_ident[EI_OSABI]);
	}
}

/**
 * print_abi - it will print the ABI version of an ELF header
 * @e_ident: a variable for an array holding the ELF ABI version
 */
void print_abi(unsigned char *e_ident)
{
	printf(" ABI Version: %d\n",
		e_ident[EI_ABIVERSION]);
}

/**
 * print_type - this willprint the type of ELF header.
 * @e_type: this is the ELF type
 * @e_ident: this is a variable for  an array containing the ELF class
 */
void print_type(unsigned int e_type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
		e_type >>= 8;

	printf(" Type: ");

	switch (e_type)
	{
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

/**
 * print_entry - it will print the arrival point of an ELF header
 * @e_entry: this will be ther  address of the ELF arrival point
 * @e_ident: this is a variable for  an array containing the ELF class
 */
void print_entry(unsigned long int e_entry, unsigned char *e_ident)
{
	printf(" Entry point address: ");

	if (e_ident[EI_DATA] == ELFDATA2MSB)
	{
		e_entry = ((e_entry << 8) & 0xFF00FF00) |
			  ((e_entry >> 8) & 0xFF00FF);
		e_entry = (e_entry << 16) | (e_entry >> 16);
	}

	if (e_ident[EI_CLASS] == ELFCLASS32)
		printf("%#x\n", (unsigned int)e_entry);

	else
		printf("%#lx\n", e_entry);
}

void elfDisplayAll(Elf64_Ehdr *header) {
  printf("ELF Header:\n");
  print_magic(header->e_ident);
	print_class(header->e_ident);
	print_data(header->e_ident);
	print_version(header->e_ident);
	print_osabi(header->e_ident);
	print_abi(header->e_ident);
	print_type(header->e_type, header->e_ident);
	print_entry(header->e_entry, header->e_ident);
}

int elfOpenFile(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", filename);
        exit(98);
    }
    return fd;
}

Elf64_Ehdr *elfReadHeader(int fileDescriptor) {
    Elf64_Ehdr *header = malloc(sizeof(Elf64_Ehdr));
    if (!header) {
        dprintf(STDERR_FILENO, "Error: Can't allocate memory for ELF header\n");
        exit(98);
    }
    if (read(fileDescriptor, header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)) {
        free(header);
        dprintf(STDERR_FILENO, "Error reading ELF header\n");
        exit(98);
    }
    return header;
}

void elfCloseFile(int fileDescriptor) {
    if (close(fileDescriptor) == -1) {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fileDescriptor);
        exit(98);
    }
}

int main(int argc, char *argv[]) {
    int fileDescriptor;
    Elf64_Ehdr *header;
    if (argc != 2) {
        dprintf(STDERR_FILENO, "Usage: %s <elf_file>\n", argv[0]);
        exit(98);
    }

    fileDescriptor = elfOpenFile(argv[1]);
    header = elfReadHeader(fileDescriptor);

    elfCheckElf(header->e_ident);
    elfDisplayAll(header);

    free(header);
    elfCloseFile(fileDescriptor);
    return 0;
}
