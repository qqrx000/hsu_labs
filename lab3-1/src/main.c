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

size_t separate(int *arr, const size_t first, const size_t last) {
    const int pivot = arr[(first+last)/2];
    size_t i = first - 1;
    size_t j = last + 1;

    while (1) {
        while (arr[i] < pivot) {
            ++i;
        }
        while (arr[j] > pivot) {
            --j;
        }
        if (i >= j) {
            return j;
        }
        swap(&arr[i], &arr[j]);
    }

}

void quickSort(int *arr, const size_t first, const size_t last) {
    if (first < last) {
        const size_t middle = separate(arr, first, last);
        quickSort(arr, first, middle);
        quickSort(arr, middle+1, last);
    }
}
