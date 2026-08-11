#include "../include/basicStrategy.h"
#include "../include/init_scr.h"
#include <ctype.h>
#include <curses.h>
#include <stdlib.h>

int dealDealerUpCard() { return rand() % 10 + 1; }

void printDealerUpCard(
    WINDOW *window,
    int dealerUpCard) { /* Probably will convert to drawDealerUpcard */
  if (dealerUpCard == 1) {
    mvwprintw(window, SCREEN_LINE_2, SCREEN_MARGIN, "Dealer's Up Card is A");
    wrefresh(window);
  } else {
    mvwprintw(window, SCREEN_LINE_2, SCREEN_MARGIN, "Dealer's Up Card is: %d",
              dealerUpCard);
    wrefresh(window);
  }
}

char answerToChar(WINDOW *window, Action a, Settings *settings) {
  switch (a) {
  case H:
    return 'H';
  case S:
    return 'S';
  case D:
    return 'D';
  case Ds:
    return settings->h17OrS17 == 'H' ? 'D' : 'S';
  case N:
    return 'N';
  case Y:
    return 'Y';
  case YN:
    return settings->doubleAfterSplit == 'Y' ? 'Y' : 'N';
  case Surr:
    return 's';
  default:
    mvwprintw(window, SCREEN_LINE_7, SCREEN_MARGIN,
              "Error, could not print answer.");
    return '?';
  }
}

void checkAndScore(WINDOW *window, Score *score, char correctAnswer,
                   char userAnswer) {
  score->total++;

  if (correctAnswer == toupper(userAnswer)) {
    mvwprintw(window, SCREEN_LINE_4, SCREEN_MARGIN, "Correct!");
    score->correct++;
  } else {
    mvwprintw(window, SCREEN_LINE_4, SCREEN_MARGIN,
              "Incorrect... The correct answer is: %c", correctAnswer);
  }
};
