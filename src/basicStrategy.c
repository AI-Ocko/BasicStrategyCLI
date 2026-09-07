#include "../include/basicStrategy.h"
#include <curses.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

WINDOW *centerWindow(int nlines, int ncols) {
  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);
  return newwin(nlines, ncols, (yMax - nlines) / 2, (xMax - ncols) / 2);
}

void printCenteredText(WINDOW *window, int row, int windowWidth,
                       const char *text) {
  int col = (windowWidth - (int)strlen(text)) / 2;
  if (col < 0)
    col = 0;
  mvwprintw(window, row, col, "%s", text);
}

static const struct {
  const char *optionsName;
} Options[] = {
    {"Pair Splitting"}, {"Soft Totals"}, {"Hard Totals"},
    {"Full Game"},      {"Settings"},
};

static const int numberOfOptions = sizeof(Options) / sizeof(Options[0]);

static void drawMainMenu(WINDOW *window, int selection,
                         int currentWindowWidth) {
  werase(window);
  box(window, 0, 0);
  printCenteredText(window, 0, currentWindowWidth, "Main Menu");
  for (int i = 0; i < numberOfOptions; i++) {
    if (i == selection)
      wattron(window, A_STANDOUT);
    printCenteredText(window, i * 2 + 6, currentWindowWidth,
                      Options[i].optionsName);
    if (i == selection)
      wattroff(window, A_STANDOUT);
  }
  wattron(window, A_DIM);
  printCenteredText(window, numberOfOptions + 14, currentWindowWidth,
                    "j/k or up/down to move     Enter to select");
  printCenteredText(window, numberOfOptions + 15, currentWindowWidth,
                    "q to quit");
  wattroff(window, A_DIM);
  wrefresh(window);
}

static const char *title[] = {
    " ____            _       _____ _             _                _______ _   "
    " _ _____ ",
    "|  _ \\          (_)     / ____| |           | |              |__   __| | "
    " | |_   _|",
    "| |_) | __ _ ___ _  ___| (___ | |_ _ __ __ _| |_ ___  __ _ _   _| |  | |  "
    "| | | |  ",
    "|  _ < / _` / __| |/ __|\\___ \\| __| '__/ _` | __/ _ \\/ _` | | | | |  | "
    "|  | | | |  ",
    "| |_) | (_| \\__ \\ | (__ ____) | |_| | | (_| | ||  __/ (_| | |_| | |  | "
    "|__| |_| |_ ",
    "|____/ \\__,_|___/_|\\___|_____/ \\__|_|  \\__,_|\\__\\___|\\__, |\\__, "
    "|_|  \\____/|_____|",
    "                                                      __/ | __/ |         "
    "         ",
    "                                                     |___/ |___/          "
    "         ",
};

void printTitle(WINDOW *window) {
  for (int i = 0; i < (int)(sizeof(title) / sizeof(title[0])); i++) {
    printCenteredText(window, i + 2, getmaxx(window), title[i]);
  }
  wrefresh(window);
}

int main(void) {
  // Initialize ncurses
  setlocale(LC_ALL, "");
  initscr();   // Start ncurses mode, creates stdscr
  cbreak();    // Disable line buffering, get input char-by-char
  noecho();    // don't echo typed keys automatically
  curs_set(0); // hides the terminal cursor

  // Initialize Settings and Score
  Settings gameSettings;
  Settings *ptrSettings = &gameSettings;
  loadSettings(ptrSettings);
  Score gameScore;
  Score *ptrScore = &gameScore;

  // Random seed
  srand(time(NULL));

  // Get screen dimensions
  int xMax, yMax;
  getmaxyx(stdscr, yMax, xMax);

  // Initialize Title window
  WINDOW *titleWindow = centerWindow(yMax, xMax);
  printTitle(titleWindow);

  // Initialie Main Menu window
  WINDOW *mainMenuWindow = centerWindow(yMax / 2, xMax / 4);
  box(mainMenuWindow, 0, 0);
  int selection = 0, keyPress;
  drawMainMenu(mainMenuWindow, 0, xMax / 4);
  keypad(mainMenuWindow, TRUE); // enable arrow keys, F-keys, etc.

  while ((keyPress = wgetch(mainMenuWindow)) != 'q') {
    switch (keyPress) {
    case 'k':
    case KEY_UP:
      if (selection > 0)
        selection--;
      break;
    case 'j':
    case KEY_DOWN:
      if (selection < numberOfOptions - 1)
        selection++;
      break;
    case '\n':
    case '\r':
    case KEY_ENTER:
      if (selection == 4) {
        drawSettingsMenu(mainMenuWindow, 0, xMax / 4, ptrSettings);
        settingsMenu(mainMenuWindow, 0, xMax / 4, ptrSettings);
      } else {
        WINDOW *trainerWindow = centerWindow(yMax - 4, xMax - 4);
        TrainerOptions[selection](trainerWindow, ptrScore, ptrSettings);
        delwin(trainerWindow);
      }
    }
    printTitle(titleWindow);
    drawMainMenu(mainMenuWindow, selection, xMax / 4);
  }

  delwin(mainMenuWindow);
  delwin(titleWindow);
  endwin();

  return 0;
}
