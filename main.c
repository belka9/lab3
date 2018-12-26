
#include "my_lib.h"

#define POW_TWO 65537
#define LEN_OF_PAT_AND_BUF 17

int main() {
    const int threeToPow[17] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049,
                                177147, 531441, 1594323, 4782969, 14348907, 43046721};
    unsigned char pattern[LEN_OF_PAT_AND_BUF] = {0};
    unsigned char buffer[LEN_OF_PAT_AND_BUF] = {0};
    unsigned char *str = (unsigned char *) malloc(sizeof(unsigned char) * POW_TWO);
    if (str == NULL) {
        printf("memory didn't give");
        return 1;
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
    int hashOfPat = getHash(pattern, lenPat, threeToPow);
    printf("%d ", hashOfPat);
    int lenStr = 0, ind = 0, indexStr = 0;
    while ((lenStr = fread(&str[indexStr], sizeof(char), (size_t) (POW_TWO - 1 - indexStr), stdin)) != 0) {
        lenStr += indexStr;
        int hashOfStr = getHash(str, lenPat, threeToPow);
        if (hashOfPat == hashOfStr)
            strCmp(str, pattern, 0, ind);
        for (int i = 1; i < lenStr - lenPat + 1; i++) {
            hashOfStr = getRehash(hashOfStr, str[i - 1], str[lenPat + i - 1], lenPat, threeToPow);
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
