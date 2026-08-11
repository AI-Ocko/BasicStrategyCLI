#include "../include/cardArt.h"
#include <curses.h>
#include <string.h>

static const char *cardBackArt[] = {
    "╭──────────╮", "│▚▞▚▞▚▞▚▞▚▞│", "│▞▚▞▚▞▚▞▚▞▚│",
    "│▚▞▚▞▚▞▚▞▚▞│", "│▞▚▞▚▞▚▞▚▞▚│", "│▚▞▚▞▚▞▚▞▚▞│",
    "│▞▚▞▚▞▚▞▚▞▚│", "│▚▞▚▞▚▞▚▞▚▞│", "╰──────────╯",
};

static const char *cardTemplateArt[] = {
    "╭──────────╮", "│  · · · · │",                 /* rank at 1,1 */
    "│ · · · · ·│", "│· · · · · │", "│ · ·   · ·│", /* suit at 4, 6 */
    "│· · · · · │", "│ · · · · ·│", "│· · · ·   │", /* rank at 7,10 */
    "╰──────────╯",
};

void drawCardTemplate(WINDOW *window, int y, int x, Card card) {
  for (int i = 0; i < CARD_HEIGHT; i++) {
    mvwaddstr(window, y + i, x, cardTemplateArt[i]);
  }

  mvwaddstr(window, y + 1, x + 1, card.rank);
  mvwaddstr(window, y + 4, x + 6, card.suit);
  mvwaddstr(window, y + 7, x + 11 - (int)strlen(card.rank), card.rank);
}

void drawCardBack(WINDOW *window, int y, int x) {
  for (int i = 0; i < CARD_HEIGHT; i++) {
    mvwaddstr(window, y + i, x, cardBackArt[i]);
  }
}
