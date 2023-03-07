#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int merge(int* arr, int* extra_arr, int low, int mid, int high) {
    int i = low, j = mid + 1, k = low;
    int inversionCount = 0;

    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            extra_arr[k++] = arr[i++];
        }
        else {
            extra_arr[k++] = arr[j++];
            inversionCount += (mid - i + 1);
        }
    }
    while (i <= mid) {
        extra_arr[k++] = arr[i++];
    }
    for (int m = low; m <= high; m++) {
        arr[m] = extra_arr[m];
    }
 
    return inversionCount;
}

int merge_sort(int* arr, int* extra_arr, int low, int high) {
    if (high <= low) {
        return 0;
    }
    int mid = low + (high - low) / 2;

    int inversionCount = 0;

    inversionCount += merge_sort(arr, extra_arr, low, mid); // left side

    inversionCount += merge_sort(arr, extra_arr, mid + 1, high); // right side

    inversionCount += merge(arr, extra_arr, low, mid, high); // merge

    return inversionCount;
}

int main() {
    int n = 0;
    if (scanf("%d", &n) != 1) {
        printf("Error");
        return -1;
    }
    int* arr = malloc((n + 1) * sizeof(int));
    int* extra_arr = malloc((n + 1) * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Error");
            return -1;
        }
    }
    for (int i = 0; i < n; i++) {
        extra_arr[i] = arr[i];
    }

    printf("%d\n", merge_sort(&arr[0], &extra_arr[0], 0, n - 1));
    free(arr);
    return 0;
}