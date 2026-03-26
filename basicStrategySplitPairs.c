#include "basic_strategy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));

  int dealerUpCard = (rand() % 9) + 1;
  int playerPair = (rand() % 9) + 1;
  char printPlayerPair;
  char printDealerUpCard;
  char userAnswer;
  char correctAnswer;

  // typecasting for converting a randomly generated '1' into an 'A'
  if (playerPair == 1) {
    printPlayerPair = 'A';
  } else {
    printPlayerPair = playerPair;
  }
  if (dealerUpCard == 1) {
    printDealerUpCard = 'A';
  } else {
    printDealerUpCard = dealerUpCard;
  }

  // Print messages
  if (printPlayerPair == 'A') {
    printf("You have a pair of %c's!\n", printPlayerPair);
  } else {
    printf("You have a pair of %d's!\n", printPlayerPair);
  }
  if (printDealerUpCard == 'A') {
    printf("Dealer's up card is %c\n", printDealerUpCard);
  } else {
    printf("Dealer's up card is %d\n", printDealerUpCard);
  }

  // Get user choice
  printf("Do you split? (Y)es or (N)o: ");
  scanf("%c", &userAnswer);

  // Check the actual correct answer
  if (PairSplitting[playerPair - 1][dealerUpCard - 1] == Y) {
    correctAnswer = 'Y';
  } else {
    correctAnswer = 'N';
  }

  // Compare
  if (correctAnswer == userAnswer) {
    printf("Correct!");
  } else {
    printf("Incorrect!");
  }

  return 0;
}
