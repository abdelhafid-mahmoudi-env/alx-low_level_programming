#include <stdio.h>
#include "main.h"

void displayMagic(unsigned char *e_ident) {
    int index;
    printf("  Magic:   ");
    for (index = 0; index < EI_NIDENT; index++) {
        printf("%02x", e_ident[index]);
        if (index == EI_NIDENT - 1)
            printf("\n");
        else
            printf(" ");
    }
}

