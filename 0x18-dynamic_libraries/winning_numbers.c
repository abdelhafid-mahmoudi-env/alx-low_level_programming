#include <stdio.h>

static int numbers[] = {9, 8, 10, 24, 75, 9};
static int idx = 0;

int rand() {
    if (idx < 5) {
        return numbers[idx++];
    } else {
        idx = 0;
        return numbers[5];
    }
}

void srand(unsigned int seed) {
 
}
