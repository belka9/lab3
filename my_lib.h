#include <stdio.h>
#include <malloc.h>
#include <string.h>
void strCmp(unsigned char *str, unsigned char *pattern, int pos, int ind);

int getHash(unsigned char *str, int lenStr);

int getRehash(int oldHash, unsigned char old, unsigned char new, int lenPat);