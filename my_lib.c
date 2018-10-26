#include "my_lib.h"

const int threeToPow[17] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049,
                            177147, 531441, 1594323, 4782969, 14348907, 43046721};

void strCmp(unsigned char *str, unsigned char *pattern, int pos, int ind) {
    /*
     * Compare of 2 string - pattern and substring with len = length of pattern
     * */
    int n = strlen((const char *) pattern);
    for (int i = 0; i < n; i++) {
        printf("%d ", pos + i + ind + 1);
        if (str[pos + i] != pattern[i])
            break;
    }
}

int getHash(unsigned char *str, int lenStr) {
    /*
     * Get the hash from the string by the algorithm:
     * hash(c[0], ..., c[N-1]) = sum((c[i] % 3) * (3 ^ i))
     */
    int sum = 0;
    for (int i = 0; i < lenStr; i++)
        sum += (str[i] % 3) * threeToPow[i];
    return sum;
}

int getRehash(int oldHash, unsigned char old, unsigned char new, int lenPat) {
    /*
     * Get the rehash from the hash and old char and new char by the algorithm
     */
    int preHash = (oldHash - (old % 3)) / 3;
    int hashOfChar = (new % 3) * threeToPow[lenPat - 1];
    return preHash + hashOfChar;
}
