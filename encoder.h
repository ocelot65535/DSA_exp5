#ifndef DSA_EXP5_ENCODER_H
#define DSA_EXP5_ENCODER_H

#include "initTree.h"

void encoder_readTree();

int encoder_search(char ch,  HTNode * charlist, int n);

void encoder_encode(HTNode * charlist, hfmCode code, int n, int is_linux);



#endif //DSA_EXP5_ENCODER_H
