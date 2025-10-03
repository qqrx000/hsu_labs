// in, out and work with strings
#include <stdio.h>
#include <string.h>

// math functions
#include <math.h>

// work with symbols and memory
#include <ctype.h>
#include <stdlib.h>
#define MAX_INT_PART 13
#define MAX_FRAC_PART 12
#define ALPHABET "0123456789ABCDEF"

int isScanFCorrect(int firstScan, int secondScan);

int checkIfFractionalZero(const int fPartInt[], int lenOfFPart, int fNot);

int splitNumParts(char numInFNot[], int dotPos, char iPart[], char fPart[]);

int calcDotPos(const char numInFNot[]);

void convertIntegerPart(const int iPart[], int len, int fNot, int sNot, char result[]);

void convertFractionalPart(const int fPart[], int len, int fNot, int sNot, char result[]);

int isBadInput(int base);

int checkIfNumberInNotation(char numInFNot[], int fn);

int charToInt(char ch);

int main(void) {
    int fNot, sNot; //first Notation second Notation
    char numInFNot[14];
    int firstScan = scanf("%2i %2i\n", &fNot, &sNot);
    int secondScan = scanf("%13s", numInFNot);

    if (isBadInput(fNot) || isBadInput(sNot) || checkIfNumberInNotation(numInFNot, fNot) || isScanFCorrect(firstScan, secondScan)) {
        //checking bad input
        printf("bad input");
        return EXIT_SUCCESS;
    }
    if (fNot == sNot) {
        printf("%s\n", numInFNot);
        return EXIT_SUCCESS;
    }
    int dotPos = calcDotPos(numInFNot);

    char iPart[MAX_INT_PART] = {0}, fPart[MAX_FRAC_PART] = {0};
    int onlyIPart = 0;

    onlyIPart = splitNumParts(numInFNot, dotPos, iPart, fPart);

    const int lenOfIPart = (int)strlen(iPart);
    const int lenOfFPart = (int)strlen(fPart);

    // chars to int
    int iPartInt[MAX_INT_PART] = {0};
    int fPartInt[MAX_FRAC_PART] = {0};
    for (int i = 0; i < lenOfIPart; i++) iPartInt[i] = charToInt(iPart[i]);
    for (int i = 0; i < lenOfFPart; i++) fPartInt[i] = charToInt(fPart[i]);

    // if frac part is zero
    if (!onlyIPart) {
        onlyIPart = checkIfFractionalZero(fPartInt, lenOfFPart, fNot);
    }

    char arrForB2Not[100] = {0};
    char arrForB2NotF[100] = {0};

    convertIntegerPart(iPartInt, lenOfIPart, fNot, sNot, arrForB2Not); //changing Int Array through func
    if (!onlyIPart) convertFractionalPart(fPartInt, lenOfFPart, fNot, sNot, arrForB2NotF); // same for frac

    printf("%s", arrForB2Not);
    if (!onlyIPart && (int)strlen(arrForB2NotF) > 0) printf(".%s", arrForB2NotF);
    return EXIT_SUCCESS;
}

int isScanFCorrect(int firstScan, int secondScan) {
    if (firstScan == 2 && secondScan == 1)
        return 0;
    return 1;
}

int checkIfFractionalZero(const int fPartInt[], int lenOfFPart, int fNot) {
    double fSum = 0;
    for (int i = 0; i < lenOfFPart; i++) fSum += fPartInt[i] * pow(fNot, -i - 1);
    return (fSum == 0);
}

int splitNumParts(char numInFNot[], int dotPos, char iPart[], char fPart[]) {
    if (dotPos == -1) {
        strcpy(iPart, numInFNot); //copy iPart
        return 1;
    } else {
        strncpy(iPart, numInFNot, dotPos); //copy iPart
        iPart[dotPos] = '\0';
        strcpy(fPart, &numInFNot[dotPos + 1]); //copy fPart
        return 0;
    }
}

int calcDotPos(const char numInFNot[]) {
    for (int i = 0; numInFNot[i] != '\0'; i++) {
        if (numInFNot[i] == '.') {
            return i;
        }
    }
    return -1;
}

void convertIntegerPart(const int iPart[], int len, int fNot, int sNot, char result[]) {
    if (len == 0 || (len == 1 && iPart[0] == 0)) {
        strcpy(result, "0");
        return;
    }

    int digits[100] = {0};
    for (int i = 0; i < len; i++) digits[i] = iPart[i]; //fill the array in reverse
    char arrForB2NotF[100] = {0};
    int arrForB2NotFPos = 0; //count numbers

    while (len > 0) {
        int remainder = 0; // %
        for (int i = 0; i < len; i++) {
            int current = digits[i] + remainder * fNot;
            digits[i] = current / sNot;
            remainder = current % sNot;
        }
        arrForB2NotF[arrForB2NotFPos++] = ALPHABET[remainder]; //change to chars and nums

        int newStart = 0; //delete zeroes
        while (newStart < len && digits[newStart] == 0) newStart++;

        for (int i = 0; i < len - newStart; i++) digits[i] = digits[i + newStart];

        len -= newStart;
    }

    for (int i = 0; i < arrForB2NotFPos; i++) result[i] = arrForB2NotF[arrForB2NotFPos - i - 1];
    //reversing final result
}

void convertFractionalPart(const int fPart[], int len, int fNot, int sNot, char result[]) {
    int fracDigits[100] = {0};
    for (int i = 0; i < len; i++) fracDigits[i] = fPart[i]; //new array
    int pos = 0;
    for (int i = 0; i < 12 && len > 0; i++) {
        int intNum = 0; //this is intNum that remains when we multiply by sNot
        for (int j = len - 1; j >= 0; j--) {
            //j from end
            int current = fracDigits[j] * sNot + intNum;
            fracDigits[j] = current % fNot;
            intNum = current / fNot; //change next pos
        }
        result[pos++] = ALPHABET[intNum];
        while (len > 0 && fracDigits[len - 1] == 0) len--; //delete zeroes after number
    }
    result[pos] = '\0'; //if frac part is void
}

int isBadInput(int base) {
    return (base < 2 || base > 16);
}

int checkIfNumberInNotation(char numInFNot[], int fn) {
    if (strlen(numInFNot) == 0 || strlen(numInFNot) > MAX_INT_PART) return 1;

    int dotCount = 0, validChars = 0;
    for (int i = 0; numInFNot[i] != '\0'; i++) {
        char c = (char)toupper(numInFNot[i]);

        if (c == '.') {
            if (++dotCount > 1 || i == 0 || numInFNot[i + 1] == '\0') return 1;
            continue;
        }

        int value = -1;
        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            value = c - 'A' + 10;
        }
        if (value < 0 || value >= fn) return 1;
        validChars++;
    }
    return (validChars == 0);
}

int charToInt(char ch) {
    ch = (char)toupper(ch);
    int result;
    if (ch >= '0' && ch <= '9') {
        result = ch - '0';
    } else if (ch >= 'A' && ch <= 'F') {
        result = ch - 'A' + 10;
    } else {
        result = 0;
    }
    return result;
}
