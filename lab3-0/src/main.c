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

void swap(int *a, int *b) {
    const int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int *arr, const size_t heapSize, const size_t current) {
    size_t maxIndex = current;
    const size_t leftChild = 2 * current + 1;
    const size_t rightChild = 2 * current + 2;

    if (leftChild < heapSize && arr[leftChild] > arr[maxIndex]) {
        maxIndex = leftChild;
    }

    if (rightChild < heapSize && arr[rightChild] > arr[maxIndex]) {
        maxIndex = rightChild;
    }

    if (maxIndex != current) {
        swap(&arr[current], &arr[maxIndex]);
        heapify(arr, heapSize, maxIndex);
    }
}

void heapSort(int *arr, const size_t len) {
    for (int i = (int) (len / 2 - 1); i >= 0; i--) {
        heapify(arr, len, i);
    }

    for (int i = (int) (len - 1); i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}
