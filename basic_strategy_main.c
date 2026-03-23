#include "basic_strategy.h"
#include <stdio.h>

int main() {

  int playerTotal;
  printf("Enter a total: ");
  scanf("%d", &playerTotal);
  printf("%d\n", playerTotal);
  if (playerTotal > 17) {
    printf("Stand");
  } else if (playerTotal < 8) {
    printf("Hit");
  } else {
    printf("idek");
  }

  return 0;
}
