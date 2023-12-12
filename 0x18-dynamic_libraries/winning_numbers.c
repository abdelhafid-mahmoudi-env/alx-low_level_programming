#include <stdio.h>

int generate_winning_numbers(int *numbers) {
  for (int i = 0; i < 5; ++i) {
   	 numbers[i] = 9 + i;
  }
  numbers[5] = 9;
  return 0;
}
