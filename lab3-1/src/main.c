#include <stdio.h>
#include <stdlib.h>

void quickSort(int *arr, size_t first, size_t last);

int main(void) {
    size_t lenOfArr;
    if (scanf("%zu", &lenOfArr) != 1 || lenOfArr > 2000000) {
        return EXIT_SUCCESS;
    }

    int *arr = malloc(lenOfArr * sizeof(int));
    if (arr == NULL) {
        return EXIT_SUCCESS;
    }
    for (size_t i = 0; i < lenOfArr; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_SUCCESS;
        }
    }
    if (lenOfArr > 0) {
        quickSort(arr, 0, lenOfArr - 1);
    }
    for (size_t i = 0; i < lenOfArr; ++i) {
        printf("%d ", arr[i]);
    }
    free(arr);
    return EXIT_SUCCESS;
}

void swap(int* a, int* b) {
    const int temp = *a;
    *a = *b;
    *b = temp;
}

void separate(int *arr, const size_t first, const size_t last, size_t *left, size_t *right) {
    const int pivot = arr[(first + last) / 2];
    size_t i = first, j = first, k = last;

    while (j <= k) {
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            ++i;
            ++j;
        } else if (arr[j] > pivot) {
            swap(&arr[j], &arr[k]);
            --k;
        } else {
            ++j;
        }
    }
    *left = i;
    *right = j;
}

void quickSort(int *arr, const size_t first, const size_t last) {
    if (first < last) {
        size_t left, right;
        separate(arr, first, last, &left, &right);
        if (first < left) {
            quickSort(arr, first, left - 1);
        }
        if (right < last) {
            quickSort(arr, right, last);
        }
    }
}
