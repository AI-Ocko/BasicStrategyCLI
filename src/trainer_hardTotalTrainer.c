#include "../include/basicStrategy.h"
#include "../include/trainer_cardDrawFunctions.h"
#include <stdlib.h>
#include <string.h>

// Dealer
// UpCard-----A------2------3------4------5------6------7------8------9-----10
Action HardTotalsH17[10][10] = {
    /*  8 */ {H, H, H, H, H, H, H, H, H, H},
    /*  9 */ {H, H, D, D, D, D, H, H, H, H},
    /* 10 */ {H, D, D, D, D, D, D, D, D, H},
    /* 11 */ {D, D, D, D, D, D, D, D, D, D},
    /* 12 */ {H, H, H, S, S, S, H, H, H, H},
    /* 13 */ {H, S, S, S, S, S, H, H, H, H},
    /* 14 */ {H, S, S, S, S, S, H, H, H, H},
    /* 15 */ {H, S, S, S, S, S, H, H, H, H},
    /* 16 */ {H, S, S, S, S, S, H, H, H, H},
    /* 17 */ {S, S, S, S, S, S, S, S, S, S}};

Action HardTotalsS17[10][10] = {
    /*  8 */ {H, H, H, H, H, H, H, H, H, H},
    /*  9 */ {H, H, D, D, D, D, H, H, H, H},
    /* 10 */ {H, D, D, D, D, D, D, D, D, H},
    /* 11 */ {H, D, D, D, D, D, D, D, D, D},
    /* 12 */ {H, H, H, S, S, S, H, H, H, H},
    /* 13 */ {H, S, S, S, S, S, H, H, H, H},
    /* 14 */ {H, S, S, S, S, S, H, H, H, H},
    /* 15 */ {H, S, S, S, S, S, H, H, H, H},
    /* 16 */ {H, S, S, S, S, S, H, H, H, H},
    /* 17 */ {S, S, S, S, S, S, S, S, S, S}};

static const char *hardTotalActions[] = {
    "Hit",
    "Stand",
    "Double",
};

static const int numberOfUserActions =
    sizeof(hardTotalActions) / sizeof(hardTotalActions[0]);

Card generatePlayerCardOne() {
  Card playerCardOne;

  playerCardOne.rank = (rand() % 9) + 1;
  playerCardOne.suit = rand() % SUIT_COUNT;

  return playerCardOne;
}
Card generatePlayerCardTwo(Card playerCardOne) {
  Card playerCardTwo;

  // Check max card total, make sure it is between 8-17
  do {
    if (playerCardOne.rank == 9) {
      playerCardTwo.rank = rand() % 6 + 1;
    } else if (playerCardOne.rank == 8) {
      playerCardTwo.rank = rand() % 7 + 1;
    } else if (playerCardOne.rank == 7) {
      playerCardTwo.rank = rand() % 8 + 1;
    } else {
      playerCardTwo.rank = rand() % 9 + 1;
    }
  } while (playerCardTwo.rank == playerCardOne.rank ||
           (playerCardOne.rank + 1) + (playerCardTwo.rank + 1) <= 7);
  playerCardTwo.suit = rand() % SUIT_COUNT;

  return playerCardTwo;
}

static void drawTrainerWindow(WINDOW *window, int selection,
                              int currentWindowWidth, int playerTotal,
                              Card dealerUpCard, Card playerCardOne,
                              Card playerCardTwo) {
  werase(window);
  box(window, 0, 0);

  // Title
  printCenteredText(window, 0, currentWindowWidth, "Hard Total Trainer");

  // Draw dealer upcard
  drawCardBack(window, 2, ((currentWindowWidth - CARD_WIDTH) / 2) + 4);
  drawCardTemplate(window, 2, ((currentWindowWidth - CARD_WIDTH) / 2) - 4,
                   dealerUpCard);

  // Draw player soft total
  drawCardTemplate(window, 17, ((currentWindowWidth - CARD_WIDTH) / 2) - 3,
                   playerCardOne);
  drawCardTemplate(window, 14, ((currentWindowWidth - CARD_WIDTH) / 2) + 3,
                   playerCardTwo);

  // Prompt
  mvwprintw(window, 20, 20, "You have a total of %d.", playerTotal);
  printCenteredText(window, 28, currentWindowWidth, "Hit, Stand, or Double?");

  // Print User Actions
  //
  // Get starting column based on ((width of window)-(length of multiple
  // strings))/2 for centered position
  int totalWidth = 0;
  int textSpacing = 4;
  for (int i = 0; i < numberOfUserActions; i++) {
    totalWidth += (int)strlen(hardTotalActions[i]);
    if (i > 0)
      totalWidth += textSpacing;
  }
  int col = (currentWindowWidth - totalWidth) / 2;
  if (col < 0)
    col = 0;

  for (int i = 0; i < numberOfUserActions; i++) {
    if (i == selection)
      wattron(window, A_STANDOUT);
    mvwaddstr(window, getmaxy(window) * 3 / 4, col, hardTotalActions[i]);
    if (i == selection)
      wattroff(window, A_STANDOUT);
    col += (int)strlen(hardTotalActions[i]) +
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

int hardTotalTrainer(WINDOW *window, Score *score, Settings *settings) {
  int selection = 0, keyPress;

  // Draw Trainer Window
  Card dealerUpCard = generateDealerUpCard();
  Card playerCardOne = generatePlayerCardOne();
  Card playerCardTwo = generatePlayerCardTwo(playerCardOne);
  int playerTotal = ((playerCardOne.rank + 1) + (playerCardTwo.rank + 1));
  drawTrainerWindow(window, selection, getmaxx(window), playerTotal,
                    dealerUpCard, playerCardOne, playerCardTwo);
  keypad(window, TRUE);

  // Get User Input
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

      Action correctAnswer =
          settings->h17OrS17 == 'H'
              ? HardTotalsH17[playerTotal - 8][dealerUpCard.rank]
              : HardTotalsS17[playerTotal - 8][dealerUpCard.rank];

      int correctOption;
      switch (correctAnswer) {
      case H:
        correctOption = 0;
        break;
      case S:
        correctOption = 1;
        break;
      case D:
        correctOption = 2;
        break;
      default:
        correctOption = 1;
        break;
      }
      score->total++;
      if (correctOption == selection) {
        printCenteredText(window, 30, getmaxx(window), "Correct!");
        score->correct++;
        wgetch(window);
      } else {
        mvwprintw(window, 30, 40, "Incorrect. The answer is: %s",
                  hardTotalActions[correctOption]);
        wgetch(window);
      }

      dealerUpCard = generateDealerUpCard();
      playerCardOne = generatePlayerCardOne();
      playerCardTwo = generatePlayerCardTwo(playerCardOne);
      selection = 0;
      break;
    }
    }
    playerTotal = (playerCardOne.rank) + 1 + (playerCardTwo.rank + 1);
    drawTrainerWindow(window, selection, getmaxx(window), playerTotal,
                      dealerUpCard, playerCardOne, playerCardTwo);
  }

  werase(window);
  wrefresh(window);

  return 1;
};
