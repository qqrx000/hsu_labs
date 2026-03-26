#include <stdio.h>
#include <stdlib.h>

typedef enum { ADD, SUB, MUL, DIV } operationType;

typedef struct List {
    char operator;
    operationType typeOfOper;
    int priority;
    struct List *next;
} List;

void initList(List **l) {
    *l = NULL;
}

void deinitList(List **l) {
    List *current = *l;
    while (current) {
        List *temp = current;
        current = current->next;
        free(temp);
    }
    *l = NULL;
}

void destroy(List *l) {
    while (l != NULL) {
        List *temp = l;
        l = l->next;
        free(temp);
    }
}

List *prepend(List *l, const char operator, const operationType typeOfOper, const int priority) {
    List *ln = malloc(sizeof(*ln));
    if (!ln) {
        destroy(l);
        return NULL;
    }
    ln->operator = operator;
    ln->typeOfOper = typeOfOper;
    ln->priority = priority;
    ln->next = l;
    return ln;
}

List *append(List *l, const char operator, const operationType typeOfOper, const int priority) {
    if (!l) return prepend(l, operator, typeOfOper, priority);
    List *lc = l;
    List *ln = malloc(sizeof(*ln));
    while (l->next) {
        l = l->next;
    }
    l->next = ln;
    l->next->next = NULL;
    l->operator = operator;
    l->typeOfOper = typeOfOper;
    l->priority = priority;
    return lc;
}

int main(void) {
    size_t countOfOper;
    if (scanf("%zu", &countOfOper) != 1 || countOfOper > 50) {
        printf("syntax error");
        return EXIT_SUCCESS;
    }
    List *listOfOpers;
    initList(&listOfOpers);
    for (size_t i = 0; i < countOfOper; i++) {
        char operator;
        int priority;
        operationType typeOfOper;
        if (scanf("%c %operationType %d", &operator, &typeOfOper, &priority) != 3) {
            printf("syntax error");
            return EXIT_SUCCESS;
        }
        listOfOpers = append(listOfOpers, operator, typeOfOper, priority);
    }

    return EXIT_SUCCESS;
}
