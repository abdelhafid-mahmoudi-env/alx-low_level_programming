#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "main.h"

int main(int argc, char *argv[]) {
    Elf64_Ehdr *header;
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

    header = malloc(sizeof(Elf64_Ehdr));
    if (header == NULL) {
        closeFile(fileDescriptor);
        dprintf(STDERR_FILENO, "Error: Can't allocate memory\n");
        exit(98);
    }

    bytesRead = read(fileDescriptor, header, sizeof(Elf64_Ehdr));
    if (bytesRead == -1) {
        free(header);
        closeFile(fileDescriptor);
        dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
        exit(98);
    }

    checkElf(header->e_ident);
    printf("ELF Header:\n");
    displayMagic(header->e_ident);
    displayClass(header->e_ident);
    displayData(header->e_ident);
    displayVersion(header->e_ident);
    displayOsAbi(header->e_ident);
    displayAbi(header->e_ident);
    displayType(header->e_type, header->e_ident);
    displayEntryPoint(header->e_entry, header->e_ident);

    free(header);
    closeFile(fileDescriptor);
    return 0;
}

