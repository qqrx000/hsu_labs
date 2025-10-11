#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT_PART 13
#define MAX_FRAC_PART 12
#define MAX_LEN_STRING 14
#define ALPHABET "0123456789ABCDEF"
#define ARRAY_SIZE 64

int checkIfFractionalZero(const char fPartInt[], size_t lenOfFPart, int fNot);

int splitNumParts(char numInFNot[], char iPart[], char fPart[]);

void convertIntegerPart(const char iPart[], size_t len, int fNot, int sNot,
                        char result[]);

void convertFractionalPart(const char fPart[], size_t len, int fNot, int sNot,
                           char result[]);

int isBadInput(int base);

int checkIfNumberInNotation(char numInFNot[], int fn);

int charToInt(char ch);

int main(void) {
  int fNot, sNot; // first Notation second Notation
  char numInFNot[MAX_LEN_STRING];
  if (scanf("%2i %2i\n", &fNot, &sNot) != 2) return EXIT_SUCCESS;
  if (scanf("%13s", numInFNot) != 1) return EXIT_SUCCESS;

  if (isBadInput(fNot) || isBadInput(sNot) ||
      checkIfNumberInNotation(numInFNot, fNot)) {
    printf("bad input");
    return EXIT_SUCCESS;
  }
  if (fNot == sNot) {
    printf("%s\n", numInFNot);
    return EXIT_SUCCESS;
  }

  char iPart[MAX_INT_PART] = {0}, fPart[MAX_FRAC_PART] = {0};
  const int onlyIPart = splitNumParts(numInFNot, iPart, fPart);

  const size_t lenOfIPart = strlen(iPart);
  const size_t lenOfFPart = strlen(fPart);

  char arrForB2Not[ARRAY_SIZE] = {0};
  char arrForB2NotF[ARRAY_SIZE] = {0};

  convertIntegerPart(iPart, lenOfIPart, fNot, sNot, arrForB2Not); // changing Int Array through func
  convertFractionalPart(fPart, lenOfFPart, fNot, sNot, arrForB2NotF); // same for frac

  printf("%s", arrForB2Not);
  if (onlyIPart == 0 && !checkIfFractionalZero(fPart, lenOfFPart, fNot)) printf(".%s", arrForB2NotF);
  return EXIT_SUCCESS;
}

int checkIfFractionalZero(const char fPartInt[], const size_t lenOfFPart, const int fNot) {
  double fSum = 0;
  for (size_t i = 0; i < lenOfFPart; i++)
    fSum += fPartInt[i] * pow(fNot, -i - 1);
  return (fSum == 0);
}

int splitNumParts(char numInFNot[], char iPart[], char fPart[]) {
  int dotPos = -1;
  for (int i = 0; numInFNot[i] != '\0'; i++) {
    if (numInFNot[i] == '.') {
      dotPos = i;
      break;
    }
  }
  if (dotPos == -1) {
    strcpy(iPart, numInFNot); // copy iPart
    return 1;
  }
  strncpy(iPart, numInFNot, dotPos); // copy iPart
  iPart[dotPos] = '\0';
  strcpy(fPart, &numInFNot[dotPos + 1]); // copy fPart
  return 0;
}

void convertIntegerPart(const char iPart[], size_t len, const int fNot, const int sNot,
                        char result[]) {
  int iPartInt[MAX_INT_PART] = {0};
  for (size_t i = 0; i < len; i++)
    iPartInt[i] = charToInt(iPart[i]);
  if (len == 0 || (len == 1 && iPartInt[0] == 0)) {
    strcpy(result, "0");
    return;
  }
  int digits[ARRAY_SIZE] = {0};
  for (size_t i = 0; i < len; i++) digits[i] = iPartInt[i]; // fill the array in reverse
  char arrForB2NotF[ARRAY_SIZE] = {0};
  int arrForB2NotFPos = 0; // count numbers

  while (len > 0) {
    int remainder = 0; // %
    for (size_t i = 0; i < len; i++) {
      int current = digits[i] + remainder * fNot;
      digits[i] = current / sNot;
      remainder = current % sNot;
    }
    arrForB2NotF[arrForB2NotFPos++] =
        ALPHABET[remainder]; // change to chars and nums

    size_t newStart = 0; // delete zeroes
    while (newStart < len && digits[newStart] == 0) newStart++;

    for (size_t i = 0; i < len - newStart; i++) digits[i] = digits[i + newStart];

    len -= newStart;
  }

  for (int i = 0; i < arrForB2NotFPos; i++)
    result[i] = arrForB2NotF[arrForB2NotFPos - i - 1];
  // reversing final result
}

void convertFractionalPart(const char fPart[], size_t len, const int fNot,const int sNot,
                           char result[]) {
  int fPartInt[MAX_FRAC_PART] = {0};
  for (size_t i = 0; i < len; i++)
    fPartInt[i] = charToInt(fPart[i]);

  int fracDigits[ARRAY_SIZE] = {0};
  for (size_t i = 0; i < len; i++)
    fracDigits[i] = fPartInt[i]; // new array
  int pos = 0;
  for (int i = 0; i < MAX_FRAC_PART && len > 0; i++) {
    int intNum = 0; // this is intNum that remains when we multiply by sNot
    for (size_t j = len - 1; j > 0; j--) {
      // j from end
      const int current = fracDigits[j] * sNot + intNum;
      fracDigits[j] = current % fNot;
      intNum = current / fNot; // change next pos
    }
    result[pos++] = ALPHABET[intNum];
    while (len > 0 && fracDigits[len - 1] == 0)
      len--; // delete zeroes after number
  }
  result[pos] = '\0'; // if frac part is void
}

int isBadInput(const int base) { return (base < 2 || base > 16); }

int checkIfNumberInNotation(char numInFNot[], const int fn) {
  const size_t len = strlen(numInFNot);
  if (len == 0 || len > MAX_INT_PART)
    return 1;

  int dotCount = 0, validChars = 0;
  for (int i = 0; numInFNot[i] != '\0'; i++) {
    char c = (char)toupper(numInFNot[i]);

    if (c == '.') {
      if (++dotCount > 1 || i == 0 || numInFNot[i + 1] == '\0')
        return 1;
      continue;
    }

    int value = -1;
    if (c >= '0' && c <= '9') {
      value = c - '0';
    } else if (c >= 'A' && c <= 'F') {
      value = c - 'A' + 10;
    }
    if (value < 0 || value >= fn)
      return 1;
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
