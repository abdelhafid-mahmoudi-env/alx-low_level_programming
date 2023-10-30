#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

ssize_t read_textfile(const char *filename, size_t letters);
int create_file(const char *filename, char *text_content);
int append_text_to_file(const char *filename, char *text_content);
int _putchar(char c);
int _strlen(char *str);
void checkElf(unsigned char *e_ident);
void displayMagic(unsigned char *e_ident);
void displayClass(unsigned char *e_ident);
void displayData(unsigned char *e_ident);
void displayVersion(unsigned char *e_ident);
void displayAbi(unsigned char *e_ident);
void displayOsAbi(unsigned char *e_ident);
void displayType(unsigned int e_type, unsigned char *e_ident);
void displayEntryPoint(unsigned long int e_entry, unsigned char *e_ident);
void closeFile(int fileDescriptor);

#endif /* MAIN_H */

