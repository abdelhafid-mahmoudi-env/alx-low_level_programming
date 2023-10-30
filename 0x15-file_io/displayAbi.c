#include <stdio.h>
#include "main.h"

void displayAbi(unsigned char *e_ident) {
    printf("  ABI Version:                       %d\n", e_ident[EI_ABIVERSION]);
}

