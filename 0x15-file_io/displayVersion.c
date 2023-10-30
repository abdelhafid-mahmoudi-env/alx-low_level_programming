#include <stdio.h>
#include "main.h"

void displayVersion(unsigned char *e_ident) {
    printf("  Version:                           %d", e_ident[EI_VERSION]);
    switch (e_ident[EI_VERSION]) {
        case EV_CURRENT:
            printf(" (current)\n");
            break;
        default:
            printf("\n");
            break;
    }
}

