#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

void closeFile(int fileDescriptor) {
    if (close(fileDescriptor) == -1) {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fileDescriptor);
        exit(98);
    }
}

