#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "format.h"

#ifndef curses_h
#define curses_h

short curs_color(int fg);

int colornum(int fg, int bg);

void init_colorpairs(void);

int is_bold(int fg);

void setcolor(int fg, int bg);

void unsetcolor(int fg, int bg);

char to_hex(unsigned char value);

unsigned char from_hex(char symbol);

void init_curses(bool colors);

void colordemo();

void render_ncurses(struct params *params, char *animation);

#endif
