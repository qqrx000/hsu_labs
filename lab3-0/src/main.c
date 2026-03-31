#include <stdio.h>
#include <stdlib.h>

void heapSort(int *arr, size_t len);

int main(void) {
    size_t lenOfArr;
    if (scanf("%zu", &lenOfArr) != 1 || lenOfArr > 2000000) {
        return EXIT_SUCCESS;
    }
    int *arr = malloc(sizeof(int) * lenOfArr);
    if (arr == NULL) {
        return EXIT_SUCCESS;
    }
    for (size_t i = 0; i < lenOfArr; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_SUCCESS;
        }
    }
    heapSort(arr, lenOfArr);
    for (size_t i = 0; i < lenOfArr; ++i) {
        printf("%d ", arr[i]);
    }
    free(arr);
    return EXIT_SUCCESS;
}

void heapify(int *arr, const size_t heapSize, size_t current) {
    size_t largest = current;
    int needContinue;

    do {
        needContinue = 0;
        const size_t left = largest + largest + 1;
        const size_t right = left + 1;

        if (left < heapSize) {
            if (*(arr + left) > *(arr + largest)) {
                largest = left;
            }
        }

        if (right < heapSize) {
            if (*(arr + right) > *(arr + largest)) {
                largest = right;
            }
        }

        if (largest != current) {
            const int tmp = arr[current];
            arr[current] = arr[largest];
            arr[largest] = tmp;
            current = largest;
            needContinue = 1;
        }
    } while (needContinue);
}

void heapSort(int *arr, const size_t len) {
    if (arr == NULL || len <= 1) {
        return;
    }

    for (int i = (int) (len / 2) - 1; i >= 0; i--) {
        heapify(arr, len, i);
    }

    for (int i = (int) (len - 1); i > 0; i--) {
        arr[0] ^= arr[i];
        arr[i] ^= arr[0];
        arr[0] ^= arr[i];
        heapify(arr, i, 0);
    }
}
