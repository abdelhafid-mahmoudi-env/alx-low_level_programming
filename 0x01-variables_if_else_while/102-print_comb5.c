#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: Always 0
 */

int main() {
    int i, j;

    for (i = 0; i <= 98; i++) {
        for (j = i + 1; j <= 99; j++) {
            // Extract the tens and ones digits for i and j
            int tens_i = i / 10;
            int ones_i = i % 10;
            int tens_j = j / 10;
            int ones_j = j % 10;

            // Print the first two-digit number
            putchar('0' + tens_i);
            putchar('0' + ones_i);
            putchar(' ');

            // Print the second two-digit number
            putchar('0' + tens_j);
            putchar('0' + ones_j);

            // Print a comma and a space to separate combinations
            if (i != 98 || j != 99) {
                putchar(',');
                putchar(' ');
            }
        }
    }

    return 0;
}
