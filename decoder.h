#ifndef DSA_EXP5_DECODER_H
#define DSA_EXP5_DECODER_H
#include "encoder.h"
#include <regex.h>
 typedef struct char2code{
    char * code;
    int length;
    char character;
    struct char2code * next;
}char2code;

char2code * decoder_initList();

void decoder_addnode(char2code * head, char ch, char * code, int length);

char2code * decoder_parsing_file(int is_linux);

void decoder_decode(int is_linux);

char decoder_sreach_code(char2code * head, char * string, int length);


#endif //DSA_EXP5_DECODER_H
