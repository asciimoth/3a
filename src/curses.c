#include "curses.h"

short curs_color(int fg){
    switch (7 & fg) {           /* RGB */
    case 0:                     /* 000 */
        return (COLOR_BLACK);
    case 1:                     /* 001 */
        return (COLOR_BLUE);
    case 2:                     /* 010 */
        return (COLOR_GREEN);
    case 3:                     /* 011 */
        return (COLOR_CYAN);
    case 4:                     /* 100 */
        return (COLOR_RED);
    case 5:                     /* 101 */
        return (COLOR_MAGENTA);
    case 6:                     /* 110 */
        return (COLOR_YELLOW);
    case 7:                     /* 111 */
        return (COLOR_WHITE);
    }
}

int colornum(int fg, int bg){
    int B, bbb, ffff;

    B = 1 << 7;
    bbb = (7 & bg) << 4;
    ffff = 7 & fg;

    return (B | bbb | ffff);
}

void init_colorpairs(void){
    int fg, bg;
    int colorpair;

    for (bg = 0; bg <= 7; bg++) {
        for (fg = 0; fg <= 7; fg++) {
            colorpair = colornum(fg, bg);
            init_pair(colorpair, curs_color(fg), curs_color(bg));
        }
    }
}

int is_bold(int fg){
    /* return the intensity bit */

    int i;

    i = 1 << 3;
    return (i & fg);
}

void setcolor(int fg, int bg){
    /* set the color pair (colornum) and bold/bright (A_BOLD) */
    attron(COLOR_PAIR(colornum(fg, bg)));
    if (is_bold(fg)) {
        attron(A_BOLD);
    }
}

void unsetcolor(int fg, int bg){
    /* unset the color pair (colornum) and bold/bright (A_BOLD) */
    attroff(COLOR_PAIR(colornum(fg, bg)));
    if (is_bold(fg)) {
        attroff(A_BOLD);
    }
}

char to_hex(unsigned char value){
    switch(value){
        case(0): return '0';
        case(1): return '1';
        case(2): return '2';
        case(3): return '3';
        case(4): return '4';
        case(5): return '5';
        case(6): return '6';
        case(7): return '7';
        case(8): return '8';
        case(9): return '9';
        case(10): return 'a';
        case(11): return 'b';
        case(12): return 'c';
        case(13): return 'd';
        case(14): return 'e';
    }
    return 'f';
}

unsigned char from_hex(char symbol){
    switch(symbol){
        case('0'): return 0;
        case('1'): return 1;
        case('2'): return 2;
        case('3'): return 3;
        case('4'): return 4;
        case('5'): return 5;
        case('6'): return 6;
        case('7'): return 7;
        case('8'): return 8;
        case('9'): return 9;
        case('a'): return 10;
        case('b'): return 11;
        case('c'): return 12;
        case('d'): return 13;
        case('e'): return 14;
    }
    return 15;
}

void init_curses(bool colors){
    /* initialize curses */
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    /* initialize colors */
    if (colors){
        if (has_colors() == FALSE) {
            endwin();
            puts("Your terminal does not support color");
            exit(1);
        }
        start_color();
        init_colorpairs();
    }
}

void colordemo(){
    init_curses(true);
    int fg, bg;
    mvaddstr(0, 21, "COLOR TABLE");
    mvaddstr(1, 5, "Firs letter - foreground, second - background");
    char str[] = " __ ";
    for (bg = 0; bg <= 7; bg++) {
        for (fg = 0; fg <= 7; fg++) {
            setcolor(fg, bg);
            str[1] = to_hex(fg);
            str[2] = to_hex(bg);
            mvaddstr(fg + 3, bg * 4, str);
        }
        for (fg = 8; fg <= 15; fg++) {
            setcolor(fg, bg);
            str[1] = to_hex(fg);
            str[2] = to_hex(bg);
            mvaddstr(fg + 3 - 8, 24 + bg * 4, str);
        }
    }
    refresh();
    getch();
    endwin();
}

void render_ncurses(struct params *params, char *animation){
    init_curses(params->colors > 0);
    size_t len = strlen(animation); //size of animation
    unsigned char colors = params->colors;
    unsigned short width = params->width;
    unsigned short height = params->height;
    unsigned short datacols = params->datacols;
    unsigned int delay = params->delay * 1000;
    int lux, luy = 0; //left up corner of animation position
    do{
        size_t frame = 0;
        bool next_frame = true;
        while(next_frame){
            for(int x=0; x<params->width; x++){
                for(int y=0; y<params->height; y++){
                    size_t symbol_position, fg_color_position, bg_color_position = 0;
                    symbol_position = (frame*width*datacols*height)+(y*width*datacols)+x;
                    if (symbol_position >= len){
                        next_frame = false;
                        break;
                    }
                    switch(params->colors){
                        case (1):{
                            fg_color_position = (frame*width*datacols*height)+(y*width*datacols)+width+x;
                            if (fg_color_position >= len){
                                next_frame = false;
                                break;
                            }
                            unsigned char fg = from_hex(animation[fg_color_position]);
                            setcolor(fg, 0);
                            break;
                        }
                        case (2):{                            
                            bg_color_position = (frame*width*datacols*height)+(y*width*datacols)+width+x;
                            if (bg_color_position >= len){
                                next_frame = false;
                                break;
                            }
                            unsigned char bg = from_hex(animation[bg_color_position]);
                            setcolor(15, bg);
                            break;
                        }
                        case (3):{
                            fg_color_position = (frame*width*datacols*height)+(y*width*datacols)+width+x;
                            bg_color_position = (frame*width*datacols*height)+(y*width*datacols)+width*2+x;
                            if (fg_color_position >= len || bg_color_position >= len){
                                next_frame = false;
                                break;
                            }
                            unsigned char fg = from_hex(animation[fg_color_position]);
                            unsigned char bg = from_hex(animation[bg_color_position]);
                            setcolor(fg, bg);
                            break;
                        }
                    }
                    mvaddch(luy+y,lux+x, animation[symbol_position]);
                }
            }
            refresh();
            frame++;
            usleep(delay);
        }
    }while(params->loop);
    endwin();
}
