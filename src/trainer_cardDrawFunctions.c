#include "../include/trainer_cardDrawFunctions.h"
#include <curses.h>
#include <stdlib.h>
#include <string.h>

static const char *cardBackArt[] = {
    "╭──────────╮", "│▚▞▚▞▚▞▚▞▚▞│", "│▞▚▞▚▞▚▞▚▞▚│",
    "│▚▞▚▞▚▞▚▞▚▞│", "│▞▚▞▚▞▚▞▚▞▚│", "│▚▞▚▞▚▞▚▞▚▞│",
    "│▞▚▞▚▞▚▞▚▞▚│", "│▚▞▚▞▚▞▚▞▚▞│", "╰──────────╯",
};

static const char *cardTemplateArt[] = {
    "╭──────────╮", "│  · · · · │",                 /* rank at 1,1 */
    "│ · · · · ·│", "│· · · · · │", "│ · ·   · ·│", /* suit at 4, 5 */
    "│· · · · · │", "│ · · · · ·│", "│· · · ·   │", /* rank at 7,10 */
    "╰──────────╯",
};

static const char *rankPool[] = {
    "A", "2", "3", "4", "5", "6", "7", "8", "9", "10",
};

static const char *suitPool[] = {
    "♠",
    "♥",
    "♦",
    "♣",
};

Card generateDealerUpCard() {
  Card dealerUpCard;

  dealerUpCard.rank = rand() % RANK_COUNT;
  dealerUpCard.suit = rand() % SUIT_COUNT;

  return dealerUpCard;
}

Card generatePlayerCard() {
  Card playerCard;

  playerCard.rank = rand() % RANK_COUNT;
  playerCard.suit = rand() % SUIT_COUNT;

  return playerCard;
}

void drawCardTemplate(WINDOW *window, int y, int x, Card card) {
  for (int i = 0; i < CARD_HEIGHT; i++) {
    mvwaddstr(window, y + i, x, cardTemplateArt[i]);
  }

  mvwaddstr(window, y + 1, x + 1, rankPool[card.rank]);
  mvwaddstr(window, y + 4, x + 5, suitPool[card.suit]);
  mvwaddstr(window, y + 7, x + 11 - (int)strlen(rankPool[card.rank]),
            rankPool[card.rank]);
}

void drawCardBack(WINDOW *window, int y, int x) {
  for (int i = 0; i < CARD_HEIGHT; i++) {
    mvwaddstr(window, y + i, x, cardBackArt[i]);
  }
}
