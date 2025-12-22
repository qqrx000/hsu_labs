#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_OF_SYMBOLS 32
#define ERROR "bad input"

int containsDuplicates(const char *chain, size_t lenOfChain);

int permutations(size_t *chain, size_t lenOfChain, size_t countOfPerm);

int charArrToSizeT(const char *charArr, size_t *numArr, size_t len);

int sizeTArrToChar(char *charArr, const size_t *numArr, size_t len);

int main(void) {
  char chain[LEN_OF_SYMBOLS];
  if (fgets(chain, LEN_OF_SYMBOLS, stdin) == NULL) {
    printf(ERROR);
    return EXIT_SUCCESS;
  }
  size_t lenOfChain = strlen(chain); //not const( due to 27 line
  if (lenOfChain > 0 && chain[lenOfChain - 1] == '\n') { // delete \n
    chain[lenOfChain - 1] = '\0';
    lenOfChain--;
  }
  if (lenOfChain == 0) {
    printf(ERROR);
    return EXIT_SUCCESS;
  }
  if (containsDuplicates(chain, lenOfChain) == 1) {
    printf(ERROR);
    return EXIT_SUCCESS;
  }
  size_t countOfPerm;
  if (scanf("%zu", &countOfPerm) != 1) {
    printf(ERROR);
    return EXIT_SUCCESS;
  }

  size_t *newChain = malloc(lenOfChain * sizeof(size_t));
  if (newChain == NULL) {
    printf(ERROR);
    return EXIT_SUCCESS;
  }
  if (charArrToSizeT(chain, newChain, lenOfChain) == 1) {
    printf(ERROR);
    free(newChain);
    return EXIT_SUCCESS;
  }
  if (permutations(newChain, lenOfChain, countOfPerm) == 1) {
    printf(ERROR);
  }
  free(newChain);
  return EXIT_SUCCESS;
}

int containsDuplicates(const char *chain, const size_t lenOfChain) {
  for (size_t i = 0; i < lenOfChain; ++i) {
    for (size_t j = i + 1; j < lenOfChain; ++j) {
      if (chain[i] == chain[j]) {
        return 1;
      }
    }
  }
  return 0;
}

int charArrToSizeT(const char *charArr, size_t *numArr, const size_t len) {
    for (size_t i = 0; i < len; ++i) {
      if (charArr[i] >= '0' && charArr[i] <= '9') {
        numArr[i] = (size_t)(charArr[i] - '0');
      } else {
        return 1;
      }
    }
    return 0;
}

int sizeTArrToChar(char *charArr, const size_t *numArr, const size_t len) {
  for (size_t i = 0; i < len; ++i) {
    if (numArr[i] <= 9) {
      charArr[i] = (char)(numArr[i] + '0');
    } else {
      return 1;
    }
  }
  return 0;
}

void swap(size_t *s1, size_t *s2) {
  const size_t tmp = *s1;
  *s1 = *s2;
  *s2 = tmp;
}

int permutations(size_t *chain, const size_t lenOfChain,
                 const size_t countOfPerm) {
  size_t countSuccess = 0;
  while (countSuccess < countOfPerm) {
    size_t i = lenOfChain - 1; // find element which smaller then next
    while (i > 0 && chain[i - 1] >= chain[i]) {
      --i;
    }
    if (i == 0) { // last one
      break;
    }
    size_t j = lenOfChain - 1;
    while (chain[j] <= chain[i - 1]) { // find j
      --j;
    }
    swap(&chain[i - 1], &chain[j]);
    j = lenOfChain - 1; // reverse from i-1 for next permutation
    while (i < j) {
      swap(&chain[i], &chain[j]);
      ++i;
      --j;
    }
    char strChain[lenOfChain + 1];
    if (sizeTArrToChar(strChain, chain, lenOfChain) ==
        1) {
      return 1;
    }
    strChain[lenOfChain] = '\0'; // add \0
    printf("%s\n", strChain);
    ++countSuccess;
  }
  return 0;
}
