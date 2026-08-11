#include "../include/basicStrategy.h"
#include "../include/cardArt.h"
#include "../include/init_scr.h"
#include <ctype.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>

// Dealer
// UpCard-----A------2------3------4------5------6------7------8------9-----10
Action PairSplitting[10][10] = {
    /* A,A */ {Y, Y, Y, Y, Y, Y, Y, Y, Y, Y},
    /* 2,2 */ {N, YN, YN, Y, Y, Y, Y, N, N, N},
    /* 3,3 */ {N, YN, YN, Y, Y, Y, Y, N, N, N},
    /* 4,4 */ {N, N, N, N, YN, YN, N, N, N, N},
    /* 5,5 */ {N, N, N, N, N, N, N, N, N, N},
    /* 6,6 */ {N, YN, Y, Y, Y, Y, N, N, N, N},
    /* 7,7 */ {N, Y, Y, Y, Y, Y, Y, N, N, N},
    /* 8,8 */ {Y, Y, Y, Y, Y, Y, Y, Y, Y, Y},
    /* 9,9 */ {N, Y, Y, Y, Y, Y, N, Y, Y, N},
    /* 10,10 */ {N, N, N, N, N, N, N, N, N, N},
};

int surrender[3][10] = {
    /* 14 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    /* 15 */ {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    /* 16 */ {0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
};

const char *UserAction[] = {
    "Split",
    "Don't Split",
};

static const int numberOfUserActions =
    sizeof(UserAction) / sizeof(UserAction[0]);

static void drawTrainerWindow(WINDOW *window, int selection,
                              int currentWindowWidth) {
  werase(window);
  box(window, 0, 0);
  printCenteredText(window, 0, currentWindowWidth, "Pair Splitting Trainer");
  printCenteredText(window, 28, currentWindowWidth, "Do you split?");

  // Get starting column based on (width of window - length of multiple strings)
  // / 2 for centered position
  int totalWidth = 0;
  int textSpacing = 4;
  for (int i = 0; i < numberOfUserActions; i++) {
    totalWidth += (int)strlen(UserAction[i]);
    if (i > 0)
      totalWidth += textSpacing;
  }
  int col = (currentWindowWidth - totalWidth) / 2;
  if (col < 0)
    col = 0;

  // Print User Actions
  for (int i = 0; i < numberOfUserActions; i++) {
    if (i == selection)
      wattron(window, A_STANDOUT);
    mvwprintw(window, getmaxy(window) * 3 / 4, col, UserAction[i]);
    if (i == selection)
      wattroff(window, A_STANDOUT);
    col += (int)strlen(UserAction[i]) +
           textSpacing; /* increment starting column for next loop*/
  }
  wattron(window, A_DIM);
  printCenteredText(window, getmaxy(window) - 4, currentWindowWidth,
                    "h/l or left/right to move     Enter to select");
  printCenteredText(window, getmaxy(window) - 3, currentWindowWidth,
                    "q to quit");
  wattroff(window, A_DIM);
  wrefresh(window);
}

int pairSplittingTrainer(WINDOW *window, Score *score, Settings *settings) {
  int selection = 0, keyPress;
  drawTrainerWindow(window, selection, getmaxx(window));
  keypad(window, TRUE);

  for (int i = 0;
       i < (int)(sizeof(templateCardArt) / sizeof(templateCardArt[0])); i++) {
    mvwaddstr(window, i + 1, 2, templateCardArt[i]);
  }

  // draw dealerUpCard
  // // Generate random pair and dealerUpCard
  // int dealerUpCard = dealDealerUpCard();
  // int playerPair = (rand() % 10) + 1;
  //
  // draw PlayerPair

  while ((keyPress = wgetch(window)) != 'q') {
    switch (keyPress) {
    case 'h':
    case KEY_LEFT:
      if (selection > 0)
        selection--;
      break;
    case 'l':
    case KEY_RIGHT:
      if (selection < numberOfUserActions - 1)
        selection++;
      break;
    case '\n':
    case '\r':
    case KEY_ENTER:
    }
    drawTrainerWindow(window, selection, getmaxx(window));
  }

  werase(window);
  wrefresh(window);

  // char printPlayerPair;
  // char userAnswer;
  // char correctAnswer;
  //
  //
  // // typecasting for converting a randomly generated '1' into an 'A'
  // if (playerPair == 1) {
  //   printPlayerPair = 'A';
  // } else {
  //   printPlayerPair = playerPair;
  // }
  //
  // werase(window);
  // box(window, 0, 0);
  // wrefresh(window);
  //
  // // Print messages
  // if (printPlayerPair == 'A') {
  //   mvwprintw(window, SCREEN_LINE_1, SCREEN_MARGIN, "You have a pair of
  //   %c's!",
  //             printPlayerPair);
  //   wrefresh(window);
  // } else {
  //   mvwprintw(window, SCREEN_LINE_1, SCREEN_MARGIN, "You have a pair of
  //   %d's!",
  //             printPlayerPair);
  //   wrefresh(window);
  // }
  //
  // printDealerUpCard(window, dealerUpCard); // prints on SCREEN_LINE_2
  //
  // // Get user choice
  // mvwprintw(window, SCREEN_LINE_3, SCREEN_MARGIN,
  //           "Do you split? (Y)es, (N)o, or (Q)uit: ");
  // wrefresh(window);
  // userAnswer = wgetch(window);
  //
  // // exit
  // if (toupper(userAnswer) == 'Q') {
  //   return 0;
  // }
  //
  // // Check misinput ("It was a misinput it was A MISINPUT... CALM DOWN,
  // // YOU CALM THE FUCK DOWN")
  // while (userAnswer != 'y' && userAnswer != 'n') {
  //   mvwprintw(window, SCREEN_LINE_7, SCREEN_MARGIN,
  //             "Invalid input... please answer again.");
  //   userAnswer = wgetch(window);
  //   mvwprintw(window, SCREEN_LINE_7, SCREEN_MARGIN,
  //             "                                     ");
  // }
  //
  // // Check correct answer
  // correctAnswer = answerToChar(
  //     window, PairSplitting[playerPair - 1][dealerUpCard - 1], settings);
  //
  // // Compare correct answer with user answer
  // checkAndScore(window, score, correctAnswer, userAnswer);

  return 1;
}
