#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_TEMPLATE 18 // 16 + 2 (\0 + \n)

size_t prepareTemplate(char *template); // remove \n

int calcHash(const char *str, size_t len);

void calcPower(int *powers, int len);

int initTemplate(char *text, size_t len,
                 int *changedHash); // read first part of text

int changePattern(char *text, size_t len, int *place, int *changedHash,
                  int power);

void analyzeCollision(const char *text, const char *template, size_t len,
                      int changedHash, int hashTemp,
                      int place); // check what to print

int main(void) {
  char template[SIZE_OF_TEMPLATE];
  if (fgets(template, sizeof(template), stdin) == NULL)
    return EXIT_SUCCESS;

  const size_t lenOfTemp = prepareTemplate(template);
  if (lenOfTemp == 0)
    return EXIT_SUCCESS;
  // if template not null -> print hash
  const int hashTemp = calcHash(template, lenOfTemp);
  printf("%d ", hashTemp);

  if ((int)lenOfTemp > SIZE_OF_TEMPLATE)
    return EXIT_SUCCESS;

  int powers[SIZE_OF_TEMPLATE];
  calcPower(powers, (int)lenOfTemp);
  const int power = powers[lenOfTemp - 1];

  char text[SIZE_OF_TEMPLATE];
  int changedHash; // read first part to check
  const int read = initTemplate(text, lenOfTemp, &changedHash);

  if (read < (int)lenOfTemp)
    return EXIT_SUCCESS;

  int place = 0; // first check
  analyzeCollision(text, template, lenOfTemp, changedHash, hashTemp, place);
  // check while text is not end
  while (changePattern(text, lenOfTemp, &place, &changedHash, power)) {
    analyzeCollision(text, template, lenOfTemp, changedHash, hashTemp, place);
  }
  return EXIT_SUCCESS;
}

// clear newline from template
size_t prepareTemplate(char *template) {
  template[SIZE_OF_TEMPLATE - 1] = '\0';
  size_t lenOfTemp = strlen(template);
  if (lenOfTemp > 0 && template[lenOfTemp - 1] == '\n') {
    template[lenOfTemp - 1] = '\0'; // remove \n
    lenOfTemp--;
  }
  return lenOfTemp;
}

int calcHash(const char *str, const size_t len) {
  int hash = 0;
  int power = 1;
  for (size_t i = 0; i < len; ++i) {
    hash += (unsigned char)str[i] % 3 * power;
    power *= 3;
  }
  return hash;
}

void calcPower(int *powers, const int len) {
  powers[0] = 1;
  for (int i = 1; i < len; ++i) {
    powers[i] = powers[i - 1] * 3;
  }
}
// read first part of text and calc hash
int initTemplate(char *text, const size_t len, int *changedHash) {
  int power = 1;
  int read = 0;
  *changedHash = 0;

  for (size_t i = 0; i < len; ++i) {
    const int ch = getchar();
    if (ch == EOF)
      break;
    text[i] = (char)ch;
    *changedHash += (unsigned char)ch % 3 * power;
    power *= 3;
    read++;
  }
  // if read is finish
  if (read == (int)len)
    text[len] = '\0';

  return read;
}
// change by one char and recalc hash
int changePattern(char *text, const size_t len, int *place, int *changedHash,
                  const int power) {
  const int ch = getchar();
  if (ch == EOF)
    return EXIT_SUCCESS;
  // remove left char, change powers, add new char, *power
  *changedHash = (*changedHash - (unsigned char)text[0] % 3) / 3 +
                 (unsigned char)ch % 3 * power;

  memmove(text, text + 1, len - 1);
  text[len - 1] = (char)ch;

  (*place)++;
  return EXIT_FAILURE;
}

void analyzeCollision(const char *text, const char *template, const size_t len,
                      const int changedHash, const int hashTemp,
                      const int place) {
  if (changedHash == hashTemp) {

    size_t limit;
    if (len > 0)
      limit = len - 1; // compare all without last one
    else
      limit = 0; // nothing need to do
    size_t j;
    // stop if not equal
    for (j = 0; j < limit; ++j) {
      if (text[j] != template[j])
        break;
    }

    if (j < limit) {
      printf("%d ", place + 1); // print only first pos
    } else {
      for (size_t k = 0; k < len; ++k) {
        printf("%d ", place + (int)k + 1); // full equal
      }
    }
  }
}
