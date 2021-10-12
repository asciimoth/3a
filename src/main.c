#include <argp.h>
#include "format.h"
#include "curses.h"

const char *argp_program_version = "3a 1.0.0";
static char doc[] = "TUI tool for playng .3a animations.";

struct arguments{
    unsigned short delay; bool delay_exist;
    bool loop; bool loop_exist;
    char *file; bool file_exist;
    bool colortable;
};

static struct argp_option options[] = { 
    { "delay", 'd', "NUM", 0, "Force frames draw delay"},
    { "loop", 'l', 0, 0, "Enable loop mode"},
    { "noloop", 'n', 0, 0, "Disable loop mode"},
    { "colortable", 'c', 0, 0, "Show colortable"},
    { 0 } 
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key){
        case ARGP_KEY_ARG: {
            arguments->file = strdup(arg);
            arguments->file_exist = arguments->file != NULL;
            break;
        };
        case 'd': {
            arguments->delay_exist = true;
            arguments->delay = atoi(arg);
            break;
        };
        case 'l': {
            arguments->loop_exist = true;
            arguments->loop = true;
            break;
        };
        case 'n': {
            arguments->loop_exist = true;
            arguments->loop = false;
            break;
        };
        case 'c':{
            arguments->colortable = true;
            break;
        }
    }
    return 0;
}

void apply_args(struct params *param, struct arguments *args){
    if (args->delay_exist){
        param->delay = args->delay;
    }
    if (args->loop_exist){
        param->loop = args->loop;
    }
}

int main( int argc, char **argv ){
    struct arguments arguments = { 0, false, false, false, NULL, false };
    struct argp argp = {options, parse_opt, 0, doc, 0, 0, 0};
    int res = argp_parse (&argp, argc, argv, 0, 0, &arguments);
    if (res != 0)
        return res;
    if (arguments.colortable){
        colordemo();
        return 0;
    }
    struct params params = { 0, 0, DEFAULT_LAG, DEFAULT_LOOP, DEFAULT_COLORS };
    char * animation;
    if(arguments.file_exist){
        //printf("file: %s\n", arguments.file);
        FILE *fp;
        if((fp=fopen(arguments.file, "r"))==NULL){
            printf("Cannot open file %s", arguments.file);
            exit(0);
        }
        read_head(fp, &params);
        apply_args(&params, &arguments);
        animation = read_animation(fp);
        fclose(fp);
    }else{
        //printf("No file in args\n");
        /*
        В качестве параметров используем демо параметры
        возвращаем строку с анимацией из демо
        */
        return 0;
    }
    //printf("%u\n", params.datacols);
    render_ncurses(&params, animation);
    return 0;
}
