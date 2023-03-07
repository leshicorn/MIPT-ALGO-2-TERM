#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE_TO_USE_INSERTION_SORT 10

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int choose_pivot(int low, int high) {
    // Choose a random pivot between low and high
    return low + rand() % (high - low + 1);
}

int partition(int* arr, int low, int high) {
    int pivot_idx = choose_pivot(low, high);
    int pivot = arr[pivot_idx];

    // Move pivot to end of array
    swap(&arr[pivot_idx], &arr[high]);

    int i = low - 1;
    int j = high;

    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (j >= low && arr[j] > pivot);

        if (i >= j) {
            break;
        }

        swap(&arr[i], &arr[j]);
    }

    // Move pivot to its final position
    swap(&arr[i], &arr[high]);

    return i;
}

void insertion_sort(int* arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void quick_sort(int* arr, int low, int high) {
    while (high - low + 1 > MIN_SIZE_TO_USE_INSERTION_SORT) {
        int pivot_idx = partition(arr, low, high);

        if (pivot_idx - low < high - pivot_idx) {
            quick_sort(arr, low, pivot_idx - 1);
            low = pivot_idx + 1;
        } else {
            quick_sort(arr, pivot_idx + 1, high);
            high = pivot_idx - 1;
        }
    }

    insertion_sort(arr, low, high);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("Error: invalid input");
        return 1;
    }

    int* arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Error: memory allocation failed");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Error: invalid input");
            free(arr);
            return 1;
        }
    }

    quick_sort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}