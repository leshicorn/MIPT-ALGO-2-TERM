#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Merge(int* arr, int* extra_arr, const int low, const int mid, const int high) {
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

int MergeSort(int* arr, int* extra_arr, const int low, const int high) {
    if (high <= low) {
        return 0;
    }
    int mid = low + (high - low) / 2;

    int inversionCount = 0;

    inversionCount += MergeSort(arr, extra_arr, low, mid); // left side

    inversionCount += MergeSort(arr, extra_arr, mid + 1, high); // right side

    inversionCount += Merge(arr, extra_arr, low, mid, high); // Merge

    return inversionCount;
}

int Input(int* arr, const int n) {
    for (size_t i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Error");
            return -1;
        }
    }
    return 0;
}

void CopyArray(const int* arr, int* ExtraArr, const int n) {
    for (size_t i = 0; i < n; ++i) {
        ExtraArr[i] = arr[i];
    }
}

void PrintAnswer(const int* arr, const int* ExtraArr, const int n) {
    printf("%d\n", MergeSort(&arr[0], &ExtraArr[0], 0, n - 1));
    free(arr);
}

int main() {
    int n = 0;
    if (scanf("%d", &n) != 1) {
        printf("Error");
        return -1;
    }
    int* arr = malloc((n + 1) * sizeof(int));
    int* ExtraArr = malloc((n + 1) * sizeof(int));


    if (Input(arr, n) == -1) {
        printf("Error\n");
        return -1;
    }

    CopyArray(arr, ExtraArr, n);

    PrintAnswer(arr, ExtraArr, n);

    return 0;
}