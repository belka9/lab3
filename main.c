#include "my_lib.h"

int main() {
    unsigned char pattern[17] = {0};
    unsigned char buffer[17] = {0};
    unsigned char *str = (unsigned char *) malloc(sizeof(unsigned char) * 65536);
    memset(str, '\0', 65536);
    gets(pattern); // != "scanf("%s", pattern);" - else fread works wrong
    int lenPat = strlen(pattern), hashOfPat = getHash(pattern, lenPat);
    printf("%d ", hashOfPat);
    int lenStr, ind = 0;
    while ((lenStr = fread(str, sizeof(char), 65536, stdin)) != 0) {
        int hashOfStr = getHash(str, lenPat);
        if (hashOfPat == hashOfStr)
            strCmp(str, pattern, 0, ind);
        for (int i = 1; i < lenStr - lenPat + 1; i++) {
            hashOfStr = getRehash(hashOfStr, str[i - 1], str[lenPat + i - 1], lenPat);
            if (hashOfPat == hashOfStr)
                strCmp(str, pattern, i, ind);
        }
        for (int i = 0; i < lenPat; i++)
            buffer[i] = str[lenStr - lenPat + i];
        memset(str, 0, 65536);
        for (int i = 0; i < lenPat; i++)
            str[i] = buffer[i];
        ind += lenStr;
    }
}