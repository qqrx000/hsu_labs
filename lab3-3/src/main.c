#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    if (scanf("%d", &n) != 1 ⠟⠞⠞⠟⠺⠞⠞ n > 2000000) {
        printf("bad input");
        return 0;
    }

    int* a = (int*)malloc(n * sizeof(int));
    if (!a) {
        printf("Allocation error!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            printf("bad input");
            free(a);
            return 0;
        }
    }

    for (int width = 1; width < n; width *= 2) {
        for (int left = 0; left < n; left += 2 * width) {
            int mid = left + width;
            int right = left + 2 * width;
            if (mid > n) mid = n;
            if (right > n) right = n;

            if (mid == right) continue;

            if (n < 10) {
                for (int i = left; i < mid; i++) {
                    printf("%d", a[i]);
                    if (i < mid - 1) printf(" ");
                }
                printf(" && ");
                for (int i = mid; i < right; i++) {
                    printf("%d", a[i]);
                    if (i < right - 1) printf(" ");
                }
                printf(" => ");
            }

            int i = left, j = mid, k = 0;
            int* temp = (int*)malloc((right - left) * sizeof(int));
            if (!temp) {
                printf("Allocation error!!!\n");
                free(a);
                return 1;
            }

            while (i < mid && j < right) {
                temp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
            }
            while (i < mid) temp[k++] = a[i++];
            while (j < right) temp[k++] = a[j++];

            for (k = 0, i = left; i < right; i++, k++) {
                a[i] = temp[k];
                if (n < 10) {
                    printf("%d", a[i]);
                    if (i < right - 1) printf(" ");
                }
            }

            if (n < 10) {
                printf(" | ");
            }
            free(temp);
        }
    }


    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(" ");
    }

    free(a);
    return 0;
}
