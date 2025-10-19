#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_TEMPLATE 16
#define SIZE_OF_TEXT 128

int hashOfTemplate(char template[]);

size_t lenOfTemplate(char template[]);

int main(void) {
  char template[SIZE_OF_TEMPLATE] = {0};
  char text[SIZE_OF_TEXT] = {0};
  if (scanf("%15s\n", template) != 1 || scanf("%128s", text) != 1) {
    return EXIT_SUCCESS;
  }
  const int hash = hashOfTemplate(template);
  printf("%i\n", hash);
  return EXIT_SUCCESS;
}

int hashOfTemplate(char template[]) {
  const size_t len = lenOfTemplate(template);
  double hash = 0.0;
  for (size_t i = 0; i < len; i++) {
    hash += (template[i] % 3) * pow(3, (double)i);
  }
  return (int)hash;
}

size_t lenOfString(char string[]) {
  const size_t len = strlen(string);
  for (size_t i = 0; i < len; i++) {
    if (string[i + 1] == '0') {
      string[i+1] = '\0';
      return i;
    }
  }
  return len;
}