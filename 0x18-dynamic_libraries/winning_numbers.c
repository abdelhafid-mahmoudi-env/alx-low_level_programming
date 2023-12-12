#include <unistd.h>
#include <stdlib.h>

static int initialized = 0;
static int counter = 0;
static const int winning_numbers[] = {9, 8, 10, 24, 75, 9};
static const int winning_numbers_size = sizeof(winning_numbers) / sizeof(winning_numbers[0]);

void srand(unsigned int seed) {
    initialized = 1;
    counter = 0;
    (void)seed;
}

int rand(void) {
    if (!initialized) {
        return random();
    }

    if (counter < winning_numbers_size) {
        return winning_numbers[counter++];
    } else {
        return random();
    }
}

