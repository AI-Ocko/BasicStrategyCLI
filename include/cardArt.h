#ifndef CARDART_H
#define CARDART_H

#include "basicStrategy.h"
#include "init_scr.h"
#include <curses.h>

#define CARD_HEIGHT 9
#define CARD_WIDTH 12

typedef enum {
  RANK_A,
  RANK_2,
  RANK_3,
  RANK_4,
  RANK_5,
  RANK_6,
  RANK_7,
  RANK_8,
  RANK_9,
  RANK_10,
  RANK_COUNT
} Rank;

typedef enum { SPADES, HEARTS, DIAMONDS, CLUBS, SUIT_COUNT } Suit;

typedef struct {
  Rank rank;
  Suit suit;
} Card;

void drawCardTemplate(WINDOW *window, int y, int x, Card card);
void drawCardBack(WINDOW *window, int y, int x);

Card generateDealerUpCard();
Card generatePlayerCard();
Card generateAceCard();

#endif
