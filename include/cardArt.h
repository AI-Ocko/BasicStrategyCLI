#ifndef CARDART_H
#define CARDART_H

#include <curses.h>

#define CARD_HEIGHT 9
#define CARD_WIDTH 12

typedef struct {
  const char *rank;
  const char *suit;
} Card;

void drawCardTemplate(WINDOW *window, int y, int x, Card card);
void drawCardBack(WINDOW *window, int y, int x);

#endif
