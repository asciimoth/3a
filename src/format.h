#include <stdbool.h>
#include <stdio.h>

#ifndef format_h
#define format_h

#define DEFAULT_LAG 50
#define DEFAULT_LOOP false
#define DEFAULT_COLORS 0

#define READ_BUFFER_SIZE 1024

#define WIDTH_PARAM "width"
#define HEGHT_PARAM "height"
#define DELAY_PARAM "delay"
#define LOOP_PARAM "loop"
#define COLORS_PARAM "colors"
#define DATACOLS_PARAM "datacols"

#define TRUE_VALUE "true"
#define FALSE_VALUE "false"

struct params{
    unsigned short width;
    unsigned short height;
    unsigned short delay;
    bool loop;
    unsigned char colors;
    unsigned char datacols;
};

/*
Replace first delimiter symbol to \0 and return pointer to next symbol 
or NULL if there is no delimiter symbols in string
*/
void * split(char str[], char delimiter);

/* Parce head of .3a file to params */
void read_head(FILE *fp, struct params *param);

/* concat two str */
char * append(char * a, char * b);

/* Parce body of .3a file */
char * read_animation(FILE *fp);

#endif
