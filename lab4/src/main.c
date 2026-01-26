#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t countOfOper;
    if (scanf("%zu", &countOfOper) != 1 || countOfOper > 50) {
        printf("bad input");
        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}
