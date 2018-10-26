
#include "my_lib.h"

#define POW_TWO 65537
#define LEN_OF_PAT_AND_BUF 17

int main() {
    unsigned char pattern[LEN_OF_PAT_AND_BUF] = {0};
    unsigned char buffer[LEN_OF_PAT_AND_BUF] = {0};
    unsigned char *str = (unsigned char *) malloc(sizeof(unsigned char) * POW_TWO);
    if (str == NULL) {
        printf("memory didn't give");
        return 0;
    }
    memset(str, '\0', POW_TWO);
    fgets((char *) pattern, LEN_OF_PAT_AND_BUF, stdin);
    int lenPat = strlen((const char *) pattern);
    if (pattern[lenPat - 1] == '\n') {
        pattern[lenPat - 1] = '\0';
        lenPat--;
    } else {
        fgetc(stdin);
    }
    int hashOfPat = getHash(pattern, lenPat);
    printf("%d ", hashOfPat);
    int lenStr = 0, ind = 0, indexStr = 0;
    while ((lenStr = fread(&str[indexStr], sizeof(char), (size_t) (POW_TWO - 1 - indexStr), stdin)) != 0) {
        lenStr += indexStr;
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
        memset(str, '\0', POW_TWO);
        for (int i = 0; i < lenPat; i++)
            str[i] = buffer[i];
        indexStr = lenPat;
        ind += (lenStr - indexStr);
    }
    free(str);
}