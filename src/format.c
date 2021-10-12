#include <string.h>
#include <stdlib.h>
#include "format.h"

void * split(char str[], char delimiter){
    for (int i = 0; ; i++){
        if (str[i] == '\0'){
            break;
        }
        if (str[i] == delimiter){
            str[i] = '\0';
            char *p = str;
            p = p + i+1;
            return p;
        }
    }
    return NULL;
}

void escape_comment(char str[]){
    split(str, '\t');
}

void read_head(FILE *fp, struct params *param){
    char buf[READ_BUFFER_SIZE];
    bool datacols_auto = true;
    while(true){
        char *res;
        if((res=fgets(buf, READ_BUFFER_SIZE, fp))==NULL){
            return;
        }
        if (strcmp(buf,"\n")==0){
            break;
        }
        escape_comment(buf);
        char *value = split(buf, ' ');
        if (value==NULL) continue;
        if (strcmp(buf, WIDTH_PARAM)==0){
            param->width = atoi(value);
        }else if (strcmp(buf, HEGHT_PARAM)==0){
            param->height = atoi(value);
        }else if (strcmp(buf, DELAY_PARAM)==0){
            param->delay = atoi(value);
        }else if (strcmp(buf, LOOP_PARAM)==0){
            param->loop = (strcmp(value, FALSE_VALUE)!=0);
        }else if (strcmp(buf, COLORS_PARAM)==0){
            if (strcmp(value, "none")==0){
                param->colors = 0;
            } else if (strcmp(value, "fg")==0){
                param->colors = 1;
            } else if (strcmp(value, "bg")==0){
                param->colors = 2;
            } else if (strcmp(value, "full")==0){
                param->colors = 3;
            }
        }else if (strcmp(buf, DATACOLS_PARAM)==0){
            param->datacols = atoi(value);
            datacols_auto = false;
        }
    }
    if (datacols_auto){
        switch(param->colors){
            case(0):
                param->datacols = 1;
                break;
            case(1):
            case(2):
                param->datacols = 2;
                break;
            case(3):
                param->datacols = 3;
                break;
        }
    }
}

char * append(char * a, char * b){
    char * new = malloc(strlen(a)+strlen(b)+1);
    new[0] = '\0';
    strcat(new,a);
    strcat(new,b);
    return new;
}

char * read_animation(FILE *fp){
    char buf[READ_BUFFER_SIZE];
    size_t pointer = 0;
    char c = '\0';
    char *anim = malloc(1);
    bool loop = true;
    bool comment = false;
    anim[0] = '\0';
    while(loop){
        pointer = 0;
        while(true){
            c=getc(fp);
            if (c==EOF){
                loop = false;
                buf[pointer] = '\0';
                break;
            }
            if (c=='\n'){
                if (comment)
                    comment = false;
                continue;
            }
            if (comment)
                continue;
            if (c=='\t'){
                comment = true;
                continue;
            }
            buf[pointer] = c;
            pointer++;
            if (pointer == READ_BUFFER_SIZE-2){
                buf[pointer] = '\0';
                break;
            }
        }
        char *new = append(anim,buf);
        free(anim);
        anim = new;
    }
    return anim;
}
