#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// work with symbols and memory
#include <ctype.h>
#include <stdlib.h>
#define MAX_INT_PART 13
#define MAX_FRAC_PART 12

int CheckIfBadInput(int fn, int sn);
int CheckIfNumberInNotation(char NumInFNot[], int fn);
int CharToInt(char Char);
void ConvertIntegerPart(int Ipart[], int len, int fNot, int sNot, char result[]);
void ConvertFractionalPart(int Fpart[], int len, int fNot, int sNot, char result[]);

int main(void) {
    int fNot, sNot; //first Notation second Notation
    char Ipart[MAX_INT_PART] = {0}, Fpart[MAX_FRAC_PART] = {0};
    char NumInFNot[14];
    int OnlyIpart = 0;

    scanf("%i %i\n", &fNot, &sNot);
    scanf("%s", NumInFNot);

    if (CheckIfBadInput(fNot, sNot) || CheckIfNumberInNotation(NumInFNot, fNot)) { //checking bad input
        printf("bad input");
        return EXIT_SUCCESS;
    }

    if (fNot == sNot) {
        printf("%s\n", NumInFNot);
        return EXIT_SUCCESS;
    }

    // split integer and frac parts
    int dotPos = -1;
    for (int i = 0; NumInFNot[i] != '\0'; i++) {
        if (NumInFNot[i] == '.') {
            dotPos = i;
            break;
        }
    }

    if (dotPos == -1) {
        strcpy(Ipart, NumInFNot); //copy Ipart
        OnlyIpart = 1;
    } else {
        strncpy(Ipart, NumInFNot, dotPos); //copy Ipart
        strcpy(Fpart, &NumInFNot[dotPos + 1]); //copy Fpart
    }

    int LenOfIpart = strlen(Ipart);
    int LenOfFpart = strlen(Fpart);

    // chars to int
    int IpartInt[MAX_INT_PART] = {0};
    int FpartInt[MAX_FRAC_PART] = {0};
    for (int i = 0; i < LenOfIpart; i++) IpartInt[i] = CharToInt(Ipart[i]);
    for (int i = 0; i < LenOfFpart; i++) FpartInt[i] = CharToInt(Fpart[i]);

    // if frac part is zero
    if (!OnlyIpart) {
        double Fsum = 0;
        for (int i = 0; i < LenOfFpart; i++) Fsum += FpartInt[i] * pow(fNot, -i - 1);
        OnlyIpart = (Fsum == 0);
    }
    // print 10base number imidiatly
    if (sNot == 10) {
        for (int i = 0; i < LenOfIpart; i++) printf("%d", IpartInt[i]);
        if (!OnlyIpart) {
            printf(".");
            for (int i = 0; i < LenOfFpart; i++) printf("%d", FpartInt[i]);
        }
    } else {
        char ArrayForB2Notation[100] = {0};
        char ArrayForB2NotF[100] = {0};

        ConvertIntegerPart(IpartInt, LenOfIpart, fNot, sNot, ArrayForB2Notation); //changing Int Array through func
        if (!OnlyIpart) ConvertFractionalPart(FpartInt, LenOfFpart, fNot, sNot, ArrayForB2NotF); // same for frac

        printf("%s", ArrayForB2Notation);
        if (!OnlyIpart && strlen(ArrayForB2NotF) > 0) printf(".%s", ArrayForB2NotF);
    }

    return EXIT_SUCCESS;
}

void ConvertIntegerPart(int Ipart[], int len, int fNot, int sNot, char result[]) {
    if (len == 0 || (len == 1 && Ipart[0] == 0)) {
        strcpy(result, "0");
        return;
    }

    int digits[100] = {0};
    for (int i = 0; i < len; i++) digits[i] = Ipart[i]; //fill the array in reverse
    char Alphabet[] = "0123456789ABCDEF";
    char Temp[100] = {0};
    int TempPos = 0; //count numbers

    while (len > 0) {
        int remainder = 0; // %
        for (int i = 0; i < len; i++) {
            int current = digits[i] + remainder * fNot;
            digits[i] = current / sNot;
            remainder = current % sNot;
        }
        Temp[TempPos++] = Alphabet[remainder]; //change to chars and nums

        int NewStart = 0; //delete zeroes
        while (NewStart < len && digits[NewStart] == 0) NewStart++;

        for (int i = 0; i < len - NewStart; i++) digits[i] = digits[i + NewStart];

        len -= NewStart;
    }

    for (int i = 0; i < TempPos; i++) result[i] = Temp[TempPos - i - 1]; //reversing final result
}

void ConvertFractionalPart(int Fpart[], int len, int fNot, int sNot, char result[]) {
    int FracDigits[100] = {0};
    for (int i = 0; i < len; i++) FracDigits[i] = Fpart[i]; //new array
    char Alphabet[] = "0123456789ABCDEF";
    int pos = 0;
    for (int i = 0; i < 12 && len > 0; i++) {
        int IntNum = 0; //this is IntNum that remains when we multiply by sNot
        for (int j = len - 1; j >= 0; j--) { //j from end
            int current = FracDigits[j] * sNot + IntNum;
            FracDigits[j] = current % fNot;
            IntNum = current / fNot; //change next pos
        }
        result[pos++] = Alphabet[IntNum];
        while (len > 0 && FracDigits[len - 1] == 0) len--; //delete zeroes after number
    }
    result[pos] = '\0'; //if frac part is void
}

int CheckIfBadInput(int fn, int sn) {
    return (fn < 2 || fn > 16 || sn < 2 || sn > 16);
}

int CheckIfNumberInNotation(char NumInFNot[], int fn) {
    if (strlen(NumInFNot) == 0 || strlen(NumInFNot) > 13) return 1;

    int dotCount = 0, validChars = 0;
    for (int i = 0; NumInFNot[i] != '\0'; i++) {
        char c = toupper(NumInFNot[i]);

        if (c == '.') {
            if (++dotCount > 1 || i == 0 || NumInFNot[i + 1] == '\0') return 1;
            continue;
        }

        int value = (c >= '0' && c <= '9') ? c - '0' :
                   (c >= 'A' && c <= 'F') ? c - 'A' + 10 : -1;
        if (value < 0 || value >= fn) return 1;
        validChars++;
    }
    return (validChars == 0);
}

int CharToInt(char Char) {
    Char = toupper(Char);
    return (Char >= '0' && Char <= '9') ? Char - '0' :
           (Char >= 'A' && Char <= 'F') ? Char - 'A' + 10 : 0;
}