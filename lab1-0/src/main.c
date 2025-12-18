#include <stdio.h>
#include <string.h>

#define PAGE_SIZE 1024
#define WRONG_ARR_LEN 256
#define LEN_OF_TEMPLATE 17 //16+1

void analyzeAndPrint(const char *template);

int main(void) {
  char template[LEN_OF_TEMPLATE];
  int i = 0;
  while (i < LEN_OF_TEMPLATE) {
	  const int c = getchar();
	  if (c == EOF || c == '\n') {
	  	break;	  
	  }
	  template[i++] = (char)c;
  }
  if (i == 0) {
	  return 0;
  }
  template[i] = '\0';
  analyzeAndPrint(template);
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
void analyzeAndPrint(const char *template) {
  char buffer[PAGE_SIZE];
  int start_pos = 0;
  int usedBytes = 0;

  while (1) {
    // try to fill the rest buff
    const size_t freeSpace = PAGE_SIZE - usedBytes;
    int count = 0;

    for (size_t i = 0; i < freeSpace; ++i) {
      const int c = getchar();
      if (c == EOF) {
        break;
      }
      buffer[usedBytes + i] = (char)c;
      count++;
    }

    // check if nothing read
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

