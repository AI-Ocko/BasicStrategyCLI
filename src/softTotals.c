#include "../include/basicStrategy.h"
#include "../include/cardArt.h"
#include <curses.h>
#include <string.h>

// Dealer
// UpCard--------------A------2------3------4------5------6------7------8------9-----10
Action SoftTotalsH17[8][10] = {
    /* A,2 */ {H, H, H, H, D, D, H, H, H, H},
    /* A,3 */ {H, H, H, H, D, D, H, H, H, H},
    /* A,4 */ {H, H, H, D, D, D, H, H, H, H},
    /* A,5 */ {H, H, H, D, D, D, H, H, H, H},
    /* A,6 */ {H, H, D, D, D, D, H, H, H, H},
    /* A,7 */ {H, Ds, Ds, Ds, Ds, Ds, S, S, H, H},
    /* A,8 */ {S, S, S, S, S, Ds, S, S, S, S},
    /* A,9 */ {S, S, S, S, S, S, S, S, S, S}};

Action SoftTotalsS17[8][10] = {
    /* A,2 */ {H, H, H, H, D, D, H, H, H, H},
    /* A,3 */ {H, H, H, H, D, D, H, H, H, H},
    /* A,4 */ {H, H, H, D, D, D, H, H, H, H},
    /* A,5 */ {H, H, H, D, D, D, H, H, H, H},
    /* A,6 */ {H, H, D, D, D, D, H, H, H, H},
    /* A,7 */ {H, S, Ds, Ds, Ds, Ds, S, S, H, H},
    /* A,8 */ {S, S, S, S, S, S, S, S, S, S},
    /* A,9 */ {S, S, S, S, S, S, S, S, S, S}};

static const char *softTotalActions[] = {
    "Hit",
    "Stand",
    "Double",
};

static const int numberOfUserActions =
    sizeof(softTotalActions) / sizeof(softTotalActions[0]);

static void drawTrainerWindow(WINDOW *window, int selection,
                              int currentWindowWidth, Card dealerUpCard,
                              Card playerCard, Card aceCard) {
  werase(window);
  box(window, 0, 0);

  // Title
  printCenteredText(window, 0, currentWindowWidth, "Pair Splitting Trainer");

  // Draw dealer upcard
  drawCardBack(window, 2, ((currentWindowWidth - CARD_WIDTH) / 2) + 4);
  drawCardTemplate(window, 2, ((currentWindowWidth - CARD_WIDTH) / 2) - 4,
                   dealerUpCard);

  // Draw player soft total
  drawCardTemplate(window, 17, ((currentWindowWidth - CARD_WIDTH) / 2) - 3,
                   aceCard);
  drawCardTemplate(window, 14, ((currentWindowWidth - CARD_WIDTH) / 2) + 3,
                   playerCard);

  // Prompt
  printCenteredText(window, 28, currentWindowWidth, "Hit, Stand, or Double?");

  // Print User Actions
  //
  // Get starting column based on ((width of window)-(length of multiple
  // strings))/2 for centered position
  int totalWidth = 0;
  int textSpacing = 4;
  for (int i = 0; i < numberOfUserActions; i++) {
    totalWidth += (int)strlen(softTotalActions[i]);
    if (i > 0)
      totalWidth += textSpacing;
  }
  int col = (currentWindowWidth - totalWidth) / 2;
  if (col < 0)
    col = 0;

  for (int i = 0; i < numberOfUserActions; i++) {
    if (i == selection)
      wattron(window, A_STANDOUT);
    mvwaddstr(window, getmaxy(window) * 3 / 4, col, softTotalActions[i]);
    if (i == selection)
      wattroff(window, A_STANDOUT);
    col += (int)strlen(softTotalActions[i]) +
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

int softTotalTrainer(WINDOW *window, Score *score, Settings *settings) {
  int selection = 0, keyPress;
  // Draw trainer window
  Card dealerUpCard = generateDealerUpCard();
  Card playerCard = generatePlayerCard();
  Card aceCard = generateAceCard();
  drawTrainerWindow(window, selection, getmaxx(window), dealerUpCard,
                    playerCard, aceCard);
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
              ? SoftTotalsH17[playerCard.rank][dealerUpCard.rank]
              : SoftTotalsS17[playerCard.rank][dealerUpCard.rank];

      int correctOption;
      if (correctAnswer == H) {
        correctOption = 0;
      } else if (correctAnswer == S) {
        correctOption = 1;
      } else if (correctAnswer == D) {
        correctOption = 2;
      } else {
        correctOption = settings->h17OrS17 == 'H' ? 0 : 1;
      }

      score->total++;
      if (correctOption == selection) {
        printCenteredText(window, 30, getmaxx(window), "Correct!");
        score->correct++;
        wgetch(window);
      } else {
        mvwprintw(window, 30, 40, "Incorrect. The answer is: %s",
                  softTotalActions[correctOption]);
        wgetch(window);
      }

      dealerUpCard = generateDealerUpCard();
      playerCard = generatePlayerCard();
      selection = 0;
      break;
    }
    }
    drawTrainerWindow(window, selection, getmaxx(window), dealerUpCard,
                      playerCard, aceCard);
  }

  werase(window);
  wrefresh(window);

  return 1;
};
