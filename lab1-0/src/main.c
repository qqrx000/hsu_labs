#include <stdio.h>
#include <string.h>

#define PAGE_SIZE 1024
#define WRONG_ARR_LEN 256
#define LEN_OF_TEMPLATE 17 //16+1

void analyzeAndPrint(FILE *file, const char *template);

int main(void) {
  char template[LEN_OF_TEMPLATE];
  // read template
  if (fgets(template, sizeof(template), stdin)==NULL) {
    return 0; // nothing read
  }
  size_t len = strlen(template);
  if (len > 0 && template[len - 1] == '\n') {
	  template[len-1] = '\0';
  }
  analyzeAndPrint(stdin, template);
  return 0;
}

void wrongCharArr(const char *template, int wrongArr[WRONG_ARR_LEN]) {
  const int lenOfTemp = (int)strlen(template);
  // set default shift
  for (int i = 0; i < WRONG_ARR_LEN; i++) {
    wrongArr[i] = lenOfTemp;
  }
  // set shift values for template chars except last
  for (int i = 0; i < lenOfTemp - 1; i++) {
    wrongArr[(unsigned char)template[i]] = lenOfTemp - i - 1;
  }
}

// update search window
int updateWindow(const int shift, const int lenOfTemp, const int index,
                 const char *text, int wrongArr[WRONG_ARR_LEN]) {
  // if mismatch happened
  if (index >= 0) {
    const int badChar = (unsigned char)text[shift + lenOfTemp - 1];
    return shift + wrongArr[badChar];
  }
  // if full pattern matched
  return shift + lenOfTemp;
}

// Boyer–Moore
int search(const char *text, const char *template, const int textLen,
           const int start_pos) {
  const int lenOfTemp = (int)strlen(template);
  int wrongArr[WRONG_ARR_LEN];
  wrongCharArr(template, wrongArr);
  int shift = 0;
  // keep searching while pattern fits
  while (shift <= textLen - lenOfTemp) {
    int index = lenOfTemp - 1;
    // compare characters from right to left
    while (index >= 0) {
      // print position being checked
      printf("%d ", start_pos + shift + index + 1);
      if (text[shift + index] != template[index]) {
        break; // stop cause mismatch
      }
      index--; // move left
    }
    shift = updateWindow(shift, lenOfTemp, index, text, wrongArr);
  }
  return shift;
}

//read file and search
void analyzeAndPrint(FILE *file, const char *template) {
  char buffer[PAGE_SIZE];
  int start_pos = 0;
  int usedBytes = 0;

  while (1) {
    // try to fill the rest buff
    const int freeSpace = PAGE_SIZE - usedBytes;
    const int count = fread(buffer + usedBytes, 1, freeSpace, file);
    // check if nothing readed
    if (count <= 0) {
      break;
    }
    usedBytes += count;

    int consumed = search(buffer, template, usedBytes, start_pos);

    // if consumed more than we have — protect
    if (consumed > usedBytes) {
      consumed = usedBytes;
    }
    // move to begin
    const int leftover = usedBytes - consumed;
    if (leftover > 0) {
      memmove(buffer, buffer + consumed, leftover);
    }
    //update counters
    usedBytes = leftover;
    start_pos += consumed;
  }
}

