#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void checkElf(unsigned char *e_ident);
void displayHeaderInfo(unsigned char *e_ident, unsigned int e_type, unsigned long int e_entry);
void manageFile(int *fileDescriptor, char *filePath, Elf64_Ehdr **header);
void closeAndExit(int fileDescriptor, Elf64_Ehdr *header, char *message);

void checkElf(unsigned char *e_ident) {
    for (int index = 0; index < 4; index++) {
        if (e_ident[index] != 127 &&
            e_ident[index] != 'E' &&
            e_ident[index] != 'L' &&
            e_ident[index] != 'F') {
            dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
            exit(98);
        }
    }
}

void displayHeaderInfo(unsigned char *e_ident, unsigned int e_type, unsigned long int e_entry) {
    printf("  Magic:   ");
    for (int index = 0; index < EI_NIDENT; index++) {
        printf("%02x", e_ident[index]);
        printf(index == EI_NIDENT - 1 ? "\n" : " ");
    }
}

void manageFile(int *fileDescriptor, char *filePath, Elf64_Ehdr **header) {
    *fileDescriptor = open(filePath, O_RDONLY);
    if (*fileDescriptor == -1) {
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", filePath);
        exit(98);
    }

    *header = malloc(sizeof(Elf64_Ehdr));
    if (*header == NULL) {
        closeAndExit(*fileDescriptor, NULL, "Error: Can't read file");
    }

    int bytesRead = read(*fileDescriptor, *header, sizeof(Elf64_Ehdr));
    if (bytesRead == -1) {
        closeAndExit(*fileDescriptor, *header, "Error: No such file");
    }
}

void closeAndExit(int fileDescriptor, Elf64_Ehdr *header, char *message) {
    if (header) {
        free(header);
    }
    if (close(fileDescriptor) == -1) {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fileDescriptor);
    }
    if (message) {
        dprintf(STDERR_FILENO, "Error: %s\n", message);
    }
    exit(98);
}

int main(int argc, char *argv[]) {
    Elf64_Ehdr *header;
    int fileDescriptor;

    if (argc != 2) {
        dprintf(STDERR_FILENO, "Usage: %s <elf_file>\n", argv[0]);
        exit(98);
    }

    manageFile(&fileDescriptor, argv[1], &header);

    checkElf(header->e_ident);
    printf("ELF Header:\n");
    displayHeaderInfo(header->e_ident, header->e_type, header->e_entry);

    closeAndExit(fileDescriptor, header, NULL);
    return 0;
}

