#include "../include/basicStrategy.h"
#include "../include/cardArt.h"
#include <curses.h>
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

static const char *pairSplittingActions[] = {
    "Split",
    "Don't Split",
};

static const int numberOfUserActions =
    sizeof(pairSplittingActions) / sizeof(pairSplittingActions[0]);

static void drawTrainerWindow(WINDOW *window, int selection,
                              int currentWindowWidth, Card dealerUpCard,
                              Card playerCard) {
  werase(window);
  box(window, 0, 0);

  // Title
  printCenteredText(window, 0, currentWindowWidth, "Pair Splitting Trainer");

  // Draw dealer upcard
  drawCardBack(window, 2, ((currentWindowWidth - CARD_WIDTH) / 2) + 4);
  drawCardTemplate(window, 2, ((currentWindowWidth - CARD_WIDTH) / 2) - 4,
                   dealerUpCard);

  // Draw player pair
  drawCardTemplate(window, 17, ((currentWindowWidth - CARD_WIDTH) / 2) - 3,
                   playerCard);
  drawCardTemplate(window, 14, ((currentWindowWidth - CARD_WIDTH) / 2) + 3,
                   playerCard);

  // Prompt
  printCenteredText(window, 28, currentWindowWidth, "Do you split?");

  // Print User Actions
  //
  // Get starting column based on ((width of window)-(length of multiple
  // strings))/2 for centered position
  int totalWidth = 0;
  int textSpacing = 4;
  for (int i = 0; i < numberOfUserActions; i++) {
    totalWidth += (int)strlen(pairSplittingActions[i]);
    if (i > 0)
      totalWidth += textSpacing;
  }
  int col = (currentWindowWidth - totalWidth) / 2;
  if (col < 0)
    col = 0;

  for (int i = 0; i < numberOfUserActions; i++) {
    if (i == selection)
      wattron(window, A_STANDOUT);
    mvwaddstr(window, getmaxy(window) * 3 / 4, col, pairSplittingActions[i]);
    if (i == selection)
      wattroff(window, A_STANDOUT);
    col += (int)strlen(pairSplittingActions[i]) +
           textSpacing; /* increment starting column for next loop*/
  }

  // Print hints
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

  // Draw trainer window
  Card dealerUpCard = generateDealerUpCard();
  Card playerCard = generatePlayerCard();
  drawTrainerWindow(window, selection, getmaxx(window), dealerUpCard,
                    playerCard);
  keypad(window, TRUE);

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
    case KEY_ENTER: {

      Action correctAnswer = PairSplitting[playerCard.rank][dealerUpCard.rank];

      int correctOption;
      if (correctAnswer == Y) {
        correctOption = 0;
      } else if (correctAnswer == N) {
        correctOption = 1;
      } else {
        correctOption = settings->doubleAfterSplit == 'Y' ? 0 : 1;
      }

      score->total++;
      if (correctOption == selection) {
        printCenteredText(window, 30, getmaxx(window), "Correct!");
        // mvwprintw(window, 15, 20, "Correct!");
        score->correct++;
        wgetch(window);
      } else {
        mvwprintw(window, 30, 40, "Incorrect. The answer is: %s",
                  pairSplittingActions[correctOption]);
        wgetch(window);
      }

      dealerUpCard = generateDealerUpCard();
      playerCard = generatePlayerCard();
      selection = 0;
      break;
    }
    }
    drawTrainerWindow(window, selection, getmaxx(window), dealerUpCard,
                      playerCard);
  }

  werase(window);
  wrefresh(window);

  return 1;
}
