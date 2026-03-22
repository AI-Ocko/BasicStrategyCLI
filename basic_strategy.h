#include <stdio.h>

typedef enum {

  H = 0,
  S = 1,
  D = 2,
  Ds = 3,
  N = 4,
  Y = 5,
  YN = 6,
  Surr = 7

} Action;

// Dealer High Card  2      3      4      5      6      7      8      9     10 A

Action HardTotals[10][10] = {
    /*  8 */ {H, H, H, H, H, H, H, H, H, H},
    /*  9 */ {H, D, D, D, D, H, H, H, H, H},
    /* 10 */ {D, D, D, D, D, D, D, D, H, H},
    /* 11 */ {D, D, D, D, D, D, D, D, D, D},
    /* 12 */ {H, H, S, S, S, H, H, H, H, H},
    /* 13 */ {S, S, S, S, S, H, H, H, H, H},
    /* 14 */ {S, S, S, S, S, H, H, H, H, H},
    /* 15 */ {S, S, S, S, S, H, H, H, H, H},
    /* 16 */ {S, S, S, S, S, H, H, H, H, H},
    /* 17 */ {S, S, S, S, S, S, S, S, S, S}};

Action SoftTotals[8][10] = {
    /* A,2 */ {H, H, H, D, D, H, H, H, H, H},
    /* A,3 */ {H, H, H, D, D, H, H, H, H, H},
    /* A,5 */ {H, H, D, D, D, H, H, H, H, H},
    /* A,5 */ {H, H, D, D, D, H, H, H, H, H},
    /* A,6 */ {H, D, D, D, D, H, H, H, H, H},
    /* A,7 */ {Ds, Ds, Ds, Ds, Ds, S, S, H, H, H},
    /* A,8 */ {S, S, S, S, Ds, S, S, S, S, S},
    /* A,9 */ {S, S, S, S, S, S, S, S, S, S}};

Action PairSplitting[10][10] = {
    /* 2,2 */ {YN, YN, Y, Y, Y, Y, N, N, N, N},
    /* 3,3 */ {YN, YN, Y, Y, Y, Y, N, N, N, N},
    /* 4,4 */ {N, N, N, YN, YN, N, N, N, N, N},
    /* 5,5 */ {N, N, N, N, N, N, N, N, N, N},
    /* 6,6 */ {YN, Y, Y, Y, Y, N, N, N, N, N},
    /* 7,7 */ {Y, Y, Y, Y, Y, Y, N, N, N, N},
    /* 8,8 */ {Y, Y, Y, Y, Y, Y, Y, Y, Y, Y},
    /* 9,9 */ {Y, Y, Y, Y, Y, N, Y, Y, N, N},
    /* 10,10 */ {N, N, N, N, N, N, N, N, N, N},
    /* A,A */ {Y, Y, Y, Y, Y, Y, Y, Y, Y, Y},
};

int surrender[3][10] = {
    /* 14 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    /* 15 */ {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    /* 16 */ {0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
};
